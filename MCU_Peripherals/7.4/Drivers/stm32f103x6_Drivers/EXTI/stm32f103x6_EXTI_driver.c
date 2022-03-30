/*
 * stm32f103x6_gpio_driver.c
 *
 *  Created on: Mar 26, 2022
 *      Author: Hassan
 */


//********************************
// Includes
//********************************
#include "stm32f103x6_EXTI_driver.h"


/**************************************************************************************/
// Generic Variables
//********************************
void (* GP_IRQ_CallBack[15])(void);


/**************************************************************************************/
// generic Macros
//********************************
#define AFIO_GPIO_EXTI_Mapping(x)		((x==GPIOA)?0:\
										(x==GPIOB)?1:\
										(x==GPIOC)?2:\
										(x==GPIOD)?3:0)


/**************************************************************************************/
// Generic functions
//********************************
void EXTI0_IRQHandler (void){
	// write 1 to clear PR register
	EXTI->PR |= (1<<0);
	//call IRQ_Call
	GP_IRQ_CallBack[0]();
}

void EXTI1_IRQHandler (void){
	// write 1 to clear PR register
	EXTI->PR |= (1<<1);
	//call IRQ_Call
	GP_IRQ_CallBack[1]();
}

void EXTI2_IRQHandler (void){
	// write 1 to clear PR register
	EXTI->PR |= (1<<2);
	//call IRQ_Call
	GP_IRQ_CallBack[2]();
}

void EXTI3_IRQHandler (void){
	// write 1 to clear PR register
	EXTI->PR |= (1<<3);
	//call IRQ_Call
	GP_IRQ_CallBack[3]();
}

void EXTI4_IRQHandler (void){
	// write 1 to clear PR register
	EXTI->PR |= (1<<4);
	//call IRQ_Call
	GP_IRQ_CallBack[4]();
}

void EXTI9_5_IRQHandler (void){
	if(	EXTI->PR & (1<<5)){	EXTI->PR |= (1<<5);	GP_IRQ_CallBack[5](); }
	if(	EXTI->PR & (1<<6)){	EXTI->PR |= (1<<6);	GP_IRQ_CallBack[6](); }
	if(	EXTI->PR & (1<<7)){	EXTI->PR |= (1<<7);	GP_IRQ_CallBack[7](); }
	if(	EXTI->PR & (1<<8)){	EXTI->PR |= (1<<8);	GP_IRQ_CallBack[8](); }
	if(	EXTI->PR & (1<<9)){	EXTI->PR |= (1<<9);	GP_IRQ_CallBack[9](); }

}

void EXTI15_10_IRQHandler (void){
	if(	EXTI->PR & (1<<10)){	EXTI->PR |= (1<<10);	GP_IRQ_CallBack[10](); }
	if(	EXTI->PR & (1<<11)){	EXTI->PR |= (1<<11);	GP_IRQ_CallBack[11](); }
	if(	EXTI->PR & (1<<12)){	EXTI->PR |= (1<<12);	GP_IRQ_CallBack[12](); }
	if(	EXTI->PR & (1<<13)){	EXTI->PR |= (1<<13);	GP_IRQ_CallBack[13](); }
	if(	EXTI->PR & (1<<14)){	EXTI->PR |= (1<<14);	GP_IRQ_CallBack[14](); }
	if(	EXTI->PR & (1<<15)){	EXTI->PR |= (1<<15);	GP_IRQ_CallBack[15](); }
}


void Enable_NVIC(uint16_t IRQ){
	switch(IRQ){
	case 0:
		NVIC_IRQ6_EXTI0_Enable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Enable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Enable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Enable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Enable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Enable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Enable;
		break;
	}
}


void Disable_NVIC(uint16_t IRQ){
	switch(IRQ){
	case 0:
		NVIC_IRQ6_EXTI0_Disable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Disable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Disable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Disable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Disable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Disable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Disable;
		break;
	}
}

/**************************************************************************************/
// APIs
//********************************
/*================================================================
 * @Fn			-MCAL_EXTI_GPIO_Init
 * @brief 		-Initializes the EXTI from specific GPIO Pin and the Mask/Trigger
 * 				 condition and IRQ CallBack
 * @param [in] 	-EXTI_Config: configure the parameter of EXTI IRQ set by @ref EXTI_define,
 * 				 EXTI_Trigger_define and EXTI_IRQ_define
 * @retval 		-none
 * Note			-STM32F103C6 MCU has GPIOs A,B,C,D,E modules
 * 				 but the package LQFP48 has only A,B and parts of C,D exported to external pins
 */
