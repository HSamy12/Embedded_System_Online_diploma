/*
 ******************************************************************************
 * @file           : main.c
 * @author         : Hassan Samy
 * @brief          : toggle led program
 ******************************************************************************
 */
#include "Plat_type.h"

#define PortA_BASE 	0x40010800

#define GPIO_CRH 	*(vuint32_t*) (PortA_BASE + 0x04)
#define GPIO_ODR 	*(vuint32_t*) (PortA_BASE + 0x0C)
int main(void)
{
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
