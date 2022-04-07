/*
 * stm32f103x6_gpio_driver.c
 *
 *  Created on: Mar 26, 2022
 *      Author: Hassan
 */


//********************************
// Includes
//********************************
#include "stm32f103x6_gpio_driver.h"

/**************************************************************************************/
// Generic Functions
//********************************
uint8_t Get_CRHL_Position(uint16_t PinNumber){
	switch(PinNumber){
	case GPIO_Pin_0:
		return 0;
		break;
	case GPIO_Pin_1:
		return 4;
		break;
	case GPIO_Pin_2:
		return 8;
		break;
	case GPIO_Pin_3:
		return 12;
		break;
	case GPIO_Pin_4:
		return 16;
		break;
	case GPIO_Pin_5:
		return 20;
		break;
	case GPIO_Pin_6:
		return 24;
		break;
	case GPIO_Pin_7:
		return 28;
		break;
	case GPIO_Pin_8:
		return 0;
		break;
	case GPIO_Pin_9:
		return 4;
		break;
	case GPIO_Pin_10:
		return 8;
		break;
	case GPIO_Pin_11:
		return 12;
		break;
	case GPIO_Pin_12:
		return 16;
		break;
	case GPIO_Pin_13:
		return 20;
		break;
	case GPIO_Pin_14:
		return 24;
		break;
	case GPIO_Pin_15:
		return 28;
		break;
	default:
		return 0;
		break;
	}
}


/**************************************************************************************/
// APIs
//********************************
/*================================================================
 * @Fn			-MCAL_GPIO_Init
 * @brief 		-Initializes the GPIOx PINy with specified Pin Configurations
 * @param [in] 	-GPIOx: where x is GPIO peripheral (A...E depend on device)
 * @param [in] 	-PinConfig: pointer to GPIO_PinConfig_t structure that contains
 * 				 configuration information for specified GPIO.
 * @retval 		-none
 * Note			-STM32F103C6 MCU has GPIOs A,B,C,D,E modules
 * 				 but the package LQFP48 has only A,B and parts of C,D exported to external pins
 */
void MCAL_GPIO_Init(GPIO_TypeDef* GPIOx,GPIO_PinConfig_t *PinConfig){

	uint32_t PIN_Config = 0;
	//Port configuration register low (GPIOx_CRL) configures Pins from 0 >> 7
	//Port configuration register high (GPIOx_CRH) configures Pins from 8 >> 15
	volatile uint32_t *configregister = NULL;

	configregister = (PinConfig->GPIO_PinNumber < GPIO_Pin_8 )? &GPIOx->CRL : &GPIOx->CRH;

	// clears CNFx[1:0] and MODEy[1:0]
	(*configregister) &= ~(0x0F << Get_CRHL_Position(PinConfig->GPIO_PinNumber));

	//if pin is any output type
	if((PinConfig->GPIO_MODE == GPIO_MODE_AF_Out_OD) || (PinConfig->GPIO_MODE == GPIO_MODE_AF_Out_PP) || (PinConfig->GPIO_MODE == GPIO_MODE_Out_OD) || (PinConfig->GPIO_MODE == GPIO_MODE_Out_PP)){
		PIN_Config= ((((PinConfig->GPIO_MODE - 4) << 2) | (PinConfig->GPIO_Out_Speed)) & 0x0F);
	}
	//if input floating or analog
	else{
		if((PinConfig->GPIO_MODE == GPIO_MODE_In_FLO) || (PinConfig->GPIO_MODE == GPIO_MODE_analog))

			PIN_Config= (((PinConfig->GPIO_MODE)<<2) & 0x0F);

		//if input alternative function
		else if(PinConfig->GPIO_MODE == GPIO_MODE_AF_In)
			PIN_Config= (((GPIO_MODE_In_FLO)<<2) & 0x0F); //considered as floating

		// if input pull-up or pull-down
		else{
			PIN_Config= (((GPIO_MODE_In_PU)<<2) & 0x0F);
			if(PinConfig->GPIO_MODE == GPIO_MODE_In_PU)
				//PxODR = 1 ===> pull up table 20. port bit configuration
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			else
				//PxODR = 0 ===> pull down table 20. port bit configuration
				GPIOx->ODR &= ~PinConfig->GPIO_PinNumber;
		}
	}
	// sets CNFx[1:0] and MODEy[1:0] according to PIN_Config
	(*configregister) |= ((PIN_Config) << Get_CRHL_Position(PinConfig->GPIO_PinNumber));
}



