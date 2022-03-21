/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body

 ******************************************************************************
 */
#include "Plat_type.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define RCC_BASE	0x40021000
#define RCC_APB2ENR	*(vuint32_t*)(RCC_BASE + 0x18)

#define PortA_BASE 	0x40010800
#define GPIOA_CRL 	*(vuint32_t*)(PortA_BASE + 0x00)
#define GPIOA_CRH 	*(vuint32_t*)(PortA_BASE + 0x04)
#define GPIOA_IDR 	*(vuint32_t*)(PortA_BASE + 0x08)
#define GPIOA_ODR 	*(vuint32_t*)(PortA_BASE + 0x0C)

#define PortB_BASE 	0x40010C00
#define GPIOB_CRL 	*(vuint32_t*)(PortB_BASE + 0x00)
#define GPIOB_CRH 	*(vuint32_t*)(PortB_BASE + 0x04)
#define GPIOB_IDR 	*(vuint32_t*)(PortB_BASE + 0x08)
#define GPIOB_ODR 	*(vuint32_t*)(PortB_BASE + 0x0C)


void clk_init(){
	// Enable clock to GPIO PORTA
	RCC_APB2ENR |= (1<<2);
	// Enable clock to GPIO PORTB
	RCC_APB2ENR |= (1<<3);
}

void GPIO_init(){
	// configuring pin A1 as floating input
	//reseting pin A1 CNF and MODE Bits
	GPIOA_CRL &=~(0b1111<<4);
	//setting to MODE 00:Input mode  and CNF 01:Floating input
	GPIOA_CRL |=(0b0100<<4);

	// configuring pin A13 as floating input
	//reseting pin A13 CNF and MODE Bits
	GPIOA_CRH &=~(0b1111<<20);
	//setting to MODE 00:Input mode  and CNF 01:Floating input
	GPIOA_CRH |=(0b0100<<20);

	// configuring pin B1 as Push Pull output
	//reseting pin B1 CNF and MODE Bits
	GPIOB_CRL &=~(0b1111<<4);
	//setting to MODE 01:Output mode 10MHz max and CNF 00:Push Pull output
	GPIOB_CRL |=(0b0001<<4);

	// configuring pin B13 as Push Pull output
	//reseting pin B13 CNF and MODE Bits
	GPIOB_CRH &=~(0b1111<<20);
	//setting to MODE 01:Output mode 10MHz max and CNF 00:Push Pull output
	GPIOB_CRH |=(0b0001<<20);
}

void wait_ms(uint32_t time){
	uint32_t i,j;
	for(i=0;i<time;i++)
		for(j=0;j<255;j++);
}

int main(void)
{
	clk_init();
	GPIO_init();

    /* Loop forever */
	while(1){
		if(!((GPIOA_IDR & (1<<1)) >>1)){
			GPIOB_ODR ^=(1<<1);
			while(!((GPIOA_IDR&(1<<1)) >>1)); //single pressing
		}

		if(((GPIOA_IDR & (1<<13)) >>13))	//multiple pressing
			GPIOB_ODR ^=(1<<13);

		wait_ms(1);
	}
}

