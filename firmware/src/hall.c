/*
 * Hall Effect Button Reader
 * WHowe <github.com/whowechina>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "hall.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "board_defs.h"

#include "config.h"

static const uint8_t key_map[] = HALL_KEY_MAP;

#define HALL_KEY_NUM count_of(key_map)

static bool hall_present[HALL_KEY_NUM];
static uint16_t reading[HALL_KEY_NUM];
bool key_actuated[HALL_KEY_NUM];

static void hall_discovery()
{
    hall_update();
    for (int i = 0; i < HALL_KEY_NUM; i++) {
        hall_present[i] = (reading[i] > 200);
    }
}

bool hall_is_present(uint8_t key)
{
    if (key >= HALL_KEY_NUM) {
        return false;
    }
    return hall_present[key];
}

uint16_t hall_raw(uint8_t key)
{
    if (key >= HALL_KEY_NUM) {
        return 0;
    }
    return reading[key];
}

void hall_init()
{
    gpio_init(ADC_MUX_EN);
    gpio_init(ADC_MUX_A0);
    gpio_init(ADC_MUX_A1);
    gpio_init(ADC_MUX_A2);
    gpio_init(ADC_MUX_A3);
    gpio_set_dir(ADC_MUX_EN, GPIO_OUT);
    gpio_set_dir(ADC_MUX_A0, GPIO_OUT);
    gpio_set_dir(ADC_MUX_A1, GPIO_OUT);
    gpio_set_dir(ADC_MUX_A2, GPIO_OUT);
    gpio_set_dir(ADC_MUX_A3, GPIO_OUT);
    gpio_put(ADC_MUX_EN, 1);
    gpio_put(ADC_MUX_A0, 0);
    gpio_put(ADC_MUX_A1, 0);
    gpio_put(ADC_MUX_A2, 0);
    gpio_put(ADC_MUX_A3, 0);

    adc_init();
    adc_gpio_init(26 + ADC_CHANNEL);
    adc_select_input(ADC_CHANNEL);
    gpio_pull_down(26 + ADC_CHANNEL);

    // pwm mode for lower power ripple
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
    gpio_put(25, 1);

    hall_discovery();
}

uint8_t hall_keynum()
{
    return HALL_KEY_NUM;
}

static inline void select_channel(int chn)
{
    uint8_t mask = key_map[chn];
    gpio_put(ADC_MUX_A0, mask & 1);
    gpio_put(ADC_MUX_A1, mask & 2);
    gpio_put(ADC_MUX_A2, mask & 4);
    gpio_put(ADC_MUX_A3, mask & 8);
}

static inline uint16_t read_avg(int count)
{
    uint32_t sum = 0;
    for (int i = 0; i < count; i++) {
        sum += adc_read();
    }
    return sum / count;
}

static void read_sensor(int chn, int avg)
{
    reading[chn] = read_avg(avg);
    if (chord_runtime.debug.hall) {
        if (chn == 0) {
            printf("\n");
        }
        printf(" %d:%4d,", chn, reading[chn]);
    }
}

static void do_triggering()
{
    for (int i = 0; i < HALL_KEY_NUM; i++) {
        int travel = hall_key_travel(i);

        int on_trig = chord_cfg->trigger.on[i] % 36 + 1;
        on_trig = on_trig * hall_key_range(i) / 37;

        int off_trig = (35 - chord_cfg->trigger.off[i] % 36) + 1;
        off_trig = off_trig * on_trig / 38; // 38 for just a bit more dead zone

        key_actuated[i] = key_actuated[i] ? (travel > off_trig)
                                          : (travel >= on_trig);
    }
}

void hall_update()
{
    for (int i = 0; i < HALL_KEY_NUM; i++) {
        select_channel(i);
        sleep_us(5);
        read_sensor(i, 16);
    }

    do_triggering();
}

bool hall_key_actuated(uint8_t key)
{
    if (key >= HALL_KEY_NUM) {
        return false;
    }
    return key_actuated[key];
}

uint16_t hall_key_range(uint8_t key)
{
    if (key >= HALL_KEY_NUM) {
        return 0;
    }
    return abs(chord_cfg->calibrated.down[key] - chord_cfg->calibrated.up[key]);
}

uint16_t hall_key_travel(uint8_t key)
{
    if (key >= HALL_KEY_NUM) {
        return 0;
    }

    int up = chord_cfg->calibrated.up[key];
    int down = chord_cfg->calibrated.down[key];
    int range = down - up;
    int travel = reading[key] - up;
    if (range < 0) {
        travel = -travel;
        range = -range;
    }

    if (travel < 8) { // extra start-up dead zone
        travel = 0;
    } else if (travel > range) {
        travel = range;
    }

    return travel;
}

uint8_t hall_key_travel_byte(uint8_t key)
{
    if (key >= HALL_KEY_NUM) {
        return 0;
    }

    int range = hall_key_range(key);
    int pos = hall_key_travel(key);
    return (range != 0) ? pos * 255 / range : 0;
}

static void read_sensors_avg(uint16_t avg[HALL_KEY_NUM])
{
    const int avg_count = 200;
    uint32_t sum[HALL_KEY_NUM] = {0};

    for (int i = 0; i < avg_count; i++) {
        for (int j = 0; j < HALL_KEY_NUM; j++) {
            select_channel(j);
            sleep_us(5);
            read_sensor(j, 32);
            sum[j] += reading[j];
        }
    }
    for (int i = 0; i < HALL_KEY_NUM; i++) {
        avg[i] = sum[i] / avg_count;
    }
}

void hall_calibrate()
{
    printf("Calibrating key RELEASED...\n");

    uint16_t up_val[HALL_KEY_NUM] = {0};
    read_sensors_avg(up_val);

    printf("Calibrating key PRESSED...\n");
    printf("Please press all keys down, not necessarily simultaneously.\n");

    uint16_t min[HALL_KEY_NUM] = {0};
    uint16_t max[HALL_KEY_NUM] = {0};
    for (int i = 0; i < HALL_KEY_NUM; i++) {
        min[i] = up_val[i];
        max[i] = up_val[i];
    }
    uint64_t stop = time_us_64() + 10000000;
    while (time_us_64() < stop) {
        hall_update();
        for (int i = 0; i < HALL_KEY_NUM; i++) {
            int val = hall_raw(i);
            if (val < min[i]) {
                min[i] = val;
            }
            if (val > max[i]) {
                max[i] = val;
            }
        }
    }

    uint16_t down_val[HALL_KEY_NUM] = {0};
    bool success = true;
    for (int i = 0; i < HALL_KEY_NUM; i++) {

        int trim = (max[i] - min[i]) / 50; // 2% dead zone at two sides
        max[i] -= trim;
        min[i] += trim;

        bool max_is_down = abs(max[i] - up_val[i]) > abs(min[i] - up_val[i]);
        down_val[i] = max_is_down ? max[i] : min[i];
        up_val[i] = max_is_down ? min[i] : max[i];
        if (abs(down_val[i] - up_val[i]) < 300) {
            printf("Key %d calibration failed. [%4d->%4d].\n",
                   i + 1, up_val[i], down_val[i]);
            success = false;
        }
    }

    printf("Calibration %s.\n", success ? "succeeded" : "failed");

    if (!success) {
        return;
    }

    for (int i = 0; i < HALL_KEY_NUM; i++) {
        chord_cfg->calibrated.up[i] = up_val[i];
        chord_cfg->calibrated.down[i] = down_val[i];
        printf("Key %d: %4d -> %4d.\n", i + 1, up_val[i], down_val[i]);
    }

    config_changed();
}