/*================================================================
 * @Fn			-MCAL_GPIO_DeInit
 * @brief 		-resets the GPIOx
 * @param [in] 	-GPIOx: where x is GPIO peripheral (A...E depend on device)
 * @retval 		-none
 * Note			-none
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef* GPIOx){
	// manual reset of registers
	//	GPIOx->CRL  = 0x44444444;
	//	GPIOx->CRH  = 0x44444444;
	//	GPIOx->BRR  = 0x00000000;
	//	GPIOx->BSSR = 0x00000000;
	//	GPIOx->LCKR = 0x00000000;
	//	GPIOx->ODR  = 0x00000000;
	////	GPIOx->IDR  = XX (READ ONLY);

	// or use reset controller with RCC_APB2RSTR
	//the APB2 peripheral reset register
	if(GPIOx == GPIOA){
		RCC->APB2RSTR |= (1<<2);	//Bit 2 IOPARST: IO PortA reset
		RCC->APB2RSTR &= ~(1<<2);
	}
	else if(GPIOx == GPIOB){
		RCC->APB2RSTR |= (1<<3);	//Bit 2 IOPARST: IO PortB reset
		RCC->APB2RSTR &= ~(1<<3);
	}
	else if(GPIOx == GPIOC){
		RCC->APB2RSTR |= (1<<4);	//Bit 2 IOPARST: IO PortC reset
		RCC->APB2RSTR &= ~(1<<4);
	}
	else if(GPIOx == GPIOD){
		RCC->APB2RSTR |= (1<<5);	//Bit 2 IOPARST: IO PortD reset
		RCC->APB2RSTR &= ~(1<<5);
	}
	else if(GPIOx == GPIOE){
		RCC->APB2RSTR |= (1<<6);	//Bit 2 IOPARST: IO PortE reset
		RCC->APB2RSTR &= ~(1<<6);
	}

}




/*================================================================
 * @Fn			-MCAL_GPIO_ReadPin
 * @brief		-Read specific Pin value
 * @param [in] 	-GPIOx: where x is GPIO peripheral (A...E depend on device)
 * @param [in] 	-PinNumber: set Pin number to read from
 * @retval 		-the input pin value
 * Notes			-PinNumber is set according to @ref GPIO_Pins_define
 * 				-the returned pin value will be based on @ref GPIO_PIN_State
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx,uint16_t PinNumber){
	uint8_t bitStatus;
	if(((GPIOx->IDR) & PinNumber) != GPIO_PIN_RESET)
		bitStatus = (uint8_t)GPIO_PIN_SET;
	else
		bitStatus = (uint8_t)GPIO_PIN_RESET;

	return bitStatus;

}




/*================================================================
 * @Fn			-MCAL_GPIO_ReadPort
 * @brief		-Read input Port value
 * @param [in] 	-GPIOx: where x is GPIO peripheral (A...E depend on device)
 * @retval 		-the input port values
 * Notes			-PinNumber is set according to @ref GPIO_Pins_define
 * 				-the returned value will be based on @ref GPIO_PIN_State
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef* GPIOx){

	return (uint16_t)GPIOx->IDR;
}


/*================================================================
 * @Fn			-MCAL_GPIO_WritePin
 * @brief		-write on specific pin
 * @param [in] 	-GPIOx: where x is GPIO peripheral (A...E depend on device)
 * @param [in] 	-PinNumber: set Pin number to write on
 * @param [in] 	-value: the value to be written on the pin
 * @retval 		-none
 * Notes			-PinNumber is set according to @ref GPIO_Pins_define
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef* GPIOx,uint16_t PinNumber,uint8_t value){
	if (value != GPIO_PIN_RESET)
		//		GPIOx->ODR |= (uint32_t)PinNumber;
		//		or
		GPIOx->BSRR = (uint32_t)PinNumber;
	else
		//		GPIOx->ODR &= ~((uint32_t)PinNumber);
		//		or
		GPIOx->BRR = (uint32_t)PinNumber;

}


/*================================================================
 * @Fn			-MCAL_GPIO_WritePort
 * @brief		-write on Port
 * @param [in] 	-GPIOx: where x is GPIO peripheral (A...E depend on device)
 * @param [in] 	-value: the value to be written on the port
 * @retval 		-none
 * Notes			-none
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef* GPIOx,uint16_t value){

	GPIOx->ODR = (uint32_t)value;
}



/*================================================================
 * @Fn			-MCAL_GPIO_TogglePin
 * @brief		-toggle value on specific pin
 * @param [in] 	-GPIOx: where x is GPIO peripheral (A...E depend on device)
 * @param [in] 	-PinNumber: set Pin number to toggle
 * @retval 		-none
 * Notes			-PinNumber is set according to @ref GPIO_Pins_define
 */
void MCAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx,uint16_t PinNumber){

	GPIOx->ODR ^= (uint32_t)PinNumber;
}



/*================================================================
 * @Fn			-MCAL_GPIO_LockPin
 * @brief		-locking mechanism allows IO configuration to be frozen on specific pin
 * @param [in] 	-GPIOx: where x is GPIO peripheral (A...E depend on device)
 * @param [in] 	-PinNumber: set Pin number to Lock
 * @retval 		-OK if Pin config is locked or Error if pin is not locked
 * Notes			-PinNumber is set according to @ref GPIO_Pins_define
 * 				-Lock Success & Error are specified @ref GPIO_Return_Lock
 */
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef* GPIOx,uint16_t PinNumber){
	//	Bit 16 LCKK[16]: Lock key
	//	This bit can be read any time. It can only be modified using the Lock Key Writing Sequence.
	//	0: Port configuration lock key not active
	//	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	//	LOCK key writing sequence:
	//	Write 1
	//	Write 0
	//	Write 1
	//	Read 0
	//	Read 1 (this read is optional but confirms that the lock is active)
	//	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	//	Any error in the lock sequence will abort the lock.
	//	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	//	These bits are read write but can only be written when the LCKK bit is 0.
	//	0: Port configuration not locked
	//	1: Port configuration locked.

	//set LCKK[16]
	volatile uint32_t temp = 1<<16;
	//set LCKy
	temp |= PinNumber;
	//	Write 1
	GPIOx->LCKR = temp;
	//	Write 0
	GPIOx->LCKR = PinNumber;
	//	Write 1
	GPIOx->LCKR = temp;
	//	Read 0
	temp = GPIOx->LCKR;
	//	Read 1 (this read is optional but confirms that the lock is active)
	if((uint32_t)( GPIOx->LCKR & (1<<16)))
		return GPIO_Return_Lock_Success;
	else
		return GPIO_Return_Lock_ERROR;
}
