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
    for (int i = 0; i < 12; i++) {
        if (hall_key_actuated(i)) {
            light_set_key(i, rgb32(255, 0, 255, false), false);
        } else {
            uint8_t travel = hall_key_travel_byte(i);
            light_set_key(i, rgb32_from_hsv(0, 0, travel), false);
        }
    }
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

#define AUX_1_MASK 0x0100
#define AUX_2_MASK 0x0080
#define ALL_BUTTON_MASK 0x7f
#define VIRTUAL_BUTTON_SHIFT 7

static void hid_update()
{
    uint32_t buttons = button_read();
    for (int i = 0; i < 6; i++) {
        if (hall_key_actuated(i)) {
            buttons |= (1 << i);
        }
    }

    hid_report.buttons = buttons & ALL_BUTTON_MASK;

    bool left_aux = buttons & AUX_1_MASK;
    bool right_aux = buttons & AUX_2_MASK;
    if (left_aux || right_aux) {
        hid_report.buttons <<= VIRTUAL_BUTTON_SHIFT;
    }
    if (left_aux && right_aux) {
        hid_report.buttons <<= VIRTUAL_BUTTON_SHIFT;
    }

    for (int i = 0; i < 2; i++) {
        hid_report.joy[i] = 0;
    }

    if (tud_hid_ready()) {
        if ((memcmp(&hid_report, &old_hid_report, sizeof(hid_report)) != 0) &&
             tud_hid_report(REPORT_ID_JOYSTICK, &hid_report, sizeof(hid_report))) {
            old_hid_report = hid_report;
        }
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

        sleep_until(next_frame);
        next_frame += 1000;
    }
}

/* if certain key pressed when booting, enter update mode */
static void update_check()
{
    const uint8_t pins[] = BUTTON_DEF;
    // AUX 1 and AUX 2
    for (int i = 0; i < count_of(pins); i++) {
        uint8_t gpio = pins[i];
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
    save_init(0xca44cabe, &core1_io_lock);

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

}
