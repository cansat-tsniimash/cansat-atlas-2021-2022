#include <stdbool.h>
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include <stdio.h>
#include "motor.h"
#include "triggers.h"
#include "config.h"
#include "nRF24L01_PL/nrf24_upper_api.h"
#include "nRF24L01_PL/nrf24_lower_api_stm32.h"
#include "nRF24L01_PL/nrf24_lower_api.h"
#include "Photorezistor/photorezistor.h"
#include "ATGM336H/nmea_gps.h"
#include "BME280/DriverForBME280.h"
#include "Shift_Register/shift_reg.h"
#include <math.h>
#include "LSM6DS3/DLSM.h"
#include "fatfs.h"
#include "LIS3MDL/DLIS3.h"
#include "1Wire_DS18B20/one_wire.h"

#define NRF_BUTTON_PHOTORESISTOR_PIN GPIO_PIN_10
#define NRF_BUTTON_PHOTORESISTOR_PORT GPIOB
#define TIME_WAIT_BTN_PHOTOREZ 5000
#define RADIO_TIMEOUT 2
#define KOF 0.8
#define HEIGHT_SEPARATION 200

extern SPI_HandleTypeDef hspi2;
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart6;



typedef enum//ОПИСЫВАЕМ ОБЩЕНИЕ ПО РАДИО
{

    STATE_BUILD_PACKET_MA_1_TO_GCS,
	STATE_BUILD_PACKET_MA_2_TO_GCS,
	STATE_BUILD_PACKET_TO_DA_1,
	STATE_SEND,
	STATE_WRITE_DA_PACKET_TO_GCS,
	STATE_SEND_PACKET_FROM_DA_TO_GCS,
	STATE_BUILD_PACKET_TO_DA_2
}nrf24_state_t;

typedef enum//ОПИСЫВАЕМ СОСТОЯНИЕ ПОЛЕТА
{
	STATE_INIT,
	STATE_ON_GROUND,
	STATE_WAIT,
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

	float BME280_pressure;
	float BME280_temperature;

	int16_t DS18B20_temperature;

    float latitude;
    float longitude;
    int16_t height;
    uint16_t cookie;
    uint8_t fix;

	uint16_t sum;

}packet_ma_type_1_t;

