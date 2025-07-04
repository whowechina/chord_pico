/*
 * Controller Main
 * WHowe <github.com/whowechina>
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "bsp/board.h"
#include "pico/multicore.h"
#include "pico/bootrom.h"

#include "hardware/gpio.h"
#include "hardware/sync.h"
#include "hardware/structs/ioqspi.h"
#include "hardware/structs/sio.h"

#include "tusb.h"
#include "usb_descriptors.h"

#include "board_defs.h"

#include "save.h"
#include "config.h"
#include "cli.h"
#include "commands.h"

#include "light.h"
#include "button.h"
#include "hall.h"

static void run_lights()
{
    bool lflash = (time_us_32() >> 16) & 0x01;
    bool rflash = lflash;

    for (int i = 0; i < 12; i++) {
        if (hall_key_actuated(i)) {
            light_set_key(i, rgb32(255, 0, 255, false), false);
        } else {
            uint8_t travel = MAX(hall_key_travel_byte(i), 8);
            light_set_key(i, rgb32_from_hsv(0, 0, travel), false);
        }
    }

    uint16_t fader = ~(button_read() & 0x3ff);

    uint8_t ll = 0x20;
    uint8_t lr = 0x20;
    uint8_t rl = 0x20;
    uint8_t rr = 0x20;

    if (fader & 0x03) {
        ll = 0xff;
        lr = 0;
    } else if (fader & 0x18) {
        ll = 0;
        lr = 0xff;
    } else {
        lflash = false;
    }

    if (fader & 0x60) {
        rl = 0xff;
        rr = 0;
    } else if (fader & 0x300) {
        rl = 0;
        rr = 0xff;
    } else {
        rflash = false;
    }

    light_set_fader(0, lflash ? 0 : rgb32_from_hsv(85, 220, ll), false);
    light_set_fader(1, lflash ? 0 : rgb32_from_hsv(85, 220, lr), false);
    light_set_fader(2, rflash ? 0 : rgb32_from_hsv(0, 220, rl), false);
    light_set_fader(3, rflash ? 0 : rgb32_from_hsv(0, 220, rr), false);
}

static mutex_t core1_io_lock;
static void core1_loop()
{
    while (1) {
        if (mutex_try_enter(&core1_io_lock, NULL)) {
            run_lights();
            light_update();
            mutex_exit(&core1_io_lock);
        }
        cli_fps_count(1);
        sleep_us(700);
    }
}

struct __attribute__((packed)) {
    uint32_t buttons;
    uint8_t joy[2];
} hid_report, old_hid_report;

static uint8_t fader_bits_to_axis(uint8_t fader)
{
    switch (fader) {
        case 0x01: // 10000
            return 0;
        case 0x03: // 11000
            return 31;
        case 0x02: // 01000
            return 63;
        case 0x06: // 01100
            return 95;
        case 0x04: // 00100
            return 127;
        case 0x0c: // 00110
            return 159;
        case 0x08: // 00010
            return 191;
        case 0x18: // 00011
            return 223;
        case 0x10: // 00001
            return 255;
        default:
            return 127;  // 其他情况
    }
}

static void hid_update()
{
    uint32_t buttons = button_read() ^ 0x3ff; // invert the fader bits

    hid_report.buttons = buttons << 12;
    for (int i = 0; i < 12; i++) {
        if (hall_key_actuated(i)) {
            hid_report.buttons |= (1 << i);
        }
    }

    hid_report.joy[0] = fader_bits_to_axis(buttons & 0x1f);
    hid_report.joy[1] = fader_bits_to_axis((buttons >> 5) & 0x1f);

    if (tud_hid_ready()) {
        if ((memcmp(&hid_report, &old_hid_report, sizeof(hid_report)) != 0) &&
             tud_hid_report(REPORT_ID_JOYSTICK, &hid_report, sizeof(hid_report))) {
            old_hid_report = hid_report;
        }
    }
}

static void debug_display()
{
    static uint64_t last_display = 0;
    uint64_t now = time_us_64();
    if (now - last_display < 100000) {
        return;
    }
    last_display = now;

    if (chord_runtime.debug.fader) {
        printf("FADER:");
        uint16_t fader = button_read() & 0x3ff;

        for (int i = 0; i < 10; i++) {
            bool left = i < 5;
            int id = i % 5 + 1;

            if ((fader & (1 << i)) == 0) {
                printf("%s%d", left ? "L" : "R", id);
            } else {
                printf("  ");
            }

            if (i == 4) {
                printf(" -- ");
            }
        }
        printf("\n");
    }
}

static void core0_loop()
{
    uint64_t next_frame = 0;
    while(1) {
        tud_task();

        cli_run();

        save_loop();
        cli_fps_count(0);

        button_update();
        hall_update();

        hid_update();

        debug_display();
        sleep_until(next_frame);
        next_frame += 1000;
    }
}

/* if certain key pressed when booting, enter update mode */
static void update_check()
{
    const uint8_t pins[] = BUTTON_DEF;
    // AUX 1 and AUX 2
    for (int i = 0; i < 2; i++) {
        uint8_t gpio = pins[count_of(pins) - 1 - i];
        gpio_init(gpio);
        gpio_set_function(gpio, GPIO_FUNC_SIO);
        gpio_set_dir(gpio, GPIO_IN);
        gpio_pull_up(gpio);
        sleep_ms(1);
        if (gpio_get(gpio)) {
            return;
        }
    }

    sleep_ms(100);
    reset_usb_boot(0, 2);
}

void init()
{
    sleep_ms(50);
    board_init();

    update_check();

    tusb_init();
    stdio_init_all();

    config_init();
    mutex_init(&core1_io_lock);
    save_init(0xca44cbbe, &core1_io_lock);

    light_init();
    button_init();
    hall_init();

    cli_init("chord_pico>", "\n   << Chord Pico Controller >>\n"
                            " https://github.com/whowechina\n\n");
    
    commands_init();
}

int main(void)
{
    init();
    multicore_launch_core1(core1_loop);
    core0_loop();
    return 0;
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id,
                               hid_report_type_t report_type, uint8_t *buffer,
                               uint16_t reqlen)
{
    printf("Get from USB %d-%d\n", report_id, report_type);
    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id,
                           hid_report_type_t report_type, uint8_t const *buffer,
                           uint16_t bufsize)
{
    if ((report_id == REPORT_ID_LIGHTS) && (bufsize >= 48)) {
        for (int i = 0; i < 12; i++) {
            const uint8_t *rgb = &buffer[i * 3];
            uint32_t color = rgb32(rgb[0], rgb[1], rgb[2], false);
            light_set_key(i, color, true);
        }
        for (int i = 0; i < 4; i++) {
            const uint8_t *rgb = &buffer[36 + i * 3];
            uint32_t color = rgb32(rgb[0], rgb[1], rgb[2], false);
            light_set_fader(i, color, true);
        }
    }
}
