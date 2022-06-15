#include <stm32f4xx_hal.h>
#include <stdbool.h>

#define MOTOR_TRIGGER_PORT GPIOA
#define MOTOR_TRIGGER_PIN GPIO_PIN_5

#define BOARD_TRIGGER_PORT GPIOA
#define BOARD_TRIGGER_PIN GPIO_PIN_6

bool check_out_motor_trigger()
{
	if(HAL_GPIO_ReadPin(MOTOR_TRIGGER_PORT, MOTOR_TRIGGER_PIN) == GPIO_PIN_RESET)
		return true;
	else
		return false;
}


bool check_out_board_trigger()
{
	if(HAL_GPIO_ReadPin(BOARD_TRIGGER_PORT, BOARD_TRIGGER_PIN) == GPIO_PIN_RESET)
		return true;
	else
		return false;
}
