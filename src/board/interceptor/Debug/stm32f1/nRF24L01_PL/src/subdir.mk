################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/1/Documents/git/cansat-atlas-2021-2022/lib-tsniimash/stm32f1/nRF24L01_PL/src/nrf24_lower_api_stm32.c \
C:/Users/1/Documents/git/cansat-atlas-2021-2022/lib-tsniimash/stm32f1/nRF24L01_PL/src/nrf24_upper_api.c 

OBJS += \
./stm32f1/nRF24L01_PL/src/nrf24_lower_api_stm32.o \
./stm32f1/nRF24L01_PL/src/nrf24_upper_api.o 

C_DEPS += \
./stm32f1/nRF24L01_PL/src/nrf24_lower_api_stm32.d \
./stm32f1/nRF24L01_PL/src/nrf24_upper_api.d 


# Each subdirectory must supply rules for building sources it contributes
stm32f1/nRF24L01_PL/src/nrf24_lower_api_stm32.o: C:/Users/1/Documents/git/cansat-atlas-2021-2022/lib-tsniimash/stm32f1/nRF24L01_PL/src/nrf24_lower_api_stm32.c stm32f1/nRF24L01_PL/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../../../../lib-tsniimash/stm32f1 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32f1/nRF24L01_PL/src/nrf24_upper_api.o: C:/Users/1/Documents/git/cansat-atlas-2021-2022/lib-tsniimash/stm32f1/nRF24L01_PL/src/nrf24_upper_api.c stm32f1/nRF24L01_PL/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../../../../lib-tsniimash/stm32f1 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-stm32f1-2f-nRF24L01_PL-2f-src

clean-stm32f1-2f-nRF24L01_PL-2f-src:
	-$(RM) ./stm32f1/nRF24L01_PL/src/nrf24_lower_api_stm32.d ./stm32f1/nRF24L01_PL/src/nrf24_lower_api_stm32.o ./stm32f1/nRF24L01_PL/src/nrf24_upper_api.d ./stm32f1/nRF24L01_PL/src/nrf24_upper_api.o

.PHONY: clean-stm32f1-2f-nRF24L01_PL-2f-src

