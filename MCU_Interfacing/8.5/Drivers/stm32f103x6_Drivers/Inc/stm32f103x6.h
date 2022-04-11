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
// Base address for ABP1 Peripheral
//===============================
//USART
#define USART2_BASE								0x40004400UL
#define USART3_BASE								0x40004800UL

//SPI
#define SPI2_BASE								0x40003800UL

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

//USART
#define USART1_BASE								0x40013800UL

//SPI
#define SPI1_BASE								0x40013000UL

//===============================
// Internal NVIC Addresses
//===============================
#define NVIC_Base								0xE000E100UL

#define NVIC_ISER0					*(volatile uint32_t *)(NVIC_Base + 0x0)
#define NVIC_ISER1					*(volatile uint32_t *)(NVIC_Base + 0x4)
#define NVIC_ISER2					*(volatile uint32_t *)(NVIC_Base + 0x8)
#define NVIC_ICER0					*(volatile uint32_t *)(NVIC_Base + 0x80)
#define NVIC_ICER1					*(volatile uint32_t *)(NVIC_Base + 0x84)
#define NVIC_ICER2					*(volatile uint32_t *)(NVIC_Base + 0x88)


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
	volatile uint32_t EXTICR[4];
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

//===============================
// Peripheral register: USART
//===============================
typedef struct{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR[3];
	volatile uint32_t GTPR;
}USART_TypeDef;

//===============================
// Peripheral register: SPI
//===============================
typedef struct{
	volatile uint32_t CR[2];	//0x00 , 0x04
	volatile uint32_t SR;		//0x08
	volatile uint32_t DR;		//0x0C
	volatile uint32_t CRCPR;	//0x10
	volatile uint32_t RXCRCR;	//0x14
	volatile uint32_t TXCRCR;	//0x18
	volatile uint32_t I2SCFGR;	//0x1C
	volatile uint32_t I2SPR;	//0x20
}SPI_TypeDef;

/**************************************************************************************/
// Peripheral instants:
//********************************
//RCC
#define RCC						((RCC_TypeDef *)RCC_BASE)

//GPIO
#define GPIOA					((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB					((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC					((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD					((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE					((GPIO_TypeDef *)GPIOE_BASE)

//AFIO
#define AFIO					((AFIO_TypeDef *)AFIO_BASE)

//EXTI
#define EXTI					((EXTI_TypeDef *)EXTI_BASE)

//USART
#define USART1					((USART_TypeDef *)USART1_BASE)
#define USART2					((USART_TypeDef *)USART2_BASE)
#define USART3					((USART_TypeDef *)USART3_BASE)

//SPI
#define SPI1					((SPI_TypeDef *)SPI1_BASE)
#define SPI2					((SPI_TypeDef *)SPI2_BASE)


/**************************************************************************************/
// generic Macros
//********************************
//===============================
// IVT Macros
//===============================
//EXTI
#define EXTI0_IRQ			6
#define EXTI1_IRQ			7
#define EXTI2_IRQ			8
#define EXTI3_IRQ			9
#define EXTI4_IRQ			10
#define EXTI5_IRQ			23
#define EXTI6_IRQ			23
#define EXTI7_IRQ			23
#define EXTI8_IRQ			23
#define EXTI9_IRQ			23
#define EXTI10_IRQ			40
#define EXTI11_IRQ			40
#define EXTI12_IRQ			40
#define EXTI13_IRQ			40
#define EXTI14_IRQ			40
#define EXTI15_IRQ			40
//SPI
#define SPI1_IRQ			35
#define SPI2_IRQ			36
//USART
#define USART1_IRQ			37
#define USART2_IRQ			38
#define USART3_IRQ			39


//===============================
// RCC Clock enable macros
//===============================
//GPIO
#define RCC_GPIOA_CLK_EN() 	(RCC->APB2ENR |= (1<<2))
#define RCC_GPIOB_CLK_EN() 	(RCC->APB2ENR |= (1<<3))
#define RCC_GPIOC_CLK_EN() 	(RCC->APB2ENR |= (1<<4))
#define RCC_GPIOD_CLK_EN() 	(RCC->APB2ENR |= (1<<5))
#define RCC_GPIOE_CLK_EN() 	(RCC->APB2ENR |= (1<<6))
//AFIO
#define RCC_AFIO_CLK_EN()  	(RCC->APB2ENR |= (1<<0))
//USART
#define RCC_USART1_CLK_EN()  	(RCC->APB2ENR |= (1<<14))
#define RCC_USART2_CLK_EN()  	(RCC->APB1ENR |= (1<<17))
#define RCC_USART3_CLK_EN()  	(RCC->APB1ENR |= (1<<18))
//SPI
#define RCC_SPI1_CLK_EN()  	(RCC->APB2ENR |= (1<<12))
#define RCC_SPI2_CLK_EN()  	(RCC->APB1ENR |= (1<<14))

