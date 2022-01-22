#include <stdint.h>
#include <stm32f4xx_hal.h>

extern SPI_HandleTypeDef hspi2;

static uint8_t read_reg(uint8_t reg_addr, uint8_t *reg_data, uint32_t len)
{
	// Переменная для значения STATUS регистра
	uint8_t status;

	// Опускаем chip select для того, что бы начать общение с конкретным устройством.
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1,  GPIO_PIN_RESET);

	// Добавляем в 5 битов адреса еще 3 бита для чтения из этого регистра
	reg_addr = reg_addr & ~((1 << 5) | (1 << 6) | (1 << 7));

	// Передаем адресс регистра, который читаем, на шину spi и получаем в ответ значение STATUS регистр
	HAL_SPI_TransmitReceive(&hspi2, &reg_addr, &status, 1, HAL_MAX_DELAY);

	// Читаем данные
	HAL_SPI_Receive(&hspi2, reg_data, len, HAL_MAX_DELAY);

	// Поднимаем chip select для того, что бы закончить общение с конкретным устройством.
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1,  GPIO_PIN_SET);

	return status;
}

static uint8_t write_reg(uint8_t reg_addr, uint8_t *reg_data, uint32_t len)
{
	// Переменная для значения STATUS регистра
	uint8_t status;

	// Опускаем chip select для того, что бы начать общение с конкретным устройством.
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1,  GPIO_PIN_RESET);

	// Добавляем в 5 битов адреса еще 3 бита для чтения из этого регистра
	reg_addr = (reg_addr & ~((1 << 6) | (1 << 7))) | (1 << 5);

	// Передаем адресс регистра, который читаем, на шину spi и получаем в ответ значение STATUS регистра
	HAL_SPI_TransmitReceive(&hspi2, &reg_addr, &status, 1, HAL_MAX_DELAY);

	// Читаем данные
	HAL_SPI_Transmit(&hspi2, reg_data, len, HAL_MAX_DELAY);

	// Поднимаем chip select для того, что бы закончить общение с конкретным устройством.
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1,  GPIO_PIN_SET);

	return status;
}

static void send_command(uint8_t command){
	// Опускаем chip select для того, что бы начать общение с конкретным устройством.
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1,  GPIO_PIN_RESET);

	// Передали радио комманду
	HAL_SPI_Transmit(&hspi2, &command, 1, HAL_MAX_DELAY);

	// Поднимаем chip select для того, что бы закончить общение с конкретным устройством.
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1,  GPIO_PIN_SET);
}

int app_main()
{








}
