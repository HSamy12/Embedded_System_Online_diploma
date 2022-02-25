/*
 * main.c
 *
 *  Created on: Feb 23, 2022
 *      Author: Hassan
 */

#include "DC_Motor.h"
#include "US_Sensor.h"
#include "CA.h"

void setup(){

	DC_init();
	US_init();

	CA_state = STATE(CA_waiting);
	DC_state = STATE(DC_idle);
	US_state = STATE(US_busy);
}

int main(){

	volatile int index;

	setup();

	while(1){
		 US_state();
		 CA_state();
		 DC_state();

		 for(index=0;index < 1000000; index ++);
	 }
}
