/*
 ******************************************************************************
 * @file           : main.c
 * @author         : Hassan Samy
 * @brief          : toggle led program
 ******************************************************************************
 */
#include "Plat_type.h"

#define Base_RCC 	0x40021000
#define GPIO_PORTA 	0x40010800
#define RCC_ABP2ENR *(v_uint32 *)(Base_RCC + 0x18)
#define GPIO_CRH	*(v_uint32 *)(GPIO_PORTA + 0x04)
#define GPIO_ORD	*(v_uint32 *)(GPIO_PORTA + 0x0C)

v_uint8 data[7]="asdf";

void main(void){
	RCC_ABP2ENR |= (1<<2);
	GPIO_CRH &= 0xFF0FFFFF;
	GPIO_CRH |= 0x00200000;
	uint32 i;
	while(1){
		GPIO_ORD |=(1<<13);
		for(i =0;i<5000;i++);

		GPIO_ORD &=~(1UL<<13);
		for(i = 0;i<5000;i++);
	}
}
