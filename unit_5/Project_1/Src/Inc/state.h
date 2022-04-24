/*
 * state.h
 *
 *  Created on: Feb 28, 2022
 *      Author: Hassan
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdio.h>
#include <stdlib.h>
#include "driver.h"

/*macro define for the states */
#define STATE_define_(StateFunc) void ST_##StateFunc()
#define STATE(StateFunc) 	ST_##StateFunc


/* states connections */
void Pres_val(int p);

#endif /* STATE_H_ */
