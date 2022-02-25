/*
 * US_sensor.c
 *
 *  Created on: Feb 25, 2022
 *      Author: Hassan
 */


#include "US_Sensor.h"

void (*US_state)();

unsigned int US_distance;


int generate_random(int l,int r){ // generate random value between l and r

	int rand_num =(rand()%(r-l+1))+l;
	return rand_num;
}

void US_init(){
	printf("\n======US initialized======\n");
}

STATE_define_(US_busy){

	US_state_id = US_busy;	//state name

	US_distance = generate_random(45,55);	//state action
	printf("US_busy state: US_distance =%d\n",US_distance);

	US_get_distance(US_distance);
	US_state = STATE(US_busy);
}

