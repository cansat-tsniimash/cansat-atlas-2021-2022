/*
 * app_main.c
 *
 *  Created on: Mar 19, 2022
 *      Author: 1
 */

#include "nRF24L01_PL/nrf24_upper_api.h"
#include "nRF24L01_PL/nrf24_lower_api_stm32.h"

extern SPI_HandleTypeDef hspi1;


int app_main()
{
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

	nrf24_fifo_status_t rx_status = 0;
    nrf24_fifo_status_t tx_status = 0;
	nrf24_mode_rx(&nrf24_api_config);
	while(true)
	{
		nrf24_fifo_status(&nrf24_api_config, &rx_status, &tx_status);

		if (rx_status != NRF24_FIFO_EMPTY)
		{

		}

    }
	return 0;
}

