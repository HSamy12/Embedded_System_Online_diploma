/*
 * GPIO.c
 *
 * Created: 3/30/2022 6:42:51 PM
 *  Author: Hassan
 */ 

#include "AVRMemoryMap.h"


void Port_Direction(unsigned char base,unsigned char state){
	if(state == output)
		*(volatile unsigned char*)(base-1)=0xFF;
	else
		*(volatile unsigned char*)(base-1)=0x00;
}

void Pin_Direction(unsigned char base,unsigned char pin,unsigned char state){
	if(state == output)
	*(volatile unsigned char*)(base-1)|=(1<<pin);
	else
	*(volatile unsigned char*)(base-1)&= ~(1<<pin);
}