//===============================
// RCC Reset macros
//===============================
//GPIO
#define RCC_GPIOA_RESET() 		(RCC->APB2RSTR |= (1<<2))
#define RCC_GPIOB_RESET() 		(RCC->APB2RSTR |= (1<<3))
#define RCC_GPIOC_RESET()	 	(RCC->APB2RSTR |= (1<<4))
#define RCC_GPIOD_RESET() 		(RCC->APB2RSTR |= (1<<5))
#define RCC_GPIOE_RESET() 		(RCC->APB2RSTR |= (1<<6))
//AFIO
#define RCC_AFIO_RESET()  		(RCC->APB2RSTR |= (1<<0))
//USART
#define RCC_USART1_RESET()  	(RCC->APB2RSTR |= (1<<14))
#define RCC_USART2_RESET()  	(RCC->APB1RSTR |= (1<<17))
#define RCC_USART3_RESET()  	(RCC->APB1RSTR |= (1<<18))
//SPI
#define RCC_SPI1_RESET()  	(RCC->APB2RSTR |= (1<<12))
#define RCC_SPI2_RESET()  	(RCC->APB1RSTR |= (1<<14))


//===============================
// NVIC IRQ Enable/Disable Macros:
//===============================
//EXTI
#define NVIC_IRQ6_EXTI0_Enable				(NVIC_ISER0 |= 1<<EXTI0_IRQ)
#define NVIC_IRQ7_EXTI1_Enable				(NVIC_ISER0 |= 1<<EXTI1_IRQ)
#define NVIC_IRQ8_EXTI2_Enable				(NVIC_ISER0 |= 1<<EXTI2_IRQ)
#define NVIC_IRQ9_EXTI3_Enable				(NVIC_ISER0 |= 1<<EXTI3_IRQ)
#define NVIC_IRQ10_EXTI4_Enable				(NVIC_ISER0 |= 1<<EXTI4_IRQ)
#define NVIC_IRQ23_EXTI5_9_Enable			(NVIC_ISER0 |= 1<<EXTI5_IRQ)
#define NVIC_IRQ40_EXTI10_15_Enable			(NVIC_ISER1 |= 1<<(EXTI10_IRQ-32))		//40-32 = 8

#define NVIC_IRQ6_EXTI0_Disable				(NVIC_ICER0 |= 1<<EXTI0_IRQ)
#define NVIC_IRQ7_EXTI1_Disable				(NVIC_ICER0 |= 1<<EXTI1_IRQ)
#define NVIC_IRQ8_EXTI2_Disable				(NVIC_ICER0 |= 1<<EXTI2_IRQ)
#define NVIC_IRQ9_EXTI3_Disable				(NVIC_ICER0 |= 1<<EXTI3_IRQ)
#define NVIC_IRQ10_EXTI4_Disable			(NVIC_ICER0 |= 1<<EXTI4_IRQ)
#define NVIC_IRQ23_EXTI5_9_Disable			(NVIC_ICER0 |= 1<<EXTI5_IRQ)
#define NVIC_IRQ40_EXTI10_15_Disable		(NVIC_ICER1 |= 1<<(EXTI10_IRQ-32))		//40-32 = 8

//USART
#define NVIC_IRQ37_USART1_Enable				(NVIC_ISER1 |= 1<<(USART1_IRQ-32))	//37-32 = 5
#define NVIC_IRQ38_USART2_Enable				(NVIC_ISER1 |= 1<<(USART2_IRQ-32))	//38-32 = 6
#define NVIC_IRQ39_USART3_Enable				(NVIC_ISER1 |= 1<<(USART3_IRQ-32))	//39-32 = 7

#define NVIC_IRQ37_USART1_Disable				(NVIC_ICER1 |= 1<<(USART1_IRQ-32))	//37-32 = 5
#define NVIC_IRQ38_USART2_Disable				(NVIC_ICER1 |= 1<<(USART2_IRQ-32))	//38-32 = 6
#define NVIC_IRQ39_USART3_Disable				(NVIC_ICER1 |= 1<<(USART3_IRQ-32))	//39-32 = 7

//SPI
#define NVIC_IRQ35_SPI1_Enable				(NVIC_ISER1 |= 1<<(SPI1_IRQ-32))		//35-32 = 3
#define NVIC_IRQ36_SPI2_Enable				(NVIC_ISER1 |= 1<<(SPI2_IRQ-32))		//36-32 = 4

#define NVIC_IRQ35_SPI1_Disable				(NVIC_ICER1 |= 1<<(SPI1_IRQ-32))		//35-32 = 3
#define NVIC_IRQ36_SPI2_Disable				(NVIC_ICER1 |= 1<<(SPI2_IRQ-32))		//36-32 = 4

#endif /* INC_STM32F103X6_H_ */

