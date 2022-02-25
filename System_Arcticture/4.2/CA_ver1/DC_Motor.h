/*
 * DC_Motor.h
 *
 *  Created on: Feb 25, 2022
 *      Author: Hassan
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "state.h"

enum {
	DC_idle,	DC_busy
}DC_state_id;

/* prototypes */
void DC_init();
STATE_define_(DC_idle);
STATE_define_(DC_busy);

/* ptr to function for states in DC */
extern void (*DC_state)();

#endif /* DC_MOTOR_H_ */
