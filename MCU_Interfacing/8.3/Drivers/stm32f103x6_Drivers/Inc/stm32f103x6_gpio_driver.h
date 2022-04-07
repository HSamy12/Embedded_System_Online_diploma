/*
 * stm32f103x6_gpio_driver.h
 *
 *  Created on: Mar 26, 2022
 *      Author: Hassan
 */

#ifndef INC_STM32F103X6_GPIO_DRIVER_H_
#define INC_STM32F103X6_GPIO_DRIVER_H_

/***************************************************************************************/
// Includes
//********************************
#include "stm32f103x6.h"

/**************************************************************************************/
// Configuration Structures
//********************************
typedef struct{
	uint16_t GPIO_PinNumber;	//specifies the GPIO pin to be configured.
								//this parameter must be set from @ref GPIO_Pins_define.

	uint8_t GPIO_MODE;			//specifies the operating mode for the selected pin
								//this parameter must be set from @ref GPIO_MODE_define.

	uint8_t GPIO_Out_Speed;		//specifies the speed for selected pin.
								//this parameter must be set from @ref GPIO_Speed_define.


}GPIO_PinConfig_t;



/**************************************************************************************/
// Macro Configuration references
//********************************

//===============================
//@ref GPIO_Pins_define
//===============================
#define GPIO_Pin_0				((uint16_t)0x0001)	// Pin 0 selected.
#define GPIO_Pin_1				((uint16_t)0x0002)	// Pin 1 selected.
#define GPIO_Pin_2				((uint16_t)0x0004)	// Pin 2 selected.
#define GPIO_Pin_3				((uint16_t)0x0008)	// Pin 3 selected.
#define GPIO_Pin_4				((uint16_t)0x0010)	// Pin 4 selected.
#define GPIO_Pin_5				((uint16_t)0x0020)	// Pin 5 selected.
#define GPIO_Pin_6				((uint16_t)0x0040)	// Pin 6 selected.
#define GPIO_Pin_7				((uint16_t)0x0080)	// Pin 7 selected.
#define GPIO_Pin_8				((uint16_t)0x0100)	// Pin 8 selected.
#define GPIO_Pin_9				((uint16_t)0x0200)	// Pin 9 selected.
#define GPIO_Pin_10				((uint16_t)0x0400)	// Pin 10 selected.
#define GPIO_Pin_11				((uint16_t)0x0800)	// Pin 11 selected.
#define GPIO_Pin_12				((uint16_t)0x1000)	// Pin 12 selected.
#define GPIO_Pin_13				((uint16_t)0x2000)	// Pin 13 selected.
#define GPIO_Pin_14				((uint16_t)0x4000)	// Pin 14 selected.
#define GPIO_Pin_15				((uint16_t)0x8000)	// Pin 15 selected.
#define GPIO_Pin_ALL			((uint16_t)0xFFFF)	// All Pins selected.

#define GPIO_Pins_MASK			0x0000FFFFu			// Pin MASK for test.

//===============================
// @ref GPIO_PIN_State
//===============================
//0: reset pin
#define GPIO_PIN_RESET					0
//1:set pin
#define GPIO_PIN_SET					1

//===============================
//@ref GPIO_Return_Lock
//===============================
//0:Lock Error
#define GPIO_Return_Lock_ERROR			0
//1:Lock Success
#define GPIO_Return_Lock_Success		1


//===============================
// @ref GPIO_MODE_define
//===============================
//0: Analog mode
#define GPIO_MODE_analog				0x00000000u
//1: Floating input (reset state)
#define GPIO_MODE_In_FLO				0x00000001u
//2: Input with pull-up
#define GPIO_MODE_In_PU					0x00000002u
//3: Input with pull-down
#define GPIO_MODE_In_PD					0x00000003u
//4: General purpose output push-pull
#define GPIO_MODE_Out_PP				0x00000004u
//5: General purpose output Open-drain
#define GPIO_MODE_Out_OD				0x00000005u
//6: Alternate function output Push-pull
#define GPIO_MODE_AF_Out_PP				0x00000006u
//7: Alternate function output Open-drain
#define GPIO_MODE_AF_Out_OD				0x00000007u
//8: Alternate function input
#define GPIO_MODE_AF_In					0x00000008u

//===============================
// @ref GPIO_Speed_define
//===============================
//1: Output mode, max speed 10 MHz.
#define GPIO_Speed_10M					0x00000001u
//2: Output mode, max speed 2 MHz.
#define GPIO_Speed_2M					0x00000002u
//3: Output mode, max speed 50 MHz.
#define GPIO_Speed_50M					0x00000003u


/**************************************************************************************/
// APIs supports "MCAL GPIO Driver"
//********************************
void MCAL_GPIO_Init(GPIO_TypeDef* GPIOx,GPIO_PinConfig_t *PinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef* GPIOx);

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx,uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef* GPIOx);

void MCAL_GPIO_WritePin(GPIO_TypeDef* GPIOx,uint16_t PinNumber,uint8_t value);
void MCAL_GPIO_WritePort(GPIO_TypeDef* GPIOx,uint16_t value);

void MCAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx,uint16_t PinNumber);

uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef* GPIOx,uint16_t PinNumber);

#endif /* INC_STM32F103X6_GPIO_DRIVER_H_ */
