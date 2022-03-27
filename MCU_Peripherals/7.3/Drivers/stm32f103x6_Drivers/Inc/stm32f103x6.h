/*
 * stm32f103x6.h
 *
 *  Created on: Mar 26, 2022
 *      Author: Hassan Samy
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//********************************
// Includes
//********************************
#include <stdlib.h>
#include <stdint.h>

/**************************************************************************************/
// Base addresses
//********************************


//===============================
// Base addresses for memory
//===============================
#define FLASH_Memory_BASE						0x08000000UL
#define SYSTEM_Memory_BASE						0x1FFFF000UL
#define SRAM_Memory_BASE						0x20000000UL

#define Peripheral_BASE							0x40000000UL

#define Cortex_M3_Internal_Peripheral_BASE		0xE0000000UL

//===============================
// Base address for AHB Peripheral
//===============================
//RCC
#define RCC_BASE								0x40021000UL

//===============================
// Base address for ABP2 Peripheral
//===============================
//GPIO
//A,B fully included in LQFB48
#define GPIOA_BASE								0x40010800UL
#define GPIOB_BASE								0x40010C00UL

//C,D partially included in LQFB48
#define GPIOC_BASE								0x40011000UL
#define GPIOD_BASE								0x40011400UL

//E not included in LQFB48
#define GPIOE_BASE								0x40011800UL

// AFIO
#define AFIO_BASE								0x40010000UL

// EXTI
#define EXTI_BASE								0x40010400UL


//===============================
// Base address for ABP1 Peripheral
//===============================


/**************************************************************************************/
// Peripheral registers:
//********************************

//===============================
// Peripheral register: RCC
//===============================
typedef struct{
	volatile uint32_t CR;			//0x00
	volatile uint32_t CFGR;			//0x04
	volatile uint32_t CIR;			//0x08
	volatile uint32_t APB2RSTR;		//0x0C
	volatile uint32_t APB1RSTR;		//0x10
	volatile uint32_t AHBENR;		//0x14
	volatile uint32_t APB2ENR;		//0x18
	volatile uint32_t APB1ENR;		//0x1C
	volatile uint32_t BDCR;			//0x20
	volatile uint32_t CSR;			//0x24
	volatile uint32_t AHBSTR;		//0x28
	volatile uint32_t CFGR2;		//0x2C
}RCC_TypeDef;

//===============================
// Peripheral register: GPIO
//===============================
typedef struct{
	volatile uint32_t CRL;	//0x00
	volatile uint32_t CRH;	//0x04
	volatile uint32_t IDR;	//0x08
	volatile uint32_t ODR;	//0x0C
	volatile uint32_t BSRR;	//0x10
	volatile uint32_t BRR;	//0x14
	volatile uint32_t LCKR;	//0x18
}GPIO_TypeDef;

//===============================
// Peripheral register: AFIO
//===============================
typedef struct{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t RESERVED0;
	volatile uint32_t MAPR2;
}AFIO_TypeDef;

//===============================
// Peripheral register: EXTI
//===============================
typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_TypeDef;


/**************************************************************************************/
// Peripheral instants:
//********************************
#define RCC						((RCC_TypeDef *)RCC_BASE)

#define GPIOA					((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB					((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC					((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD					((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE					((GPIO_TypeDef *)GPIOE_BASE)

#define AFIO					((AFIO_TypeDef *)AFIO_BASE)

#define EXTI					((EXTI_TypeDef *)EXTI_BASE)


/**************************************************************************************/
// Clock enable macros
//********************************
#define RCC_GPIOA_CLK_EN() 	(RCC->APB2ENR |= (1<<2))
#define RCC_GPIOB_CLK_EN() 	(RCC->APB2ENR |= (1<<3))
#define RCC_GPIOC_CLK_EN() 	(RCC->APB2ENR |= (1<<4))
#define RCC_GPIOD_CLK_EN() 	(RCC->APB2ENR |= (1<<5))
#define RCC_GPIOE_CLK_EN() 	(RCC->APB2ENR |= (1<<6))

#define RCC_AFIO_CLK_EN()  	(RCC->APB2ENR |= (1<<0))



/**************************************************************************************/
// generic Macros
//********************************


#endif /* INC_STM32F103X6_H_ */

