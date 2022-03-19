#include <stdbool.h>
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include "motor.h"
#include "triggers.h"
#include "config.h"
#include "nRF24L01_PL/nrf24_upper_api.h"
#include "nRF24L01_PL/nrf24_lower_api_stm32.h"

extern SPI_HandleTypeDef hspi2;

typedef enum//ОПИСЫВАЕМ СОСТОЯНИЕ ПОЛЕТА
{
	STATE_ON_GROUND,
	STATE_IN_RN,
	STATE_AFTER_SEPARATION,
	STATE_MINOR_DEVICE_SEPARATION,
	STATE_SEPARATED
}state_t;

#pragma pack(push,1)
typedef struct
{
	uint8_t flag;
	uint16_t num;
	uint32_t time;

	uint32_t BME280_presqure;
	uint8_t BME280_temperature;
	uint16_t BME280_humidity;

	uint8_t DS18B20_temperature;
	int16_t LSM6DSL_accelerometer_x;
	int16_t LSM6DSL_accelerometer_y;
	int16_t LSM6DSL_accelerometer_z;

	int16_t LSM6DSL_gyroscope_x;
	int16_t LSM6DSL_gyroscope_y;
	int16_t LSM6DSL_gyroscope_z;

	uint16_t sum;

}packet_ma_type_1_t;


typedef struct
{
	uint8_t flag;
	uint16_t num;
	uint32_t time;

    int16_t LIS3MDL_magnetometer_x;
    int16_t LIS3MDL_magnetometer_y;
    int16_t LIS3MDL_magnetometer_z;

    float latitude;
    float longitude;
    int16_t height;
    uint8_t fix;

    uint8_t state;

	uint16_t sum;
}packet_ma_type_2_t;
#pragma pack(pop)

int app_main()
{
	packet_ma_type_1_t packet_ma_type_1 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	packet_ma_type_2_t packet_ma_type_2 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	packet_ma_type_1.flag = 0xff;
	packet_ma_type_2.flag = 0xfe;

	nrf24_lower_api_config_t nrf24_api_config;
	nrf24_api_config.hspi = &hspi2;
	nrf24_api_config.ce_port = GPIOA;
	nrf24_api_config.ce_pin = GPIO_PIN_1;
	nrf24_api_config.cs_port = GPIOA;
	nrf24_api_config.cs_pin = GPIO_PIN_0;
	// Настройки радиопередачи
	nrf24_rf_config_t nrf24_rf_config;
	nrf24_rf_config.data_rate = NRF24_DATARATE_2000_KBIT;
	nrf24_rf_config.rf_channel = 25;
	nrf24_rf_config.tx_power = NRF24_TXPOWER_MINUS_0_DBM;
	nrf24_setup_rf(&nrf24_api_config, &nrf24_rf_config);

	// Настроили протокол
	nrf24_protocol_config_t nrf24_protocol_config;
	nrf24_protocol_config.address_width = NRF24_ADDRES_WIDTH_5_BYTES;
	nrf24_protocol_config.auto_retransmit_count = 15;
	nrf24_protocol_config.auto_retransmit_delay = 15;
	nrf24_protocol_config.crc_size = NRF24_CRCSIZE_1BYTE;
	nrf24_protocol_config.en_ack_payload = true;
	nrf24_protocol_config.en_dyn_ack = true;
	nrf24_protocol_config.en_dyn_payload_size = true;
	nrf24_setup_protocol(&nrf24_api_config, &nrf24_protocol_config);

	nrf24_pipe_set_tx_addr(&nrf24_api_config, 0xacacacacac);

	nrf24_pipe_config_t pipe_config;
	pipe_config.address = 0xacacacacac;
	pipe_config.enable_auto_ack = true;
	pipe_config.payload_size = -1;
	nrf24_pipe_rx_start(&nrf24_api_config, 0, &pipe_config);

	nrf24_mode_standby(&nrf24_api_config);
	nrf24_mode_tx(&nrf24_api_config);

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
	    nrf24_fifo_write(&nrf24_api_config, (uint8_t *)&packet_ma_type_1, sizeof(packet_ma_type_1), false);
	    nrf24_fifo_write(&nrf24_api_config, (uint8_t *)&packet_ma_type_2, sizeof(packet_ma_type_2), false);

		nrf24_irq_clear(&nrf24_api_config, NRF24_IRQ_RX_DR | NRF24_IRQ_TX_DR | NRF24_IRQ_MAX_RT);


	}
	return 0;
}


