/*
 * state.h
 *
 *  Created on: Feb 23, 2022
 *      Author: Hassan
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdio.h>
#include <stdlib.h>

/*macro define for the states */
#define STATE_define_(StateFunc) void ST_##StateFunc()
#define STATE(StateFunc) 	ST_##StateFunc


/* states connections */
void US_get_distance(int d);
void DC_motor(int s);

#endif /* STATE_H_ */
