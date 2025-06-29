/*
 * Voltex Controller Board Definitions
 * WHowe <github.com/whowechina>
 */

#if defined BOARD_CHORD_PICO

#define RGB_PIN_KEY 0
#define RGB_PIN_FADER 1

#define RGB_ORDER GRB // or RGB

 /* BT * 4, FX * 2, START, AUX * 2 */
#define BUTTON_DEF { 14, 15 }

#define ADC_MUX_EN 21
#define ADC_MUX_A0 20
#define ADC_MUX_A1 19
#define ADC_MUX_A2 18
#define ADC_MUX_A3 17

#define ADC_CHANNEL 0

/* 12 for keys + 4 for faders */
#define HALL_CHN_MAP { 5, 4, 3, 2, 1, 0, 8, 9, 10, 11, 12, 13, 6, 7, 15, 14 }
#define HALL_KEY_NUM 12


#endif
