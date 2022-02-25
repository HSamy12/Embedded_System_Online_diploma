/*
 * DC_Motor.c
 *
 *  Created on: Feb 25, 2022
 *      Author: Hassan
 */


#include "DC_Motor.h"

unsigned int DC_speed;
void (* DC_state)();

void DC_init(){
	printf("\n======DC initialized======\n");
}

STATE_define_(DC_idle){
	DC_state_id = DC_idle;	//state name

	printf("DC_idle state: DC_speed=%d  \n",DC_speed);
}

STATE_define_(DC_busy){
	DC_state_id = DC_busy;	//state name

	DC_state = STATE(DC_idle);	//state action
	printf("DC_busy state: DC_speed=%d  \n",DC_speed);
}

void DC_motor(int s){
	DC_speed =s;
	DC_state = STATE(DC_busy);
	printf("CA send DC_speed %d to DC \n",DC_speed);
}
