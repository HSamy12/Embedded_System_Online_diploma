/*
 * Alarm.h
 *
 *  Created on: Feb 28, 2022
 *      Author: Hassan
 */

#ifndef ALARM_H_
#define ALARM_H_

#include "state.h"

enum{
	High_Pressure,
	Norm_Pressure
}Alarm_state_id;

/* prototypes */
STATE_define_(High_Pressure);
STATE_define_(Norm_Pressure);

/* ptr to function for states in Alarm */
extern void (*Alarm_state)();

#endif /* ALARM_H_ */
