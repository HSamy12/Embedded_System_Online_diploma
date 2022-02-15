/*
 ******************************************************************************
 * @file           : main.c
 * @author         : Hassan Samy
 * @brief          : toggle led program
 ******************************************************************************
 */
#include "Plat_type.h"

#define SYSCTL 	0x400FE000
#define GPIOF 	0x40025000
#define SYSCTL_RCGC2_R	 	(*(v_uint32 *)(SYSCTL+ 0x108))
#define GPIOF_DIR_R			(*(v_uint32 *)(GPIOF + 0x400))
#define GPIOF_DEN_R			(*(v_uint32 *)(GPIOF + 0x51C))
#define GPIOF_DATA_R		(*(v_uint32 *)(GPIOF + 0x3FC))



int main(void){
	SYSCTL_RCGC2_R = 0x00000020;
	v_uint32 i;
	for(i =0;i<200;i++);
	GPIOF_DIR_R |= (1<<3);
	GPIOF_DEN_R |= (1<<3);
	
	while(1){
		GPIOF_DATA_R |=(1<<3);
		for(i =0;i<500000;i++);

		GPIOF_DATA_R &=~(1<<3);
		for(i = 0;i<500000;i++);
	}
	return 0;
}
