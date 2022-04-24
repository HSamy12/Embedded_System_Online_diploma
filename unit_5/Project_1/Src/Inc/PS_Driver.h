/*
 * PS_Driver.h
 *
 *  Created on: Feb 28, 2022
 *      Author: Hassan
 */

#ifndef PS_DRIVE_H_
#define PS_DRIVE_H_

#include "state.h"

enum{
	PS_reading,
	PS_waiting
}PS_state_id;

/* prototypes */
STATE_define_(PS_reading);
STATE_define_(PS_waiting);

/* ptr to function for states in PS */
extern void (*PS_state)();

#endif /* PS_DRIVE_H_ */
