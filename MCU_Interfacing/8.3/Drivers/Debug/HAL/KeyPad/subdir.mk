################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KeyPad/keypad.c 

OBJS += \
./HAL/KeyPad/keypad.o 

C_DEPS += \
./HAL/KeyPad/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/KeyPad/keypad.o: ../HAL/KeyPad/keypad.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/Hassan/STM32CubeIDE/C_Embedded/Drivers/HAL/Inc" -I"C:/Users/Hassan/STM32CubeIDE/C_Embedded/Drivers/stm32f103x6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/KeyPad/keypad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

