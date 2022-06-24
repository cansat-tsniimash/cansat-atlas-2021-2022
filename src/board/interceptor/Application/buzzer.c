#include <stm32f1xx_hal.h>
#include "buzzer.h"

#define BZR_PORT GPIOB
#define BZR_PIN GPIO_PIN_1

void bzr_on ()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1,  GPIO_PIN_SET);
}

void bzr_off ()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1,  GPIO_PIN_RESET);
}
