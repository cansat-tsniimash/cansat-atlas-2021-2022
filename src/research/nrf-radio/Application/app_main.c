#include <stdint.h>
#include <stdio.h>
#include <stm32f4xx_hal.h>
#include "nrf24_lower_api.h"

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

int app_main()
{
	// Работаем по приложению A даташита. Что нужно сделать чтобы передавать

	// в первую очередь настроим модуль
	// Начнем с конфигурационного регистра
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	uint8_t cfg_reg = 0;
	cfg_reg &= ~RF24_CONFIG_PRIM_RX; // Будем передатчиком
	cfg_reg |= RF24_CONFIG_PWR_UP; // Не будем спать
	cfg_reg |= RF24_CONFIG_EN_CRC; // Будем использовать контрольную сумму
	cfg_reg &= ~RF24_CONFIG_CRCO;  // 1 байт на контрольную сумму
	// Прерывания не используем и даже трогать на будем
	rf24_write_register(RF24_REGADDR_CONFIG, &cfg_reg, 1);

	HAL_Delay(1);

	uint8_t readout_cfg = 0;
	rf24_read_register(RF24_REGADDR_CONFIG, &readout_cfg, 1);

	// Включаем все FEATURES
	uint8_t features = 0;
	features = (1 << 2) | (1 << 1) | (1 << 0);
	rf24_write_register(RF24_REGADDR_FEATURE, &features, 1);

	// Теперь нужно установить адрес пайпа на который мы будем передавать
	uint64_t tx_addr = 0x00cadebaba;
	//rf24_write_register(RF24_REGADDR_TX_ADDR, (uint8_t *)(&tx_addr), 5); // 5 байт на адрес без доп настроек

	// Выставляем мощность и частоту
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	uint8_t rf_setup = 0;
	// Скорость на 250 кбит
	rf_setup |= RF24_RFSETUP_RF_DR_LOW;
	rf_setup &= ~RF24_RFSETUP_RF_DR_HIGH;
	// МАКСИМАЛЬНАЯ МОЩНОСТЬ
	rf_setup &= ~(RF24_RFSETUP_RF_PWR_MASK << RF24_RFSETUP_RF_PWR_OFFSET);
	//rf_setup |= (0x03 & RF24_RFSETUP_RF_PWR_MASK) << RF24_RFSETUP_RF_PWR_OFFSET;
	rf24_write_register(RF24_REGADDR_RF_SETUP, &rf_setup, 1);

	// частота считается как 2400 МГц + канал
	// встанем на 2437 - 6ой канал Wi-Fi
	uint8_t rf_channel = 41;
	rf24_write_register(RF24_REGADDR_RF_CH, &rf_channel, 1);

	// по-умолчанию включено аж 2 пайпа на приём и для них включены авто ACK
	// Сейчас у нас не будет приёмника, поэтому модуль будет отправлять пакет
	// несколько раз и будет говорить что отправка не удалась.
	// Ну и фиг с ним!

	int packet_number = 0;
	rf24_ce_activate(true);
	while(1)
	{
		uint8_t payload[32] = {0};

		// Запишем пайлоад строкой
		//snprintf(payload, sizeof(payload), "packet no %d", packet_number);

		// загоняем на радио
		// Мы не включали динамических размеров пейлоада, поэтому гоним целиком 32 байта
		// с нулями
		rf24_flush_tx();
		rf24_write_tx_payload(payload, sizeof(payload), true);

		// дергаем CE на 10мкс чтобы начать передачу.
		// МЫ не умеем по микросекундам, поэтому дернем на миллисекунду
		HAL_Delay(10);
		//rf24_ce_activate(true);
		HAL_Delay(1);
		//rf24_ce_activate(false);

		// Подождем сколько-то пока пакет отправляется
		// Пускай будет 100 мс
		HAL_Delay(10);

		// TODO: вычитать статус и посмотреть что там происходит
		volatile uint8_t status;
		rf24_get_status(&status);

		uint8_t irq_clear = (1 << 6) | (1 << 5) | (1 << 4);
		//rf24_write_register(RF24_REGADDR_STATUS, &irq_clear, 1);

		HAL_Delay(1);
		rf24_get_status(&status);

		// Увеличиваем номер пакета
		packet_number++;
	}
}
