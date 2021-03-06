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
#include <stm32f1xx_hal.h>
#include "buzzer.h"
#include "string.h"

#define DA_NUM 2

extern UART_HandleTypeDef huart3;

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern IWDG_HandleTypeDef hiwdg;

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
	uint8_t da_num;
	uint16_t num;
	uint32_t time;

	uint32_t BME280_pressure;
	int16_t BME280_temperature;
	uint16_t BME280_humidity;

	int16_t LSM6DSL_accelerometer[3];

	int16_t LSM6DSL_gyroscope[3];

	uint16_t sum;

}packet_da_type_1_t;


typedef struct
{
	uint8_t flag;
	uint8_t da_num;
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



int super_smart_write(shift_reg_t *this, unsigned char *buf, unsigned short len, int8_t * state_sd_from_m)
{
	while(1)
	{
		static uint32_t start_time;
		static FATFS fileSystem; // ???????????????????? ???????? FATFS
		static FIL testFile; // ?????????????? ??????????
		static UINT bw;
		static FRESULT res;
		static int8_t state_sd = 0;
		const char * path = "testFile.bin"; // ???????????????? ??????????

		if(state_sd == 0)
		{
			extern Disk_drvTypeDef  disk;
			disk.is_initialized[0] = 0;
			memset(&fileSystem, 0x00, sizeof(fileSystem));
			res = f_mount(&fileSystem, "0", 1);
			if(res == FR_OK){state_sd = 1; *state_sd_from_m = state_sd;}
			else
			{
				res = f_mount(0, "0", 1);
				return -1;
			}
		}
		if(state_sd == 1)
		{
			res = f_open(&testFile, path, FA_WRITE | FA_OPEN_ALWAYS);
			f_lseek(&testFile, f_size(&testFile));
			if(res == FR_OK) state_sd = 2;
			else
			{
				state_sd = 0;
				res = f_mount(0, "0", 1);
			}
		}
		if (state_sd == 2)
		{
            res = f_write (&testFile,  (uint8_t *)buf, len, &bw);
            if (HAL_GetTick() - start_time >= 10)
            {
            	res = f_sync(&testFile);
                start_time  = HAL_GetTick();
            }
	        if (res == FR_OK) return 0;
            if (res != FR_OK)
            {
    			res = f_close(&testFile);
            	state_sd = 1;
            }
		}
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
	bzr_off();
    int8_t state_sd = 0;

	//?????????? ?????????????????????? ???????????????? ?????? ?????????????????????????????? ??????????????
	uint32_t pressure_on_ground;


	struct bme280_dev bme = {0};	//???????????????????????????? ?????????????????? ??????280
	struct bme_spi_intf bme280_buffer;
	bme280_buffer.GPIO_Port = GPIOC;
	bme280_buffer.GPIO_Pin = GPIO_PIN_13;
	bme280_buffer.spi =  &hspi1;
	bme_init_default(&bme, &bme280_buffer);

	struct lsm_spi_intf lsm_intf;
	lsm_intf.GPIO_Pin = GPIO_PIN_14;
	lsm_intf.GPIO_Port = GPIOC;
	lsm_intf.spi = &hspi1;

	stmdev_ctx_t stmdev_ctx;
	lsmset(&stmdev_ctx, &lsm_intf);

	//?????????????????????????? ??????
	gps_init();
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);

	//?????????????? ?????????????????? ??????????????
	packet_da_type_1_t packet_da_type_1 = {0};
	packet_da_type_2_t packet_da_type_2 = {0};

	//?????????????????? ?????????? ?????? ?????????????????????? ??????????????
	packet_da_type_1.flag = 0xfa;
	packet_da_type_2.flag = 0xfb;

	packet_da_type_1.da_num = DA_NUM;
	packet_da_type_2.da_num = DA_NUM;

	nrf24_spi_pins_t nrf24_spi_pins;
	nrf24_spi_pins.ce_port = GPIOA;
	nrf24_spi_pins.ce_pin = GPIO_PIN_8;
	nrf24_spi_pins.cs_pin = GPIO_PIN_15;
	nrf24_spi_pins.cs_port = GPIOC;

	nrf24_lower_api_config_t nrf24_lower_api_config;

	nrf24_spi_init(&nrf24_lower_api_config, &hspi1, &nrf24_spi_pins);

	nrf24_mode_power_down(&nrf24_lower_api_config);

	// ?????????????????? ??????????????????????????
	nrf24_rf_config_t nrf24_rf_config;
	nrf24_rf_config.data_rate = NRF24_DATARATE_250_KBIT;
	nrf24_rf_config.rf_channel = 100;
	nrf24_rf_config.tx_power = NRF24_TXPOWER_MINUS_0_DBM;
	nrf24_setup_rf(&nrf24_lower_api_config, &nrf24_rf_config);

	// ?????????????????? ????????????????
	nrf24_protocol_config_t nrf24_protocol_config;
	nrf24_protocol_config.address_width = NRF24_ADDRES_WIDTH_5_BYTES;
	nrf24_protocol_config.auto_retransmit_count = 15;
	nrf24_protocol_config.auto_retransmit_delay = 15;
	nrf24_protocol_config.crc_size = NRF24_CRCSIZE_1BYTE;
	nrf24_protocol_config.en_ack_payload = true;
	nrf24_protocol_config.en_dyn_ack = false;
	nrf24_protocol_config.en_dyn_payload_size = false;
	nrf24_setup_protocol(&nrf24_lower_api_config, &nrf24_protocol_config);

	//?????????????????? ??????????(?????????? , ?????????? ??????????????????)
	nrf24_pipe_config_t pipe_config;
	pipe_config.address = 0xafafafaf01;
	pipe_config.address = (pipe_config.address & ~((uint64_t)0xff)) | ((uint64_t)DA_NUM);
	pipe_config.enable_auto_ack = true;
	pipe_config.payload_size = 32;
	nrf24_pipe_rx_start(&nrf24_lower_api_config, 0, &pipe_config);
	nrf24_pipe_set_tx_addr(&nrf24_lower_api_config, pipe_config.address);

	for (int i = 1; i < 6; i++)
	{
		pipe_config.address = 0xcfcfcfcfcf;
		pipe_config.address = (pipe_config.address & ~((uint64_t)0xff << 32)) | ((uint64_t)(i + 7) << 32);
		pipe_config.enable_auto_ack = true;
		pipe_config.payload_size = 32;
		nrf24_pipe_rx_start(&nrf24_lower_api_config, i, &pipe_config);
	}

	nrf24_mode_standby(&nrf24_lower_api_config);

	uint8_t rx_buffer[32] = {0};
	uint8_t tx_buffer[32] = {0};

	nrf24_fifo_status_t rx_status = 0;
    nrf24_fifo_status_t tx_status = 0;
	nrf24_mode_rx(&nrf24_lower_api_config);

	int64_t cookie = 0;
	struct bme280_data comp_data = {0};
	comp_data = bme_read_data(&bme);
	pressure_on_ground = (float)comp_data.pressure;

	uint32_t time_nrf_start = 0;

	float lat ;
	float lon;
	float alt;
	float temperature_celsius_gyro = 0;
    float acc_g [3];
    float gyro_dps [3];
    uint16_t packet_num_1 = 0;
    uint16_t packet_num_2 = 0;
    int fix2;
    uint32_t counter;
    uint8_t state_height = 0;
    bool radio_flag;

	float height_on_BME280 = 0;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	while(true)
	{
		HAL_IWDG_Refresh(&hiwdg);
		comp_data = bme_read_data(&bme);
		packet_da_type_1.BME280_pressure = (uint32_t)comp_data.pressure;
		packet_da_type_1.BME280_temperature = (int16_t)(comp_data.temperature*100);
		packet_da_type_1.BME280_humidity = (uint16_t)comp_data.humidity;



		height_on_BME280 = 44330*(1 - pow((float)packet_da_type_1.BME280_pressure/pressure_on_ground, 1.0/5.255));

		if (state_height == 0 && height_on_BME280 > 500) state_height = 1;
		counter++;
		if (counter  % 20 == 0) HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);

		dump_registers(&nrf24_lower_api_config);

		if (height_on_BME280 <= 200 && state_height == 1) bzr_on();

		lsmread(&stmdev_ctx, &temperature_celsius_gyro, &acc_g, &gyro_dps);

		for (int i= 0; i < 3 ; i++) packet_da_type_1.LSM6DSL_accelerometer[i] = (int16_t)(acc_g[i]*1000);
		for (int i= 0; i < 3 ; i++) packet_da_type_1. LSM6DSL_gyroscope[i] = (int16_t)(gyro_dps[i]*1000);


		gps_work();
		gps_get_coords(&cookie,  & lat,  & lon,& alt, &fix2);
		packet_da_type_2.latitude = lat;
		packet_da_type_2.longitude = lon;
		packet_da_type_2.height = (int16_t)(alt*100);
		packet_da_type_2.fix = (uint8_t)fix2;

		packet_da_type_1.time = HAL_GetTick();
		packet_da_type_2.time = HAL_GetTick();

		packet_da_type_1.num = packet_num_1;
		packet_da_type_2.num = packet_num_2;
		packet_num_1++;
		packet_num_2++;

		packet_da_type_1.sum = Crc16((uint8_t *)&packet_da_type_1, sizeof(packet_da_type_1) - 2);
		packet_da_type_2.sum = Crc16((uint8_t *)&packet_da_type_2, sizeof(packet_da_type_2) - 2);


       	super_smart_write(0, (uint8_t *)&packet_da_type_1, sizeof(packet_da_type_1), &state_sd);
       	super_smart_write(0, (uint8_t *)&packet_da_type_2, sizeof(packet_da_type_2), &state_sd);




		nrf24_fifo_status(&nrf24_lower_api_config, &rx_status, &tx_status);

		if (rx_status != NRF24_FIFO_EMPTY)
		{
			nrf24_fifo_read(&nrf24_lower_api_config, rx_buffer, 32);
			if (rx_status == NRF24_FIFO_FULL)
			{
				nrf24_fifo_flush_rx(&nrf24_lower_api_config);
			}
		}

		if (tx_status == NRF24_FIFO_EMPTY || HAL_GetTick() - time_nrf_start >= 1000)
		{
			time_nrf_start = HAL_GetTick();
			if (radio_flag)
			{
				nrf24_fifo_flush_tx(&nrf24_lower_api_config);
				memset(tx_buffer, 0x00, sizeof(tx_buffer));
				memcpy(tx_buffer, &packet_da_type_1, sizeof(packet_da_type_1));
				nrf24_fifo_write_ack_pld(&nrf24_lower_api_config, 0, tx_buffer, sizeof(tx_buffer));
				memset(tx_buffer, 0x00, sizeof(tx_buffer));
				memcpy(tx_buffer, &packet_da_type_2, sizeof(packet_da_type_2));
				nrf24_fifo_write_ack_pld(&nrf24_lower_api_config, 0, tx_buffer, sizeof(tx_buffer));
				radio_flag = !radio_flag;
			}
			else
			{
				nrf24_fifo_flush_tx(&nrf24_lower_api_config);
				memset(tx_buffer, 0x00, sizeof(tx_buffer));
				memcpy(tx_buffer, &packet_da_type_2, sizeof(packet_da_type_2));
				nrf24_fifo_write_ack_pld(&nrf24_lower_api_config, 0, tx_buffer, sizeof(tx_buffer));
				memset(tx_buffer, 0x00, sizeof(tx_buffer));
				memcpy(tx_buffer, &packet_da_type_1, sizeof(packet_da_type_1));
				nrf24_fifo_write_ack_pld(&nrf24_lower_api_config, 0, tx_buffer, sizeof(tx_buffer));
				radio_flag = !radio_flag;
			}
		}

        //???????????????? ??????????
        nrf24_irq_clear(&nrf24_lower_api_config, NRF24_IRQ_RX_DR | NRF24_IRQ_TX_DR | NRF24_IRQ_MAX_RT);

    }
	return 0;
}

