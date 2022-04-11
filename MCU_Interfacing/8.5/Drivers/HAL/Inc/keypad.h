/*
 * keypad.h
 *
 *  Created on: Mar 26, 2022
 *      Author: Hassan
 */
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "stm32f103x6.h"
#include "stm32f103x6_gpio_driver.h"


#define R0 GPIO_Pin_0
#define R1 GPIO_Pin_1
#define R2 GPIO_Pin_3
#define R3 GPIO_Pin_4
#define C0 GPIO_Pin_5
#define C1 GPIO_Pin_6
#define C2 GPIO_Pin_7
#define C3 GPIO_Pin_8

#define KEYPAD_PORT GPIOB

void Keypad_init();
char Keypad_getkey();

#endif /* KEYPAD_H_ */
