#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#include <stm32f4xx_hal.h>
#include "nRF24L01_PL/nrf24_lower_api.h"
#include "nRF24L01_PL/nrf24_upper_api.h"

extern SPI_HandleTypeDef hspi2;
/*
typedef struct
{
	struct
	{
		uint8_t mask_rx_dr:0;
		uint8_t	mask_tx_ds:0;
		uint8_t	mask_max_rt:0;
		uint8_t	en_crc:1;
		uint8_t	crc0:0;
		uint8_t	pwr_up:0;
		uint8_t	prim_rx:0;
	} config;

	struct
	{
		uint8_t enaa_p5:1;
		uint8_t	enaa_p4:1;
		uint8_t	enaa_p3:1;
		uint8_t	enaa_p2:1;
		uint8_t	enaa_p1:1;
		uint8_t	enaa_p0:1;
	} en_aa;

	struct
	{
		uint8_t erx_p5:0;
		uint8_t	erx_p4:0;
		uint8_t	erx_p3:0;
		uint8_t	erx_p2:0;
		uint8_t	erx_p1:1;
		uint8_t	erx_p0:1;
	} en_aa;

    struct
	{
		uint8_t aw:3;
    } setup_aw;

	struct
	{
		uint8_t ard:0;
		uint8_t	arc:3;
	} setup_retr;

	struct
	{
		uint8_t rf_ch:2;
	} rf_ch;

	struct
	{
		uint8_t pll_lock:0;
		uint8_t	rf_dr:1;
		uint8_t	rf_pwr:3;
		uint8_t	lna_hcurr:1;
	} rf_setup;

	struct
	{
		uint8_t en_dpl:0;
		uint8_t	en_ack_pay:0;
		uint8_t	en_dyn_ack:0;
	} feature;

	uint8_t rx_addr_p0[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
	uint8_t rx_addr_p1[5] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
	uint8_t rx_addr_p2 = 0xC3;
	uint8_t rx_addr_p3 = 0xC4;
	uint8_t rx_addr_p4 = 0xC5;
	uint8_t rx_addr_p5 = 0xC6;

	uint8_t tx_addr[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};

	struct
	{
		uint8_t rx_pw_p0:0;
	} rx_pw_p0;

	struct
	{
		uint8_t rx_pw_p1:0;
	} rx_pw_p1;

	struct
	{
		uint8_t rx_pw_p2:0;
	} rx_pw_p2;

	struct
	{
		uint8_t rx_pw_p3:0;
	} rx_pw_p3;

	struct
	{
		uint8_t rx_pw_p4:0;
	} rx_pw_p4;

	struct
	{
		uint8_t rx_pw_p5:0;
	} rx_pw_p5;


	struct
	{
		uint8_t dpl_p5:0;
		uint8_t	dpl_p4:0;
		uint8_t	dpl_p3:0;
		uint8_t	dpl_p2:0;
		uint8_t	dpl_p1:0;
		uint8_t	dpl_p0:0;
	} dynpd;
}nrf24l01_config_t;
*/
#define STATUS 0x07

#define CONFIG 0x00
#define CONFIG_MASK_RX_DR  6
#define CONFIG_MASK_TX_DS  5
#define CONFIG_MASK_MAX_RT 4
#define CONFIG_EN_CRC      3
#define CONFIG_CRCO        2
#define CONFIG_PWR_UP      1
#define CONFIG_PRIM_RX     0

#define EN_AA 0x01
#define EN_AA_ENAA_P5	5
#define EN_AA_ENAA_P4	4
#define EN_AA_ENAA_P3	3
#define EN_AA_ENAA_P2	2
#define EN_AA_ENAA_P1	1
#define EN_AA_ENAA_P0	0

#define EN_RXADDR 0x01
#define EN_RXADDR_ERX_P5	5
#define EN_RXADDR_ERX_P4	4
#define EN_RXADDR_ERX_P3	3
#define EN_RXADDR_ERX_P2	2
#define EN_RXADDR_ERX_P1	1
#define EN_RXADDR_ERX_P0	0

#define SETUP_AW 0x03

#define SETUP_RETR 0x04
#define SETUP_RETR_ARD 4
#define SETUP_RETR_ARC 0

#define RF_CH 0x05

#define RF_SETUP 0x06
#define RF_SETUP_PLL_LOCK 0
#define RF_SETUP_RF_DR 1
#define RF_SETUP_RF_PWR 11
#define RF_SETUP_LNA_HCURR 1

#define RX_ADDR_P0 0A
#define RX_ADDR_P1 0B
#define RX_ADDR_P2 0C
#define RX_ADDR_P3 0D
#define RX_ADDR_P4 0E
#define RX_ADDR_P5 0F

#define TX_ADDR 0x10

#define RX_PW_P0 0x11
#define RX_PW_P1 0x12
#define RX_PW_P2 0x13
#define RX_PW_P3 0x14
#define RX_PW_P4 0x15
#define RX_PW_P5 0x16

#define FIFO_STATUS 0x17

#define DYNPD 0x1C

#define FEATURE 0x1D


