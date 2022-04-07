################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32f103x6_Drivers/GPIO/stm32f103x6_gpio_driver.c 

OBJS += \
./stm32f103x6_Drivers/GPIO/stm32f103x6_gpio_driver.o 

C_DEPS += \
./stm32f103x6_Drivers/GPIO/stm32f103x6_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
stm32f103x6_Drivers/GPIO/stm32f103x6_gpio_driver.o: ../stm32f103x6_Drivers/GPIO/stm32f103x6_gpio_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/Hassan/STM32CubeIDE/C_Embedded/Drivers/HAL/Inc" -I"C:/Users/Hassan/STM32CubeIDE/C_Embedded/Drivers/stm32f103x6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32f103x6_Drivers/GPIO/stm32f103x6_gpio_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

