/*
 * stm32f103x6_RCC_driver.h
 *
 *  Created on: Apr 6, 2022
 *      Author: Hassan
 */

#ifndef INC_STM32F103X6_RCC_DRIVER_H_
#define INC_STM32F103X6_RCC_DRIVER_H_

/***************************************************************************************/
// Includes
//********************************
#include "stm32f103x6.h"
#include "stm32f103x6_gpio_driver.h"

/**************************************************************************************/
// generic Macros
//********************************
#define	HSI_RC_clk			(uint32_t)8000000
#define HSE_RC_clk			(uint32_t)16000000
#define PLL_RC_clk			(uint32_t)16000000


/**************************************************************************************/
// APIs
//********************************
uint32_t MCAL_RCC_GetSYS_ClkFreq();
uint32_t MCAL_RCC_GetHClkFreq();
uint32_t MCAL_RCC_GetPClk1Freq();
uint32_t MCAL_RCC_GetPClk2Freq();

#endif /* INC_STM32F103X6_RCC_DRIVER_H_ */
