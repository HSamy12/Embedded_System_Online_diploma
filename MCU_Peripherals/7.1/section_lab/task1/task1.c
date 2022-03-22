/*
 * task1.c
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
	
	//set PD5 as output
	DDRD |=(1<<5);

}

int main(void)
{
	GPIO_init();

	while(1){
		//when pressed the switch on PD0
		
		if(PIND&(1<<0))
		// LED on PD5 ON
		PORTD^=(1<<5);
		while(PIND&(1<<0));
	}
}

