/*
 * Timers.c
 *
 * Created: 4/18/2022 9:59:02 PM
 *  Author: Hassan
 */ 

#include "Timers.h"

/**********************************
*	Generic variables
**********************************/
TIMER0_CONFIG* TIMER0_Configurations = NULL;


/**********************************
*	APIs Implementations
**********************************/
void TIMER0_Init(TIMER0_CONFIG* configuartion){
	//intualizing
	TIMER0_Configurations = configuartion;
	
	//choosing the mode
	TCCR0 |= TIMER0_Configurations->mode;
	//choosing clk prescaler
	TCCR0 |= TIMER0_Configurations->clk;	
	// choosing the polarity for CO0 pin 
	TCCR0 |= TIMER0_Configurations->polarity;
}

void TIMER0_Deinit(){
	TIMER0_Configurations = NULL;
	TIMSK = 0x00;
}


void TIMER0_GetCompareValue(uint8_t* pu8_TicksNumber){
	
		*pu8_TicksNumber = OCR0;
}

void TIMER0_SetCompareValue(uint8_t u8_TicksNumber){
		OCR0 = u8_TicksNumber;
}

void TIMER0_GetDutyValue(uint8_t* pu8_Duty){
	uint8_t CmpVal =0;
	TIMER0_GetCompareValue(&CmpVal);
	*pu8_Duty = (CmpVal*100)/255;
}

void TIMER0_SetDutyValue(uint8_t u8_Duty){
	uint8_t CmpVal = (255* u8_Duty)/(100);
	 TIMER0_SetCompareValue(CmpVal);
}

void TIMER0_Get_FreqValue(TIMER0_CONFIG* configuartion,uint32_t* Fpwm){
	uint16_t prscaler = 0;
	switch (configuartion->clk)
	{
		case NO_CLK_SRC:	TIMER0_Deinit();		break; // No clock source (Timer/Counter stopped)
		case NO_PRESCALING:		prscaler = 1;		break; //clkI/O (No prescaling)
		case PRESCALING_CLK8:	prscaler = 8;		break; //clkI/O/8 (From prescaler)
		case PRESCALING_CLK64:	prscaler = 16;		break; //clkI/O/64 (From prescaler)
		case PRESCALING_CLK256: prscaler = 256;		break; //clkI/O/256 (From prescaler)
		case PRESCALING_CLK1024:prscaler = 1024;	break; // clkI/O/1024 (From prescaler)
		default:				prscaler = 1;		break; //External clock source on T0 pin. Clock on falling edge/rising edge
	}

	if(configuartion->mode == Fast_PWM){
		*Fpwm = (F_CPU)/(256*prscaler);
	}
	else{	//case of phase correct PWM
		*Fpwm = (F_CPU)/(510*prscaler);
	}
}
