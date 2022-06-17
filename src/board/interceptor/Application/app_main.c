/*
 * app_main.c
 *
 *  Created on: Mar 19, 2022
 *      Author: 1
 */
#include <stdbool.h>
#include "nRF24L01_PL/nrf24_upper_api.h"
#include "nRF24L01_PL/nrf24_lower_api_stm32.h"
#include "nRF24L01_PL/nrf24_defs.h"
#include "ATGM336H/nmea_gps.h"
#include <math.h>
#include "BME280/DriverForBME280.h"
#include "../stm32f1/LSM6DS3/DLSM.h"
#include "fatfs.h"

#define ROLE false

extern UART_HandleTypeDef huart3;

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

typedef struct reg_param_t
{
	uint8_t addr;
	const char * name;
	uint8_t size;
} reg_param_t;

static reg_param_t reg_params[] = {
	{ NRF24_REGADDR_CONFIG, "NRF24_REGADDR_CONFIG",			1},
	{ NRF24_REGADDR_EN_AA, "NRF24_REGADDR_EN_AA",				1},
	{ NRF24_REGADDR_EN_RXADDR, "NRF24_REGADDR_EN_RXADDR",		1},
	{ NRF24_REGADDR_SETUP_AW, "NRF24_REGADDR_SETUP_AW",		1},
	{ NRF24_REGADDR_SETUP_RETR, "NRF24_REGADDR_SETUP_RETR",	1},
	{ NRF24_REGADDR_RF_CH, "NRF24_REGADDR_RF_CH",				1},
	{ NRF24_REGADDR_RF_SETUP, "NRF24_REGADDR_RF_SETUP",		1},
	{ NRF24_REGADDR_STATUS, "NRF24_REGADDR_STATUS",			1},
	{ NRF24_REGADDR_OBSERVE_TX, "NRF24_REGADDR_OBSERVE_TX",	1},
	{ NRF24_REGADDR_RPD, "NRF24_REGADDR_RPD",					1},
	{ NRF24_REGADDR_RX_ADDR_P0, "NRF24_REGADDR_RX_ADDR_P0",	5},
	{ NRF24_REGADDR_RX_ADDR_P1, "NRF24_REGADDR_RX_ADDR_P1",	5},
	{ NRF24_REGADDR_RX_ADDR_P2, "NRF24_REGADDR_RX_ADDR_P2",	1},
	{ NRF24_REGADDR_RX_ADDR_P3, "NRF24_REGADDR_RX_ADDR_P3",	1},
	{ NRF24_REGADDR_RX_ADDR_P4, "NRF24_REGADDR_RX_ADDR_P4",	1},
	{ NRF24_REGADDR_RX_ADDR_P5, "NRF24_REGADDR_RX_ADDR_P5",	1},
	{ NRF24_REGADDR_TX_ADDR, "NRF24_REGADDR_TX_ADDR",			5},
	{ NRF24_REGADDR_RX_PW_P0, "NRF24_REGADDR_RX_PW_P0",		1},
	{ NRF24_REGADDR_RX_PW_P1, "NRF24_REGADDR_RX_PW_P1",		1},
	{ NRF24_REGADDR_RX_PW_P2, "NRF24_REGADDR_RX_PW_P2",		1},
	{ NRF24_REGADDR_RX_PW_P3, "NRF24_REGADDR_RX_PW_P3",		1},
	{ NRF24_REGADDR_RX_PW_P4, "NRF24_REGADDR_RX_PW_P4",		1},
	{ NRF24_REGADDR_RX_PW_P5, "NRF24_REGADDR_RX_PW_P5",		1},
	{ NRF24_REGADDR_FIFO_STATUS, "NRF24_REGADDR_FIFO_STATUS", 1},
	{ NRF24_REGADDR_DYNPD, "NRF24_REGADDR_DYNPD",				1},
	{ NRF24_REGADDR_FEATURE, "NRF24_REGADDR_FEATURE",			1}
};
//static


