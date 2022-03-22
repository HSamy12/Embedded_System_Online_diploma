/*
 * task3.c
 *
 * Created: 3/22/2022 5:06:56 PM
 *  Author: Hassan
 */ 
 
#include <util/delay.h>
#define IO_BASE    0x20
#define PIND    *(volatile unsigned char*)(IO_BASE + 0x10)
#define DDRD    *(volatile unsigned char*)(IO_BASE + 0x11)
#define PORTD   *(volatile unsigned char*)(IO_BASE + 0x12)


void GPIO_init(void){
	//set PD0 as input
	DDRD &=~(1<<0);
	// set pin 0 to Tri-state (Hi-Z)
	PORTD &=~(1<<0);
	
	//set PD5, PD6, PD7 as output
	DDRD |=(1<<5);
	DDRD |=(1<<6);
	DDRD |=(1<<7);
}

int main(void)
{
	GPIO_init();
	int i=0;
	while(1){
		//when pressed the switch on PD0
		
		if(PIND&(1<<0)){
			i++;
			switch(i){
				case 1:
					// LED on PD5 ON
					PORTD|=(1<<5);
					break;
				case 2:
					// LED on PD6 ON
					PORTD|=(1<<6);
					break;
				case 3:
					// LED on PD7 ON
					PORTD|=(1<<7);
					break;
				default:
					// LED on PD5 ON
					PORTD^=(1<<5);
					PORTD^=(1<<6);
					PORTD^=(1<<7);
					i=0;
					break;
					
			}
		while(PIND&(1<<0));
		}
	}
}

