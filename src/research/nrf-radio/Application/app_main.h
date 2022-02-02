/*
 * app_main.h
 *
 *  Created on: 26 янв. 2022 г.
 *      Author: 1
 */

#ifndef APP_MAIN_H_
#define APP_MAIN_H_


#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


void read_reg(uint8_t reg_addr, uint8_t * data, size_t data_size);
void write_reg(uint8_t reg_addr, const uint8_t * data, size_t data_size);
void read_rx_payload(uint8_t * buffer, suze_t buffer_size);
void write_tx_payload(const uint8_t * buffer, size_t buffer_size, bool use_ak);
void flush_tx(void);
void flush_rx(void);
void reuse_tx_pl(void);
void activate_features(void);
void read_plw(void);
void write_ak_pl(const uint8_t * buffer, size_t size);
void get_status(uint8_t * status);


int read_pl(uint8_t * pl , size_t);
int peek_rx_pl(void);

typedef enum mode_t
{
	MODE_TX,
	MODE_RX
} mode_t;

int switch_mode(mode_t mode);

int set_tx_pipe_addr(uint64_t pipe_addr);

int set_freq();


typedef enum data_rate_t
{
	DATA_RATE_250KBPS,
	DATA_RATE_1MBPS,
	DATA_RATE_2MBPS
} data_rate_t;


typedef enum rf_power_t
{
	RF_POWER_0DBM,
	RF_POWER_MINUS_6DBM,
	RF_POWER_MINUS_12DBM,
	RF_POWER_MINUS_18DBM,
} rf_power_t;


typedef struct rf_params_t
{
	uint8_t rf_channel;
	data_rate_t data_rate;
	rf_power_t power;
	bool enable_lna;
} rf_params_t;


#endif /* APP_MAIN_H_ */
