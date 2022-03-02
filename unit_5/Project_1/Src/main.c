/*
 * main.c
 *
 *  Created on: Feb 28, 2022
 *      Author: Hassan
 */
 
#include "PS_Driver.h"
#include "Alarm.h"


void setup(){
	GPIO_INITIALIZATION();

	Alarm_state = STATE(Norm_Pressure);
	PS_state = STATE(PS_reading);
}

int main (){

	setup();

	while (1){
		PS_state();
		Alarm_state();
	}
}
