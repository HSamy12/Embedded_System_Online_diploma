/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
#include "Plat_type.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define RCC_BASE	0x40021000
#define RCC_APB2ENR	*(vuint32_t*) (RCC_BASE + 0x18)

#define PortA_BASE 	0x40010800
#define GPIO_CRL 	*(vuint32_t*) (PortA_BASE + 0x00)
#define GPIO_CRH 	*(vuint32_t*) (PortA_BASE + 0x04)
#define GPIO_ODR 	*(vuint32_t*) (PortA_BASE + 0x0C)

#define AFIO_BASE 	0x40010000
#define AFIO_EXTICR1 	*(vuint32_t*) (AFIO_BASE + 0x08)


#define EXTI_BASE 	0x40010400
#define EXTI_IMR 	*(vuint32_t*) (EXTI_BASE + 0x00)
#define EXTI_RTSR 	*(vuint32_t*) (EXTI_BASE + 0x08)
#define EXTI_PR 	*(vuint32_t*) (EXTI_BASE + 0x14)

#define NVIC_ISER0 	*(vuint32_t*) (0xE000E100)


void clk_init(){
	// Connect clock to AFIO
	RCC_APB2ENR |= (1<<0);
	// Connect clock to GPIO
	RCC_APB2ENR |= (1<<2);
}

void GPIO_init(){
	// PORTA pin 0 works as Floating input
	GPIO_CRL &=0xFFFFFFF0;
	GPIO_CRL |=0x00000004;
	// PORTA pin 13 works as output with Max frequency 2MHz
	GPIO_CRH &=0xFF0FFFFF;
	GPIO_CRH |=0x00200000;
	//PORTA is used as source input for EXTI0
	AFIO_EXTICR1 &=0xFFFFFFF0;
}

void EXTI_init(){
	// enable rising edge trigger for EXTI at line 0
	EXTI_RTSR |= (1<<0);
	// enable interrupt mask for EXTI at line 0
	EXTI_IMR |= (1<<0);
	//enable NVIC IRQ6 (EXTI0)
	NVIC_ISER0 |= (1<<6);
}

int main(void)
{
	clk_init();
	GPIO_init();
	EXTI_init();

    /* Loop forever */
	while(1);
}

void EXTI0_IRQHandler(void){
	//toggle led at PA13
	GPIO_ODR ^= (1<<13);

	//clear pending interrupt request
	EXTI_PR |=(1<<0);
}