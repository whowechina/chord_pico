/*
 * Controller Config and Runtime Data
 * WHowe <github.com/whowechina>
 * 
 * Config is a global data structure that stores all the configuration
 * Runtime is something to share between files.
 */

#include "config.h"
#include "save.h"

chord_cfg_t *chord_cfg;

static chord_cfg_t default_cfg = {
    .fader = {
    },
    .light = {
        .level_fader = 160,
        .level_key = 96,
    },
};

chord_runtime_t chord_runtime;

static void config_loaded()
{
    for (int i = 0; i < 6; i++) {
        if (chord_cfg->trigger.on[i] > 35) {
            chord_cfg->trigger.on[i] = 35;
        }
        if (chord_cfg->trigger.off[i] > 35) {
            chord_cfg->trigger.off[i] = 35;
        }
    }

    config_changed();
}

void config_changed()
{
    save_request(false);
}

void config_factory_reset()
{
    *chord_cfg = default_cfg;
    save_request(true);
}

void config_init()
{
    chord_cfg = (chord_cfg_t *)save_alloc(sizeof(*chord_cfg), &default_cfg, config_loaded);
}