typedef struct
{
	uint8_t flag;
	uint16_t num;
	uint32_t time;


	int16_t acc_mg [3];

    int16_t gyro_mdps [3];

    int16_t LIS3MDL_magnetometer[3];

    float phortsistor;

    uint8_t state;

	uint16_t sum;
}packet_ma_type_2_t;
#pragma pack(pop)

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
static void print_register(uint8_t reg_addr, uint8_t * reg_data)
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

		printf("invalid reg addr: %d\n", reg_addr);
		return;
	}

	const char * reg_name = selected_param->name;
	const size_t reg_size = selected_param->size;

	printf("reg %s (0x%02X) = ", reg_name, (int)reg_addr);
	if (1 == reg_size)
	{
		printf("0x%02X", reg_data[0]);
		char bits_buffer[10] = {0};
		print_bits(reg_data[0], bits_buffer);
		printf(" (0b%s)", bits_buffer);
	}
	else
	{
		printf("0x");
		for (size_t j = 0; j < reg_size; j++)
		{
			printf("%02X", reg_data[j]);
		}
	}
	printf("\n");
}
static void dump_registers(void *intf_ptr)
{
	const size_t regs_count = sizeof(reg_params)/sizeof(reg_params[0]);
	for (size_t i = 0 ; i < regs_count; i++)
	{
		uint8_t reg_addr = reg_params[i].addr;
		uint8_t reg_size = reg_params[i].size;

		uint8_t reg_data[5] = { 0 };
		nrf24_read_register(intf_ptr, reg_addr, reg_data, reg_size);

		print_register(reg_addr, reg_data);
	}
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
	ds18b20_t ds18b20;
	ds18b20.onewire_pin = GPIO_PIN_1;
	ds18b20.onewire_port = GPIOA;
    onewire_init(&ds18b20);

	shift_reg_t shift_reg_sens;
	shift_reg_sens.bus = &hspi2;
	shift_reg_sens.latch_port = GPIOC;
	shift_reg_sens.latch_pin = GPIO_PIN_1;
	shift_reg_sens.oe_port = GPIOC;
	shift_reg_sens.oe_pin = GPIO_PIN_13;
	shift_reg_init(&shift_reg_sens);
	shift_reg_write_8(&shift_reg_sens, 0xff);

	shift_reg_t shift_reg_nrf;
	shift_reg_nrf.bus = &hspi2;
	shift_reg_nrf.latch_port = GPIOC;
	shift_reg_nrf.latch_pin = GPIO_PIN_4;
	shift_reg_nrf.oe_port = GPIOC;
	shift_reg_nrf.oe_pin = GPIO_PIN_5;
	shift_reg_init(&shift_reg_nrf);
	shift_reg_write_8(&shift_reg_nrf, 0xff);

	stmdev_ctx_t ctx = {0};
 	lsm_spi_intf_sr spi_interface;
	spi_interface.spi = &hspi2;
	spi_interface.sr_pin = 4;
	spi_interface.sr = &shift_reg_sens;
	lsmset_sr(&ctx, &spi_interface);

	struct bme280_dev bme = {0};	//инициализируем настройки бме280
	bme_spi_intf_sr spi_intf;
	spi_intf.spi = &hspi2;
	spi_intf.sr = &shift_reg_sens;
	spi_intf.sr_pin = 2;
	bme_init_default_sr(&bme, &spi_intf);

	stmdev_ctx_t lis3mdl_ctx;
	struct lis_spi_intf_sr lis_interface;
	lis_interface.spi = &hspi2;
	lis_interface.sr = &shift_reg_sens;
	lis_interface.sr_pin = 3;

	nrf24_spi_pins_sr_t nrf24_spi_pins_sr;
	nrf24_spi_pins_sr.pos_CE = 0;
	nrf24_spi_pins_sr.pos_CS = 1;
	nrf24_spi_pins_sr.this = &shift_reg_nrf;
	nrf24_lower_api_config_t nrf24_api_config;
	nrf24_spi_init_sr(&nrf24_api_config, &hspi2, &nrf24_spi_pins_sr);

	nrf24_mode_standby(&nrf24_api_config);
	// Настройки радиопередачи
	nrf24_rf_config_t nrf24_rf_config;
	nrf24_rf_config.data_rate = NRF24_DATARATE_250_KBIT;
	nrf24_rf_config.rf_channel = 100;
	nrf24_rf_config.tx_power = NRF24_TXPOWER_MINUS_18_DBM;
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

	float temperature_celsius_mag;

	nrf24_pipe_set_tx_addr(&nrf24_api_config, 0xacacacacac);

	nrf24_pipe_config_t pipe_config;
	pipe_config.address = 0xafafafaf01;
	pipe_config.enable_auto_ack = true;
	pipe_config.payload_size = -1;
	nrf24_pipe_rx_start(&nrf24_api_config, 0, &pipe_config);

	//заполнение структуры на фоторезистор
	photorezistor_t photoresistor;
	//сопротивление (R)
	photoresistor.resist = 5100;
	//hadc1 - дискриптор с начтройками АЦП
	photoresistor.hadc = &hadc1;

	//инициализация гпс
	gps_init();
	__HAL_UART_ENABLE_IT(&huart6, UART_IT_RXNE);
	__HAL_UART_ENABLE_IT(&huart6, UART_IT_ERR);

	packet_ma_type_1_t packet_ma_type_1 = {0};
	packet_ma_type_2_t packet_ma_type_2 = {0};
	packet_ma_type_1.flag = 0xff;
	packet_ma_type_2.flag = 0xfe;
    uint16_t height;
	uint32_t time_btn_now = HAL_GetTick();
	uint8_t da_1_rx_buffer[32];
	uint32_t start_time = 0;
	state_t state_now = STATE_INIT;
	nrf24_state_t nrf24_state_now = STATE_BUILD_PACKET_MA_1_TO_GCS;
	nrf24_fifo_status_t rx_status;
	nrf24_fifo_status_t tx_status;
	int comp;
	uint8_t da_1_resp_count = 0;
	float lux_rn = 0;
	float lux_sun = 0;
	//создаем переменные для записи телеметрии gps
	int64_t cookie;
	float lat ;
	float lon;
	float alt;
	struct bme280_data comp_data = {0};
	float temperature_celsius_gyro = 0;
    float acc_g [3];
    float gyro_dps [3];
    uint16_t packet_num_1 = 0;
    uint16_t packet_num_2 = 0;
    nrf24_mode_tx(&nrf24_api_config);
    float mag[3];
    uint32_t start_time_ds = 0;
    uint32_t now_time_ds = 0;
    uint16_t temp_ds18b20;
    bool crc_ok_ds;
    int fix;
    UINT bw;
    uint8_t state_in_send_true;
    uint8_t state_in_send_false;
    size_t packet_size;

    uint32_t send_to_gcs_start_time = 0;
	//motor_on();

    lisset_sr(&lis3mdl_ctx, &lis_interface);

	FATFS fileSystem; // переменная типа FATFS
	FIL testFile; // хендлер файла
	char testBuffer[16] = "TestTestTestTest"; // данные для записи
	UINT testBytes; // количество символов, реально записанных внутрь файла
	FRESULT res; // результат выполнения функции
	f_mount(&fileSystem, SDPath, 1);
	 // монтируете файловую систему по пути SDPath, проверяете, что она смонтировалась, только при этом условии начинаете с ней работать
	uint8_t path[13] = "testfile.bin"; // название файла
	path[12] = '\0'; // добавляем символ конца строки в конец строки

	res = f_open(&testFile, (char*)path, FA_WRITE | FA_CREATE_ALWAYS); // открытие файла, обязательно для работы с ним

	dump_registers(&nrf24_api_config);

	start_time_ds = HAL_GetTick();
	ds18b20_start_conversion(&ds18b20);
	while(1)
	{
		comp_data = bme_read_data(&bme);
		packet_ma_type_1.BME280_pressure = (float)comp_data.pressure;
		packet_ma_type_1.BME280_temperature = (float)comp_data.temperature;
		lsmread(&ctx, &temperature_celsius_gyro, &acc_g, &gyro_dps);

		for (int i= 0; i < 3 ; i++)
		{
			packet_ma_type_2.acc_mg[i] = (int16_t)(acc_g[i]*1000);
		}

		for (int i = 0; i < 3 ; i++)
		{
			packet_ma_type_2.gyro_mdps[i] = (int16_t)(gyro_dps[i]*1000);
		}
		printf("темп %ld\n ",(int32_t)packet_ma_type_1.BME280_temperature);


		lisread(&lis3mdl_ctx,&temperature_celsius_mag, &mag);
		for (int i = 0; i < 3 ;i++)
		{
			packet_ma_type_2.LIS3MDL_magnetometer[i] = mag[i]*1000;
		}



		now_time_ds = HAL_GetTick();
		if (HAL_GetTick()-start_time_ds >= 750)
		{
			ds18b20_read_raw_temperature(&ds18b20, &temp_ds18b20, &crc_ok_ds);
			packet_ma_type_1.DS18B20_temperature = (temp_ds18b20*10)/16;
			ds18b20_start_conversion(&ds18b20);
			start_time_ds = HAL_GetTick();
		}





		uint16_t height_on_BME280;
		uint32_t pressure_on_ground;
		pressure_on_ground = (float)comp_data.pressure;
		gps_work();
		gps_get_coords(&cookie,  & lat,  & lon,& alt, &fix);
		packet_ma_type_1.latitude = lat;
		packet_ma_type_1.longitude = lon;
		packet_ma_type_1.height = (int16_t)(alt*100);
		height_on_BME280 = 44330*(1 - pow((float)packet_ma_type_1.BME280_pressure/pressure_on_ground, 1.0/5.255));
		packet_ma_type_1.fix = fix;
		printf("%d ", (int)cookie);
		//кладем значение освещенности в поля пакета
		//packet_ma_type_2.phortsistor = photorezistor_get_lux(photoresistor);
		//printf("%ld\n", (uint32_t)packet_ma_type_2.phortsistor);

		switch (state_now)
		{
		case STATE_INIT:
			if (check_out_board_trigger() == false)
			{
				lux_sun = photorezistor_get_lux(photoresistor);
				state_now = STATE_ON_GROUND;
			}
		    break;

		case STATE_ON_GROUND:
			if (check_out_board_trigger() == true)
			{

				state_now = STATE_WAIT;
			}

			break;

		case STATE_WAIT:
			time_btn_now = HAL_GetTick();
		    if(time_btn_now > start_time + TIME_WAIT_BTN_PHOTOREZ)
		    {
				state_now = STATE_IN_RN;
				lux_rn = photorezistor_get_lux(photoresistor);
		    }
		    break;

		case STATE_IN_RN:
			//добавит ожидание освещенности

			packet_ma_type_2.phortsistor = photorezistor_get_lux(photoresistor);
			if ((lux_sun-lux_rn)*KOF < packet_ma_type_2.phortsistor-lux_rn)
			{
				state_now = STATE_AFTER_SEPARATION;
			}
			break;

		case STATE_AFTER_SEPARATION:
			if (HEIGHT_SEPARATION >= height_on_BME280)
			{
				state_now = STATE_MINOR_DEVICE_SEPARATION;
			}
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
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
			break;
		}






	    switch (nrf24_state_now)
	    {

	        case STATE_BUILD_PACKET_MA_1_TO_GCS:
	        	packet_ma_type_1.time = HAL_GetTick();
	            packet_num_1++;
	        	packet_ma_type_1.num = packet_num_1;
	        	packet_ma_type_1.sum = Crc16((uint8_t *)&packet_ma_type_1, sizeof(packet_ma_type_1) - 2);
	        	nrf24_pipe_set_tx_addr(&nrf24_api_config, 0x123456789a);
			    nrf24_fifo_write(&nrf24_api_config, (uint8_t *)&packet_ma_type_1, sizeof(packet_ma_type_1), false);
                state_in_send_true = STATE_BUILD_PACKET_MA_2_TO_GCS;
                state_in_send_false = STATE_BUILD_PACKET_MA_2_TO_GCS;
			    nrf24_state_now = STATE_SEND;
			    send_to_gcs_start_time = HAL_GetTick();
				res = f_write (&testFile,  (uint8_t *)&packet_ma_type_1, sizeof(packet_ma_type_1), &bw);
				res = f_write (&testFile,  (uint8_t *)&packet_ma_type_2, sizeof(packet_ma_type_2), &bw);
				f_sync(&testFile);
		        // запись в файл (на sd контроллер пишет не сразу, а по закрытии файла. Также можно использовать эту команду)
			    break;

	        case STATE_BUILD_PACKET_MA_2_TO_GCS:
	        	packet_ma_type_2.time = HAL_GetTick();
	            packet_num_2++;
	            packet_num_2++;
	        	packet_ma_type_2.num = packet_num_2;
	        	packet_ma_type_2.sum = Crc16((uint8_t *)&packet_ma_type_2, sizeof(packet_ma_type_2) - 2);
			    nrf24_fifo_write(&nrf24_api_config, (uint8_t *)&packet_ma_type_2, sizeof(packet_ma_type_2), false);
                state_in_send_true = STATE_BUILD_PACKET_TO_DA_1;
                state_in_send_false = STATE_BUILD_PACKET_TO_DA_1;
			    nrf24_state_now = STATE_SEND;
			    send_to_gcs_start_time = HAL_GetTick();
				res = f_write (&testFile,  (uint8_t *)&packet_ma_type_2, sizeof(packet_ma_type_2), &bw);
				f_sync(&testFile);
				break;

	        case STATE_SEND:
	     	    nrf24_fifo_status(&nrf24_api_config, &rx_status, &tx_status);
	            if(tx_status == NRF24_FIFO_EMPTY)
	            {
	            	nrf24_state_now = state_in_send_true;
	            }
	            if(HAL_GetTick() > (send_to_gcs_start_time + RADIO_TIMEOUT))
	            {
	            	nrf24_fifo_flush_tx(&nrf24_api_config);
	            	nrf24_state_now = state_in_send_false;
	            }
	            break;

	        case STATE_BUILD_PACKET_TO_DA_1 :
	        	//printf("ДА, лови маслину\n");
	        	nrf24_pipe_set_tx_addr(&nrf24_api_config, 0xafafafaf01);
			    nrf24_fifo_write(&nrf24_api_config, (uint8_t *)&packet_ma_type_1, sizeof(packet_ma_type_1), true);
                state_in_send_true = STATE_WRITE_DA_PACKET_TO_GCS;
                state_in_send_false = STATE_BUILD_PACKET_TO_DA_2;
			    nrf24_state_now = STATE_SEND;
			    send_to_gcs_start_time = HAL_GetTick();
	        	break;

	        case STATE_WRITE_DA_PACKET_TO_GCS :
	        	packet_size = nrf24_fifo_read(&nrf24_api_config, da_1_rx_buffer, sizeof(da_1_rx_buffer));
	        	if (packet_size > 0)
				{
					nrf24_pipe_set_tx_addr(&nrf24_api_config, 0x123456789a);
					nrf24_fifo_write(&nrf24_api_config, (uint8_t *)da_1_rx_buffer, packet_size, false);
					res = f_write (&testFile, (uint8_t *)da_1_rx_buffer, packet_size, &bw);
					f_sync(&testFile);

					send_to_gcs_start_time = HAL_GetTick();
					state_in_send_true = state_in_send_false;
					nrf24_state_now = STATE_SEND;
				}
	        	else
	        	{
	        		nrf24_state_now = state_in_send_false;
	        	}
				break;

	        case STATE_BUILD_PACKET_TO_DA_2:
	        	nrf24_pipe_set_tx_addr(&nrf24_api_config, 0xafafafaf01);
			    nrf24_fifo_write(&nrf24_api_config, (uint8_t *)&packet_ma_type_2, sizeof(packet_ma_type_2), true);
                state_in_send_true = STATE_WRITE_DA_PACKET_TO_GCS;
                state_in_send_false = STATE_BUILD_PACKET_MA_1_TO_GCS;
			    nrf24_state_now = STATE_SEND;
			    send_to_gcs_start_time = HAL_GetTick();
			    break;

	    }
	    //dump_registers(&nrf24_api_config);
		nrf24_irq_clear(&nrf24_api_config, NRF24_IRQ_RX_DR | NRF24_IRQ_TX_DR | NRF24_IRQ_MAX_RT);
	}
	return 0;
    }


