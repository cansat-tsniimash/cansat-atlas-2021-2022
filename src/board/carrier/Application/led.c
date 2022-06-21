#include <stm32f4xx_hal.h>
#include "Shift_Register/shift_reg.h"
#include "led.h"



void led_nrf_on (shift_reg_t *this, uint8_t pos, bool state)
{
	shift_reg_write_bit_8(this, pos, true);
}

void led_nrf_off (shift_reg_t *this, uint8_t pos, bool state)
{
	shift_reg_write_bit_8(this, pos, false);
}

void led_nrf_change(shift_reg_t *this, uint8_t pos, bool state)
{
	if((this->value & (1 << pos)) == 0) shift_reg_write_bit_8(this, pos, true);
	else shift_reg_write_bit_8(this, pos, false);
}



void led_sens_on (shift_reg_t *this, uint8_t pos, bool state)
{
	shift_reg_write_bit_16(this, pos, true);
}

void led_sens_off (shift_reg_t *this, uint8_t pos, bool state)
{
	shift_reg_write_bit_16(this, pos, false);
}

void led_sens_change(shift_reg_t *this, uint8_t pos, bool state)
{
	if((this->value & (1 << pos)) == 0) shift_reg_write_bit_16(this, pos, true);
	else shift_reg_write_bit_16(this, pos, false);
}
