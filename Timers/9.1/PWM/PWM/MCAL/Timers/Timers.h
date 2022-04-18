/*
 * Timers.h
 *
 * Created: 4/18/2022 9:57:51 PM
 *  Author: Hassan
 *	Note: This driver includes only PWM modes for Timer0 on the Atmega32
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

#define F_CPU 8000000UL
/**********************************
*	Include
**********************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>


/**********************************
*	refernces Enums
**********************************/
typedef enum
{	/*	references to WGM01:00 bits */
	PC_PWM = 0x40,
	Fast_PWM = 0x48
}TIMER0_MODE_t;
//WGM01	WGM00	Description
// 0	 0		Normal
// 0	 1		PWM, Phase Correct
// 1	 0		CTC
// 1	 1		Fast PWM


typedef enum
{	/*	references to COM01:00 bits */
	normal = 0x20,
	inverted = 0x30
}TIMER0_PWM_Polarity_t;
//COM01 COM00	Description
//0		0		Normal port operation, OC0 disconnected.
//0		1		Reserved
//1		0		Clear OC0 on compare match, set OC0 at BOTTOM,(nin-inverting mode)
//1		1		Set OC0 on compare match, clear OC0 at BOTTOM,(inverting mode)

typedef enum
{
	NO_CLK_SRC,
	NO_PRESCALING,
	PRESCALING_CLK8,
	PRESCALING_CLK64,
	PRESCALING_CLK256,
	PRESCALING_CLK1024,
	EXT_CLK_FALLING,
	EXT_CLK_RISING,
}TIMER0_CLOCK_t;

/**********************************
*	Configure structure
**********************************/
typedef struct
{
	TIMER0_MODE_t mode;
	TIMER0_CLOCK_t clk;
	TIMER0_PWM_Polarity_t polarity;
}TIMER0_CONFIG;


/**********************************
*	APIs
**********************************/
void TIMER0_Init(TIMER0_CONFIG* configuartion);
void TIMER0_Deinit();

void TIMER0_GetCompareValue(uint8_t* pu8_TicksNumber);
void TIMER0_SetCompareValue(uint8_t u8_TicksNumber);

void TIMER0_GetDutyValue(uint8_t* pu8_Duty);
void TIMER0_SetDutyValue(uint8_t u8_Duty);

void TIMER0_Get_FreqValue(TIMER0_CONFIG* configuartion,uint32_t* Fpwm);


#endif /* TIMERS_H_ */