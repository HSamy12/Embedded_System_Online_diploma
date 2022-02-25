/*
 * US_Sensor.h
 *
 *  Created on: Feb 25, 2022
 *      Author: Hassan
 */

#ifndef US_SENSOR_H_
#define US_SENSOR_H_

#include "state.h"

enum{
	US_busy
}US_state_id;

/* prototypes */
void US_init();
STATE_define_(US_busy);

/* ptr to function for states in US */
extern void (*US_state)();

#endif /* US_SENSOR_H_ */
