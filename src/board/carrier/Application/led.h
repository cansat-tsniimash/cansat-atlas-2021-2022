#ifndef LED_H_
#define LED_H_
#include "Shift_Register/shift_reg.h"

void led_nrf_on (shift_reg_t *this, uint8_t pos, bool state);
void led_nrf_off (shift_reg_t *this, uint8_t pos, bool state);
void led_nrf_change(shift_reg_t *this, uint8_t pos, bool state);

void led_sens_on (shift_reg_t *this, uint8_t pos, bool state);
void led_sens_off (shift_reg_t *this, uint8_t pos, bool state);
void led_sens_change(shift_reg_t *this, uint8_t pos, bool state);
#endif /* LED_H_ */
