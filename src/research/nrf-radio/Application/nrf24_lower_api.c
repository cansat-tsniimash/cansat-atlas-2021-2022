/*
 * nrf24_lower_api.c
 *
 *  Created on: 29 янв. 2022 г.
 *      Author: 1
 */
#include <stdbool.h>
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include "nrf24_lower_api.h"

extern SPI_HandleTypeDef hspi2;

#define CE_PORT GPIOA
#define CE_PIN GPIO_PIN_1

#define CS_PORT GPIOA
#define CS_PIN GPIO_PIN_0


// Чтение данных из регистров RF24
/* Аргументы:
   reg_addr - адрес читаемого регистра
   reg_data - указатель на буфер в который кладутся прочитанные данные
   data_size - размер буфера для прочитанных данных */
void rf24_read_register(uint8_t reg_addr, uint8_t * reg_data, size_t data_size)
{
	// Опускаем chip select для того, что бы начать общение с конкретным устройством.
	HAL_GPIO_WritePin(CS_PORT, CS_PIN,  GPIO_PIN_RESET);

	// Добавляем в 5 битов адреса еще 3 бита для чтения из этого регистра
	reg_addr = reg_addr & ~((1 << 5) | (1 << 6) | (1 << 7));

	// Передаем адресс регистра, который читаем
	HAL_SPI_Transmit(&hspi2, &reg_addr, 1, HAL_MAX_DELAY);

	// Читаем данные
	HAL_SPI_Receive(&hspi2, reg_data, data_size, HAL_MAX_DELAY);

	// Поднимаем chip select для того, что бы закончить общение с конкретным устройством.
	HAL_GPIO_WritePin(CS_PORT, CS_PIN,  GPIO_PIN_SET);
}

// Запись данных в регистры RF24
/* Аргументы:
   reg_addr - адрес записываемого регистра
   reg_data - указатель на буфер с записываемыми данными
   data_size - размер буфера с записываемыми данными */
void rf24_write_register(uint8_t reg_addr, const uint8_t * reg_data, size_t data_size)
{
	// Опускаем chip select для того, что бы начать общение с конкретным устройством.
	HAL_GPIO_WritePin(CS_PORT, CS_PIN,  GPIO_PIN_RESET);

	// Добавляем в 5 битов адреса еще 3 бита для чтения из этого регистра
	//reg_addr = (reg_addr & ~((1 << 6) | (1 << 7))) | (1 << 5);
	reg_addr &= (1 << 7) | (1 << 6);
	reg_addr |= (1 << 5);

	// Передаем адресс регистра, который читаем, на шину spi и получаем в ответ значение STATUS регистра
	HAL_SPI_Transmit(&hspi2, &reg_addr, 1, HAL_MAX_DELAY);
	HAL_SPI_Transmit(&hspi2, (uint8_t*)reg_data, data_size, HAL_MAX_DELAY);

	// Поднимаем chip select для того, что бы закончить общение с конкретным устройством.
	HAL_GPIO_WritePin(CS_PORT, CS_PIN,  GPIO_PIN_SET);
}

// Запись пакета для отправки
/* Аргументы:
   payload_buffer - указатель на буфер с отправляемым пакетом
   payload_size - размер отправляемого пакета в буфере payload_buffer
   use_ack - нужно ли использовать ACK для этого пакета?

   Эта функция реализует две команды: W_TX_PAYLOAD_NOACK и W_TX_PAYLOAD */
void rf24_write_tx_payload(const uint8_t * payload_buffer, size_t payload_size, bool use_ack)
{
	uint8_t command;
	// Опускаем chip select для того, что бы начать общение с конкретным устройством.
	HAL_GPIO_WritePin(CS_PORT, CS_PIN,  GPIO_PIN_RESET);

    if (use_ack)
    {
    	command = RF24_W_TX_PAYLOAD;
    }
    else
    {
    	command = RF24_W_TX_PAYLOAD_NO_ACK;
    }
    /*передаем команду */
	HAL_SPI_Transmit(&hspi2, &command, 1, HAL_MAX_DELAY);

	HAL_SPI_Transmit(&hspi2, (uint8_t*)payload_buffer, payload_size, HAL_MAX_DELAY);

	// Поднимаем chip select для того, что бы закончить общение с конкретным устройством.
	HAL_GPIO_WritePin(CS_PORT, CS_PIN,  GPIO_PIN_SET);
}


void rf24_flush_tx(void)
{
	uint8_t command = RF24_FLUSH_TX;
	HAL_GPIO_WritePin(CS_PORT, CS_PIN,  GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &command, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(CS_PORT, CS_PIN,  GPIO_PIN_SET);
}


void rf24_get_status(uint8_t * status)
{
	uint8_t command = RF24_NOP;
	HAL_GPIO_WritePin(CS_PORT, CS_PIN,  GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi2, &command, status, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(CS_PORT, CS_PIN,  GPIO_PIN_SET);
}


// Управление CE пином модуля.
/* onoff: значение true - CE прижат к полу; false - CE поднят к 1 */
void rf24_ce_activate(bool onoff)
{
	if (onoff)
	{
		HAL_GPIO_WritePin(CE_PORT, CE_PIN,  GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(CE_PORT, CE_PIN,  GPIO_PIN_SET);
	}
}
