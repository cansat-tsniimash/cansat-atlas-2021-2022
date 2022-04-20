/*
 * app_main.c
 *
 *  Created on: Mar 19, 2022
 *      Author: 1
 */

#include "nRF24L01_PL/nrf24_upper_api.h"
#include "nRF24L01_PL/nrf24_lower_api_stm32.h"
#include "ATGM336H/nmea_gps.h"
#include <math.h>
#include "BME280/DriverForBME280.h"

extern UART_HandleTypeDef huart3;

extern SPI_HandleTypeDef hspi1;

#pragma pack(push,1)
typedef struct
{
	uint8_t flag;
	uint16_t num;
	uint32_t time;

	uint32_t BME280_pressure;
	uint8_t BME280_temperature;
	uint16_t BME280_humidity;

	int16_t LSM6DSL_accelerometer_x;
	int16_t LSM6DSL_accelerometer_y;
	int16_t LSM6DSL_accelerometer_z;

	int16_t LSM6DSL_gyroscope_x;
	int16_t LSM6DSL_gyroscope_y;
	int16_t LSM6DSL_gyroscope_z;

	uint16_t sum;

}packet_da_type_1_t;


typedef struct
{
	uint8_t flag;
	uint16_t num;
	uint32_t time;

    float latitude;
    float longitude;
    float height;
    uint8_t fix;

    uint8_t state;

	uint16_t sum;
}packet_da_type_2_t;
#pragma pack(pop)



int app_main()
{
	//берем изначальное давление для барометрической формулы
	uint32_t pressure_on_ground;

	float height_BME280 = 0;
	struct bme280_dev bme = {0};	//инициализируем настройки бме280
	struct bme_spi_intf bme280_buffer;
	bme280_buffer.GPIO_Port = GPIOC;
	bme280_buffer.GPIO_Pin = GPIO_PIN_13;
	bme280_buffer.spi =  &hspi1;
	bme_init_default(&bme, &bme280_buffer);


	//инициализация гпс
	gps_init();
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);

	//создаем структуру пакетов
	packet_da_type_1_t packet_da_type_1 = {0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0};
	packet_da_type_2_t packet_da_type_2 = {0, 2, 0, 4, 0, 6, 0, 8, 0};

	//поднимаем флаги для определения пакетов
	packet_da_type_1.flag = 0xfa;
	packet_da_type_2.flag = 0xfb;

	nrf24_lower_api_config_t nrf24_api_config;
	nrf24_api_config.hspi = &hspi1;
	nrf24_api_config.ce_port = GPIOA;
	nrf24_api_config.ce_pin = GPIO_PIN_10;
	nrf24_api_config.cs_pin = GPIO_PIN_15;
	nrf24_api_config.cs_port = GPIOC;

	nrf24_mode_power_down(&nrf24_api_config);

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

	//настройка пайпа(штука , чтобы принимать)
	nrf24_pipe_config_t pipe_config;
	pipe_config.address = 0xafafafaf01;
	pipe_config.enable_auto_ack = true;
	pipe_config.payload_size = -1;
	nrf24_pipe_rx_start(&nrf24_api_config, 0, &pipe_config);

	nrf24_mode_standby(&nrf24_api_config);

	uint8_t rx_buffer[32];

	nrf24_fifo_status_t rx_status = 0;
    nrf24_fifo_status_t tx_status = 0;
	nrf24_mode_rx(&nrf24_api_config);

	int64_t cookie;
	struct bme280_data comp_data = {0};
	comp_data = bme_read_data(&bme);
	pressure_on_ground = (float)comp_data.pressure;

	float height_on_BME280 = 0;
	while(true)
	{

		comp_data = bme_read_data(&bme);
		packet_da_type_1.BME280_pressure = comp_data.pressure;
		packet_da_type_1.BME280_temperature = comp_data.temperature;
		packet_da_type_1.BME280_humidity = comp_data.humidity;

		height_on_BME280 = 44330*(1 - pow((float)packet_da_type_1.BME280_pressure/pressure_on_ground, 1.0/5.255));

		printf("высота %ld\n ",(int32_t)(height_on_BME280*100));
		printf("давл %ld\n ",(int32_t)packet_da_type_1.BME280_pressure);
		printf("темп %ld\n ",(int32_t)packet_da_type_1.BME280_temperature);
		printf("влажность %ld\n ",(int32_t)packet_da_type_1.BME280_humidity);

		gps_work();
		gps_get_coords(&cookie, &packet_da_type_2.latitude, &packet_da_type_2.longitude, &packet_da_type_2.height);


		nrf24_fifo_status(&nrf24_api_config, &rx_status, &tx_status);

		if (rx_status != NRF24_FIFO_EMPTY)
		{
			nrf24_fifo_read(&nrf24_api_config, rx_buffer, 32);
		}

        if (tx_status != NRF24_FIFO_EMPTY)
        {
    	    //nrf24_fifo_flush_tx(&nrf24_api_config);
        }
        nrf24_fifo_write_ack_pld(&nrf24_api_config, 0,(uint8_t *)&packet_da_type_1, sizeof(packet_da_type_1));
        nrf24_fifo_write_ack_pld(&nrf24_api_config, 0,(uint8_t *)&packet_da_type_2, sizeof(packet_da_type_2));

        //опускаем флаги
        nrf24_irq_clear(&nrf24_api_config, NRF24_IRQ_RX_DR | NRF24_IRQ_TX_DR | NRF24_IRQ_MAX_RT);

    }
	return 0;
}
