/*
 * Hall Effect Button Reader
 * WHowe <github.com/whowechina>
 */

#ifndef HALL_H
#define HALL_H

void hall_init();
void hall_update();

bool hall_is_present(uint8_t chn);
uint16_t hall_raw(uint8_t chn);

uint8_t hall_keynum();
bool hall_key_actuated(uint8_t chn);
uint16_t hall_key_range(uint8_t chn);
uint16_t hall_key_travel(uint8_t chn);
uint8_t hall_key_travel_byte(uint8_t chn);

void hall_calibrate();

#endif
