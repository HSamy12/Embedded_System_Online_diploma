/*
 * CA.c
 *
 *  Created on: Feb 23, 2022
 *      Author: Hassan
 */


#include "CA.h"

int CA_distance =0;
int CA_speed =0;
int CA_threshold =50;

void (*CA_state)();


void US_get_distance(int d){
	CA_distance =d;
	(CA_distance <= CA_threshold)? (CA_state = STATE(CA_waiting)):(CA_state = STATE(CA_driving));
	printf("US sent distance %d to AC \n",CA_distance);
}

STATE_define_(CA_waiting){

	CA_state_id = CA_waiting;	//state name

	CA_speed = 0;	// state action
	DC_motor(CA_speed);
}

STATE_define_(CA_driving){

	CA_state_id = CA_driving;	//state name
	printf("CA_driving state: CA_distance =%d ,CA_speed=%d  \n",CA_distance,CA_speed);

	CA_speed = 30;	// state action
	DC_motor(CA_speed);
}