#pragma pack(push,1)
typedef struct
{
	uint8_t flag;
	uint16_t num;
	uint32_t time;

	uint32_t BME280_pressure;
	uint8_t BME280_temperature;
	uint16_t BME280_humidity;

	int16_t LSM6DSL_accelerometer[3];

	int16_t LSM6DSL_gyroscope[3];

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

void print_bits(uint8_t value, char * buffer)
{
	for (size_t i = 0; i < sizeof(value)*8; i++)
	{
		int bit = value & (0x01 << 7);
		sprintf(buffer, "%d", bit ? 1 : 0);
		value = value << 1;
		buffer += 1;
	}
}

static void print_register(uint8_t reg_addr, uint8_t * reg_data, char * buffer, size_t buffer_size)
{
	reg_param_t * selected_param = NULL;
	for (size_t i = 0; i < sizeof(reg_params)/sizeof(reg_params[0]); i++)
	{
		if (reg_addr == reg_params[i].addr)
		{
			selected_param  = &reg_params[i];
			break;
		}
	}

	if (NULL == selected_param)
	{
		int written = snprintf(buffer, buffer_size, "invalid reg addr: %d\n", reg_addr);
		buffer += written;
		buffer_size -= written;
		return;
	}

	const char * reg_name = selected_param->name;
	const size_t reg_size = selected_param->size;

	int written = snprintf(buffer, buffer_size, "reg %s (0x%02X) = ", reg_name, (int)reg_addr);
	buffer += written;
	buffer_size -= written;
	if (1 == reg_size)
	{
		int written = snprintf(buffer, buffer_size, "0x%02X", reg_data[0]);
		buffer += written;
		buffer_size -= written;

		char bits_buffer[10] = {0};
		print_bits(reg_data[0], bits_buffer);
		written = snprintf(buffer, buffer_size, " (0b%s)", bits_buffer);
		buffer += written;
		buffer_size -= written;
	}
	else
	{
		written = snprintf(buffer, buffer_size, "0x");
		buffer += written;
		buffer_size -= written;

		for (size_t j = 0; j < reg_size; j++)
		{
			int written = snprintf(buffer, buffer_size, "%02X", reg_data[j]);
			buffer += written;
			buffer_size -= written;
		}
	}
	printf("\n");
}

static char buffers[sizeof(reg_params)/sizeof(*reg_params)][50];

static void dump_registers(void *intf_ptr)
{
	const size_t regs_count = sizeof(reg_params)/sizeof(reg_params[0]);
	for (size_t i = 0 ; i < regs_count; i++)
	{
		uint8_t reg_addr = reg_params[i].addr;
		uint8_t reg_size = reg_params[i].size;

		uint8_t reg_data[5] = { 0 };
		buffers[i][0] = 0;
		nrf24_read_register(intf_ptr, reg_addr, reg_data, reg_size);

		print_register(reg_addr, reg_data, buffers[i], sizeof(buffers[i]) / sizeof(buffers[i][0]));
	}

	volatile int x = 0;
}

unsigned short Crc16(unsigned char *buf, unsigned short len) {
	unsigned short crc = 0xFFFF;
	unsigned char i;
	while (len--) {
		crc ^= *buf++ << 8;
		for (i = 0; i < 8; i++)
			crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
	}
	return crc;
}

int app_main()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);

	nrf24_spi_pins_t nrf24_spi_pins;
	nrf24_spi_pins.ce_port = GPIOA;
	nrf24_spi_pins.ce_pin = GPIO_PIN_8;
	nrf24_spi_pins.cs_pin = GPIO_PIN_15;
	nrf24_spi_pins.cs_port = GPIOC;

	nrf24_lower_api_config_t nrf24_lower_api_config;

	nrf24_spi_init(&nrf24_lower_api_config, &hspi1, &nrf24_spi_pins);

	nrf24_mode_power_down(&nrf24_lower_api_config);

	// Настройки радиопередачи
	nrf24_rf_config_t nrf24_rf_config;
	nrf24_rf_config.data_rate = NRF24_DATARATE_250_KBIT;
	nrf24_rf_config.rf_channel = 100;
	nrf24_rf_config.tx_power = NRF24_TXPOWER_MINUS_6_DBM;
	nrf24_setup_rf(&nrf24_lower_api_config, &nrf24_rf_config);

	// Настроили протокол
	nrf24_protocol_config_t nrf24_protocol_config;
	nrf24_protocol_config.address_width = NRF24_ADDRES_WIDTH_5_BYTES;
	nrf24_protocol_config.auto_retransmit_count = 15;
	nrf24_protocol_config.auto_retransmit_delay = 15;
	nrf24_protocol_config.crc_size = NRF24_CRCSIZE_1BYTE;
	nrf24_protocol_config.en_ack_payload = true;
	nrf24_protocol_config.en_dyn_ack = false;
	nrf24_protocol_config.en_dyn_payload_size = false;
	nrf24_setup_protocol(&nrf24_lower_api_config, &nrf24_protocol_config);

	//настройка пайпа(штука , чтобы принимать)
	nrf24_pipe_config_t pipe_config;
	pipe_config.address = 0xafafafaf01;
	pipe_config.enable_auto_ack = true;
	pipe_config.payload_size = 32;
	nrf24_pipe_rx_start(&nrf24_lower_api_config, 0, &pipe_config);

	for (int i = 1; i < 6; i++)
	{
		pipe_config.address = 0xcfcfcfcfcf;
		pipe_config.address = (pipe_config.address & ~((uint64_t)0xff << 32)) | ((uint64_t)i << 32);
		pipe_config.enable_auto_ack = true;
		pipe_config.payload_size = 32;
		nrf24_pipe_rx_start(&nrf24_lower_api_config, i, &pipe_config);
	}

	nrf24_pipe_set_tx_addr(&nrf24_lower_api_config, 0xafafafaf01);

	nrf24_mode_standby(&nrf24_lower_api_config);

	uint8_t rx_buffer[32] = {0};
	uint8_t tx_buffer[32] = "Kto tuta";
	uint8_t tx_ack_pl_buffer[32] = "Ya DA1, vosraduysya Artem";

	nrf24_fifo_status_t rx_status = 0;
    nrf24_fifo_status_t tx_status = 0;
    if (ROLE)
    {

		nrf24_fifo_flush_tx(&nrf24_lower_api_config);
		nrf24_fifo_flush_rx(&nrf24_lower_api_config);
		//nrf24_fifo_write(&nrf24_lower_api_config ,(uint8_t *)&tx_buffer, sizeof(tx_buffer), true);
    }
    else
    {
    	nrf24_mode_rx(&nrf24_lower_api_config);
		nrf24_fifo_flush_tx(&nrf24_lower_api_config);
		nrf24_fifo_flush_rx(&nrf24_lower_api_config);
		nrf24_fifo_write_ack_pld(&nrf24_lower_api_config, 0,(uint8_t *)&tx_ack_pl_buffer, 32);//sizeof(tx_ack_pl_buffer));
    }

	while(true)
	{

		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);

		if (ROLE)
		{
			nrf24_mode_tx(&nrf24_lower_api_config);
			HAL_Delay(100);
			nrf24_mode_standby(&nrf24_lower_api_config);
		}

		dump_registers(&nrf24_lower_api_config);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
        nrf24_fifo_status(&nrf24_lower_api_config, &rx_status, &tx_status);
		if (rx_status != NRF24_FIFO_EMPTY)
		{
			uint8_t rx_packet_size;
			uint8_t rx_pipe_no;
			bool tx_full;
			nrf24_fifo_peek(&nrf24_lower_api_config, &rx_packet_size, &rx_pipe_no, &tx_full);
			nrf24_fifo_read(&nrf24_lower_api_config, rx_buffer, 32);
			nrf24_fifo_flush_rx(&nrf24_lower_api_config);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
			HAL_Delay(100);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
		}
        //HAL_Delay(200);
        //nrf24_fifo_write(&nrf24_lower_api_config ,(uint8_t *)&tx_buffer, 32, true);//sizeof(tx_buffer), true);

		int comp = 0;
		nrf24_irq_get(&nrf24_lower_api_config, &comp);
        //опускаем флаги
        nrf24_irq_clear(&nrf24_lower_api_config, comp);
        nrf24_irq_get(&nrf24_lower_api_config, &comp);

    }
	return 0;
}

