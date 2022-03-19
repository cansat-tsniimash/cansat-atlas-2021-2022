#include <stm32f4xx_hal.h>

#define MOTOR_PORT GPIOB
#define MOTOR_PIN GPIO_PIN_4

void motor_on ()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);
}

void motor_off ()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);
}
