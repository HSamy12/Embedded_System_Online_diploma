/*
 * PWM.c
 *
 * Created: 4/18/2022 8:10:29 PM
 *  Author: Hassan
 */ 


#include <avr/io.h>
#include "MCAL/Timers/Timers.h"

void gpio_init(){
	DDRB |= (1U<<PB3);	//OC0 pin set as output
}

int main(void)
{
	gpio_init();
	TIMER0_CONFIG T_Cfg;
	T_Cfg.mode = PC_PWM;
	T_Cfg.clk = PRESCALING_CLK256;
	T_Cfg.polarity = normal;
	TIMER0_Init(&T_Cfg);
	
	TIMER0_SetDutyValue(25);//set a 25% duty cycle
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}