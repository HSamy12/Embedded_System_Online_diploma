/*
 * unit7_lesson1.c
 *
 * Created: 3/21/2022 5:06:56 PM
 *  Author: Hassan
 */ 

#include <util/delay.h>
#define IO_BASE    0x20
#define PIND    *(volatile unsigned char*)(IO_BASE + 0x10)
#define DDRD    *(volatile unsigned char*)(IO_BASE + 0x11)
#define PORTD   *(volatile unsigned char*)(IO_BASE + 0x12)


void GPIO_init(void){
	//set pin 4, 5 ,6 ,7 as outputs
	DDRD |=(1<<4); 
	DDRD |=(1<<5);
	DDRD |=(1<<6);
	DDRD |=(1<<7);
}
void w8_ms(int t){
	int i,j;
	for(i=0;i<t;i++)
		for(j=0;j<50000;j++);
}

int main(void)
{
	GPIO_init();

	while(1){
		// LED on pin 5 ON
		PORTD|=(1<<5);
		_delay_ms(2000);
		PORTD&=~(1<<5);
		// LED on pin 6 ON
		PORTD|=(1<<6);
		_delay_ms(2000);
		PORTD&=~(1<<6);
		// LED on pin 7 ON
		PORTD|=(1<<7);
		_delay_ms(2000);
		PORTD&=~(1<<7);
		// Buzzer on pin 4 ON
		PORTD|=(1<<4);
		_delay_ms(4000);
		PORTD&=~(1<<4);
	}
}