/*
static void send_command(uint8_t command){
	// Опускаем chip select для того, что бы начать общение с конкретным устройством.
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1,  GPIO_PIN_RESET);

	// Передали радио комманду
	HAL_SPI_Transmit(&hspi2, &command, 1, HAL_MAX_DELAY);

	// Поднимаем chip select для того, что бы закончить общение с конкретным устройством.
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1,  GPIO_PIN_SET);
}

void nrf24l01_get_config(nrf24l01_config_t *nrf_config)
{
	uint8_t reg;
	read_reg(CONFIG, &reg, 1);

	nrf_config->config.mask_rx_dr = (reg >> CONFIG_MASK_RX_DR) & 0x01;
	nrf_config->config.mask_tx_ds = (reg >> CONFIG_MASK_TX_DS) & 0x01;
	nrf_config->config.mask_max_rt = (reg >> CONFIG_MASK_MAX_RT) & 0x01;
	nrf_config->config.en_crc = (reg >> CONFIG_EN_CRC) & 0x01;
	nrf_config->config.crc0 = (reg >> CONFIG_CRCO) & 0x01;
	nrf_config->config.prim_rx = (reg >> CONFIG_PRIM_RX) & 0x01;

	read_reg(CONFIG, &reg, 1);

	nrf_config->
}*/


static void dump_registers(void);
//static
void print_bits(uint8_t value, char * buffer);
static void print_register(uint8_t reg_addr, uint8_t * reg_data);

// Only for debug
void read_regs()
{
	uint8_t status;
	uint8_t obs_tx;
	nrf24_get_status(&status);
	nrf24_read_register(NRF24_REGADDR_OBSERVE_TX, &obs_tx, 1);
	print_register(NRF24_REGADDR_STATUS, &status);
	print_register(NRF24_REGADDR_OBSERVE_TX, &obs_tx);
}

int app_main()
{
	// Работаем по приложению A даташита. Что нужно сделать чтобы передавать

	HAL_Delay(100);

	printf("starting\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	dump_registers();
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	//while(1) {}

	// в первую очередь настроим модуль
	// переходим в power down
	nrf24_mode_power_down();

	// Настройки радиопередачи
	nrf24_rf_config_t nrf24_rf_config;
	nrf24_rf_config.data_rate = NRF24_DATARATE_2000_KBIT;
	nrf24_rf_config.rf_channel = 25;
	nrf24_rf_config.tx_power = NRF24_TXPOWER_MINUS_0_DBM;
	nrf24_setup_rf(&nrf24_rf_config);

	// Настроили протокол
	nrf24_protocol_config_t nrf24_protocol_config;
	nrf24_protocol_config.address_width = NRF24_ADDRES_WIDTH_5_BYTES;
	nrf24_protocol_config.auto_retransmit_count = 10;
	nrf24_protocol_config.auto_retransmit_delay = 0;
	nrf24_protocol_config.crc_size = NRF24_CRCSIZE_1BYTE;
	nrf24_protocol_config.en_ack_payload = true;
	nrf24_protocol_config.en_dyn_ack = true;
	nrf24_protocol_config.en_dyn_payload_size = true;
	nrf24_setup_protocol(&nrf24_protocol_config);

	// Теперь нужно установить адрес пайпа на который мы будем передавать
	nrf24_pipe_set_tx_addr(0xacacacacac);

	nrf24_pipe_config_t pipe_config;
	pipe_config.address = 0xafafafafaf;
	pipe_config.enable_auto_ack = false;
	pipe_config.payload_size = -1;
	for(int i = 0 ; i < 6 ; i++)
	{
		pipe_config.address += i;
		nrf24_pipe_rx_start(i, &pipe_config);
	}
	nrf24_mode_standby();

	printf("configured\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	dump_registers();
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	//while(1) {}

	int packet_number = 0;
	while(1)
	{
		uint8_t payload[32] = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'T', 'i', 'm', 'o', 'f', 'e', 'i', '!', '!'};

		// Запишем пайлоад строкой
		//snprintf(payload, sizeof(payload), "packet no %d", packet_number);

		nrf24_fifo_write(payload, sizeof(payload), false);

		printf("status_after_w_tx_clear\n");
		read_regs();

		// дергаем CE на 10мкс чтобы начать передачу.
		// МЫ не умеем по микросекундам, поэтому дернем на миллисекунду
		nrf24_mode_tx();
		HAL_Delay(10);
		nrf24_mode_standby();
		HAL_Delay(1);

		printf("status_after_ce_activate_clear\n");
		read_regs();


		// Подождем сколько-то пока пакет отправляется
		// Пускай будет 100 мс
		//HAL_Delay(100);

		printf("status_before_clear\n");
		read_regs();

		nrf24_irq_clear(NRF24_IRQ_RX_DR | NRF24_IRQ_TX_DR | NRF24_IRQ_MAX_RT);

		printf("status_after_clear\n");
		read_regs();

		// Увеличиваем номер пакета
		packet_number++;

		//dump_registers();

		//HAL_Delay(100);
	}
}


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

static void dump_registers(void)
{
	const size_t regs_count = sizeof(reg_params)/sizeof(reg_params[0]);
	for (size_t i = 0 ; i < regs_count; i++)
	{
		uint8_t reg_addr = reg_params[i].addr;
		uint8_t reg_size = reg_params[i].size;

		uint8_t reg_data[5] = { 0 };
		nrf24_read_register(reg_addr, reg_data, reg_size);

		print_register(reg_addr, reg_data);
	}
}

