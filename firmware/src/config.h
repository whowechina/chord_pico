/*
 * Controller Config
 * WHowe <github.com/whowechina>
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t rgb_hsv; // 0: RGB, 1: HSV
    uint8_t val[3]; // RGB or HSV
} rgb_hsv_t;

typedef struct __attribute__((packed)) {
    struct {
        uint16_t up[12];
        uint16_t down[12];
        uint16_t fader[4];
    } calibrated;
    struct {
        uint8_t on[12];
        uint8_t off[12];
    } trigger;
    struct {
        bool reversed[2];
        uint8_t not_used[7];
    } fader;
    struct {
        rgb_hsv_t colors[12];
        uint8_t level;
        uint8_t not_used[15];
    } light;
} chord_cfg_t;

typedef struct {
    struct {
        bool sensor;
        bool velocity;
    } debug;
} chord_runtime_t;

extern chord_cfg_t *chord_cfg;
extern chord_runtime_t chord_runtime;

void config_init();
void config_changed(); // Notify the config has changed
void config_factory_reset(); // Reset the config to factory default

#endif
