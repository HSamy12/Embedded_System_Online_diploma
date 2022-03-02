/*
 * PS_Driver.c
 *
 *  Created on: Feb 28, 2022
 *      Author: Hassan
 */

#include "PS_Driver.h"

void (*PS_state)();
unsigned int PS_Pval;

/*init function is inside GPIO initialization */


STATE_define_(PS_reading){

	PS_state_id = PS_reading;	//state name

	PS_Pval = getPressureVal(); // state action
	Pres_val(PS_Pval);
	PS_state = STATE(PS_waiting);
}

STATE_define_(PS_waiting){

	PS_state_id = PS_waiting;	//state name

	Delay( 80000 ); // state action

	PS_state = STATE(PS_reading);
}