void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t *EXTI_Config){

	//1. PIN must be in input Mode{GPIO}
	GPIO_PinConfig_t PinCfg;
	PinCfg.GPIO_PinNumber = EXTI_Config->EXTI_Pin.GPIO_Pin;
	PinCfg.GPIO_MODE = GPIO_MODE_AF_In;
	MCAL_GPIO_Init(EXTI_Config->EXTI_Pin.GPIO_PORT, &PinCfg);
	//--------------------------------------------------------------
	//2.Update AFIO to route to EXTI line on PORTs A,B,C,D
	uint8_t AFIO_EXTICR_index = (EXTI_Config->EXTI_Pin.ETI_InLineNumber)/4;
	uint8_t AFIO_EXTICR_position = ((EXTI_Config->EXTI_Pin.ETI_InLineNumber)%4) * 4;
	// clear the 4 bits
	AFIO->EXTICR[AFIO_EXTICR_index] &= ~( 0xF << AFIO_EXTICR_position);
	AFIO->EXTICR[AFIO_EXTICR_index] |= ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_Pin.GPIO_PORT) & 0xF) << AFIO_EXTICR_position);
	//--------------------------------------------------------------
	//3.Configure the EXTI Selected and the trigger condition RT, FT RFT {EXTI}, Then Enable the IRQ
	EXTI->RTSR &= ~(1 << EXTI_Config->EXTI_Pin.ETI_InLineNumber);
	EXTI->FTSR &= ~(1 << EXTI_Config->EXTI_Pin.ETI_InLineNumber);

	switch(EXTI_Config->Trigger_Case){
	case EXTI_Trigger_Rising:
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_Pin.ETI_InLineNumber);
		break;
	case EXTI_Trigger_Falling:
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_Pin.ETI_InLineNumber);
		break;
	case EXTI_Trigger_RisingAndFalling:
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_Pin.ETI_InLineNumber);
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_Pin.ETI_InLineNumber);
		break;
	}
	//--------------------------------------------------------------
	//4.update IRQ handling CallBack
	GP_IRQ_CallBack[EXTI_Config->EXTI_Pin.ETI_InLineNumber] = EXTI_Config->P_IRQ_CallBack;

	//--------------------------------------------------------------
	//5.Enable/Disable IRQ
	if(EXTI_Config->IRQ_En == EXTI_IRQ_Enable){
		EXTI->IMR |= (1<< EXTI_Config->EXTI_Pin.ETI_InLineNumber);
		Enable_NVIC(EXTI_Config->EXTI_Pin.ETI_InLineNumber);
	}
	else{
		EXTI->IMR &= ~(1<< EXTI_Config->EXTI_Pin.ETI_InLineNumber);
		Disable_NVIC(EXTI_Config->EXTI_Pin.ETI_InLineNumber);
	}
}


/*================================================================
 * @Fn			-MCAL_EXTI_GPIO_Deinit
 * @brief 		-Resets the EXTI registers and NVIC corresponding IRQ Masks
 * @param [in] 	-none
 * @retval 		-none
 * Note			-STM32F103C6 MCU has GPIOs A,B,C,D,E modules
 * 				 but the package LQFP48 has only A,B and parts of C,D exported to external pins
 */
void MCAL_EXTI_GPIO_Deinit(){
	EXTI->IMR = 0x0;
	EXTI->EMR = 0x0;
	EXTI->FTSR = 0x0;
	EXTI->RTSR = 0x0;
	EXTI->SWIER = 0x0;

	// write 1 to clear PR register
	EXTI->PR = 0xFFFFFFFF;

	//Disable EXTI IRQ from NVIC
	NVIC_IRQ6_EXTI0_Disable;
	NVIC_IRQ7_EXTI1_Disable;
	NVIC_IRQ8_EXTI2_Disable;
	NVIC_IRQ9_EXTI3_Disable;
	NVIC_IRQ10_EXTI4_Disable;
	NVIC_IRQ23_EXTI5_9_Disable;
	NVIC_IRQ40_EXTI10_15_Disable;
}

/*================================================================
 * @Fn			-MCAL_EXTI_GPIO_Update
 * @brief 		-updates the EXTI from specific GPIO Pin and the Mask/Trigger
 * 				 condition and IRQ CallBack
 * @param [in] 	-EXTI_Config: configure the parameter of EXTI IRQ set by @ref EXTI_define,
 * 				 EXTI_Trigger_define and EXTI_IRQ_define
 * @retval 		-none
 * Note			-STM32F103C6 MCU has GPIOs A,B,C,D,E modules
 * 				 but the package LQFP48 has only A,B and parts of C,D exported to external pins
 */
void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t *EXTI_Config){
	MCAL_EXTI_GPIO_Init(EXTI_Config);
}
