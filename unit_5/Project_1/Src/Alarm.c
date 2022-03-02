/*
 * Alarm.c
 *
 *  Created on: Feb 28, 2022
 *      Author: Hassan
 */

#include "Alarm.h"

#define THRESHOLD 20

void (*Alarm_state)();
unsigned int Al_Pval = 1;
unsigned int Al_Signal = 0;

void Pres_val(int p){ //checks if pressure is high or normal
	Al_Pval = p;
	Alarm_state= (Al_Pval > THRESHOLD)? (STATE(High_Pressure)):(STATE(Norm_Pressure));
}

STATE_define_(High_Pressure){
	Alarm_state_id = High_Pressure;	//state name

	Al_Signal =0;	// state action
	Set_Alarm_actuator(Al_Signal);
	Delay(60000);
	Alarm_state=STATE(Norm_Pressure);
}

STATE_define_(Norm_Pressure){
	Alarm_state_id = Norm_Pressure;	//state name

	Al_Signal =1;	// state action
	Set_Alarm_actuator(Al_Signal);
	Delay(60000);
	Alarm_state=STATE(Norm_Pressure);
}


