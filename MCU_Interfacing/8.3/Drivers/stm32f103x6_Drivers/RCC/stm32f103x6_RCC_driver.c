/*
 * stm32f103x6_RCC_driver.c
 *
 *  Created on: Apr 6, 2022
 *      Author: Hassan
 */

#include "stm32f103x6_RCC_driver.h"

//Set and cleared by software to control the division factor of the AHB clock.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2			2^1
//1001: SYSCLK divided by 4			2^2
//1010: SYSCLK divided by 8			2^3
//1011: SYSCLK divided by 16		2^4
//1100: SYSCLK divided by 64		2^6
//1101: SYSCLK divided by 128		2^7
//1110: SYSCLK divided by 256		2^8
//1111: SYSCLK divided by 512		2^9
const uint8_t AHBPreSc_Table[16] = {0,0,0,0,0,0,0,0,1,2,3,4,6,7,8,9};

//Set and cleared by software to control the division factor of the APB low-speed clock
//(PCLK1).
//Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
//0xx: HCLK not divided
//100: HCLK divided by 2			2^1
//101: HCLK divided by 4			2^2
//110: HCLK divided by 8			2^3
//111: HCLK divided by 16			2^4
const uint8_t APBPreSc_Table[8] = {0,0,0,0,1,2,3,4};


/**************************************************************************************/
// APIs
//********************************
uint32_t MCAL_RCC_GetSYS_ClkFreq(){
	//	Bits 3:2 SWS: System clock switch status
	//	Set and cleared by hardware to indicate which clock source is used as system clock.
	//	00: HSI oscillator used as system clock
	//	01: HSE oscillator used as system clock
	//	10: PLL used as system clock
	//	11: not applicable
	switch ((RCC->CFGR >>2) & 0b11 ){
	case 0:		//	00: HSI oscillator used as system clock
		return HSI_RC_clk;
		break;
	case 1:		//	01: HSE oscillator used as system clock
		return HSE_RC_clk;
		break;
	case 2:		//	10: PLL used as system clock
		return PLL_RC_clk;
		break;
	default:
		return HSI_RC_clk;
		break;
	}
}


uint32_t MCAL_RCC_GetHClkFreq(){
	//Bits 7:4 HPRE: AHB prescaler
	return MCAL_RCC_GetSYS_ClkFreq() >> AHBPreSc_Table[((RCC->CFGR >> 4) & 0b1111) ];
}


uint32_t MCAL_RCC_GetPClk1Freq(){
	//Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
	return MCAL_RCC_GetHClkFreq() >> APBPreSc_Table[((RCC->CFGR >> 8) & 0b111) ];
}


uint32_t MCAL_RCC_GetPClk2Freq(){
	//Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
	return MCAL_RCC_GetHClkFreq() >> APBPreSc_Table[((RCC->CFGR >> 11) & 0b111) ];
}

