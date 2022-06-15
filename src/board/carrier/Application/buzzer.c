#include <stm32f4xx_hal.h>

#define BZR_PORT GPIOB
#define BZR_PIN GPIO_PIN_10

void bzr_on ()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,  GPIO_PIN_SET);
}

void bzr_off ()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,  GPIO_PIN_RESET);
}
