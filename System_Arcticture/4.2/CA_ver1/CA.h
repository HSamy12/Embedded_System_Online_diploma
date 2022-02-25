/*
 * CA.h
 *
 *  Created on: Feb 23, 2022
 *      Author: Hassan
 */

#ifndef CA_H_
#define CA_H_

#include "state.h"

enum {
	CA_waiting,	CA_driving
}CA_state_id;

/* prototypes */
STATE_define_(CA_waiting);
STATE_define_(CA_driving);

/* ptr to function for states in main Alg. */
extern void (*CA_state)();

#endif /* CA_H_ */
