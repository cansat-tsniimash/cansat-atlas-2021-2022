#include <stdbool.h>
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include "motor.h"
#include "triggers.h"
#include "config.h"

typedef enum//ОПИСЫВАЕМ СОСТОЯНИЕ ПОЛЕТА
{
	STATE_ON_GROUND,
	STATE_IN_RN,
	STATE_AFTER_SEPARATION,
	STATE_MINOR_DEVICE_SEPARATION,
	STATE_SEPARATED
}state_t;

int app_main()
{
	 uint32_t start_time = 0;
	 state_t state_now = STATE_ON_GROUND;
	 motor_on();
	 while(1)
	 {
		 switch (state_now)
		 {
		 case STATE_ON_GROUND:
			 if (check_out_board_trigger() == true)
			 {
				 state_now = STATE_IN_RN;
			 }
			 break;
		 case STATE_IN_RN:
			 //добавит ожидание освещенности
			 state_now = STATE_AFTER_SEPARATION;
		 	 break;
		 case STATE_AFTER_SEPARATION:
			 //ждем достижения восыты
			 state_now = STATE_MINOR_DEVICE_SEPARATION;
			 break;
		 case STATE_MINOR_DEVICE_SEPARATION:
             motor_on();
             start_time = HAL_GetTick();
			 if (check_out_motor_trigger() == true || (HAL_GetTick() - start_time) > MOTOR_TIMEOUT)
			 {
				 motor_off();
				 state_now = STATE_SEPARATED;
			 }
			 break;
		 case STATE_SEPARATED:
			 //общение с ДА
             break;
		 }
	 }
	 return 0;
}


