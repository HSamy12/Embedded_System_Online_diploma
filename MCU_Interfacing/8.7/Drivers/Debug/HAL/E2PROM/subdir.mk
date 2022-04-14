################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/E2PROM/I2C_Slave_EEPROM.c 

OBJS += \
./HAL/E2PROM/I2C_Slave_EEPROM.o 

C_DEPS += \
./HAL/E2PROM/I2C_Slave_EEPROM.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/E2PROM/I2C_Slave_EEPROM.o: ../HAL/E2PROM/I2C_Slave_EEPROM.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/Hassan/STM32CubeIDE/C_Embedded/Drivers/HAL/Inc" -I"C:/Users/Hassan/STM32CubeIDE/C_Embedded/Drivers/stm32f103x6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/E2PROM/I2C_Slave_EEPROM.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

