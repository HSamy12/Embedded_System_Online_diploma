/*
 ******************************************************************************
 * @file           : main.c
 * @author         : Hassan Samy
 * @brief          : toggle led program
 ******************************************************************************
 */
#include "Plat_type.h"

#define RCC_BASE	0x40021000
#define PortA_BASE 	0x40010800

#define RCC_CR		*(vuint32_t*) (RCC_BASE + 0x00)
#define RCC_CFGR	*(vuint32_t*) (RCC_BASE + 0x04)
#define RCC_APB2ENR	*(vuint32_t*) (RCC_BASE + 0x18)
#define GPIO_CRH 	*(vuint32_t*) (PortA_BASE + 0x04)
#define GPIO_ODR 	*(vuint32_t*) (PortA_BASE + 0x0C)

void clk_init(){
	RCC_CR   |=(0b1<<0);	// HSION value 1 (HSI ON)

	RCC_CFGR |=(0b0<<16); 	// PLLSRC value 0 (use HSI/2 input to PLL)
	RCC_CFGR |=(0b0110<<18);// PLLMUL value 0110 (x8)
	RCC_CR   |=(0b1<<24);	// PLLON value 1 (PLL ON)

	RCC_CFGR |=(0b10<<0); 	// SYSCLK value 10 (use PLL)
	RCC_CFGR |=(0b100<<8); 	// PPRE1 value 100 (prescaler /2)
	RCC_CFGR |=(0b101<<11);	// PPRE2 value 101 (prescaler /4)
}

int main(void){
	clk_init();

	RCC_APB2ENR |= (1<<2);	//GPIOA CLK is on

	GPIO_CRH &= 0xff0fffff;
	GPIO_CRH |= 0x00200000;
	while(1)
	{
		GPIO_ODR |= 1 << 13; // set bit 13
		for(uint32_t count = 0; count < 5000; count++);
		GPIO_ODR &= ~(1 << 13); // clear bit 13
		for(uint32_t count = 0; count < 5000; count++);

	}
	return 0;
}
