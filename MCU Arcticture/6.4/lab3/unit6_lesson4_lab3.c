/*
 * unit6_lesson4_lab3.c
 *
 * Created: 3/18/2022 4:04:16 PM
 *  Author: Hassan
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//define of SREG (status register)
#define SREG    _SFR_IO8(0x3F)

void GPIO_init(void){
	//direction PORTD pin 2 as input & pin 7 as output
	DDRD&=~(1<<DDD2);
	DDRD|=(1<<DDD7);
}

void EXTI_init(){
	
	MCUCR |=(1<<ISC00);
	GICR |=(1<<INT0);
	SREG |=(1<<7);
}

int main(void)
{	
	GPIO_init();
	EXTI_init();
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}

ISR(INT0_vect)
{
	//LED ON
	PORTD|= (1<<PD7);
	_delay_ms(1000);
	//LED OFF
	PORTD&=~(1<<PD7);
}