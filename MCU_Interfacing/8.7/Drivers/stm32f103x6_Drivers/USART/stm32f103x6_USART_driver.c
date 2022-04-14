/*
 * stm32f103x6_USART_driver.c
 *
 *  Created on: Apr 6, 2022
 *      Author: Hassan
 */

//********************************
// Includes
//********************************
#include "stm32f103x6_USART_driver.h"

/**************************************************************************************/
// Generic Variables
//********************************
USART_Config_t* P_UART_Cfg[3] = {NULL,NULL,NULL};

/**************************************************************************************/
// Generic Functions
//********************************
//ISR
void USART1_IRQHandler (void)
{

	P_UART_Cfg[0]->P_IRQ_CallBack () ;

}

void USART2_IRQHandler (void)
{
	P_UART_Cfg[1]->P_IRQ_CallBack () ;

}
void USART3_IRQHandler (void)
{
	P_UART_Cfg[2]->P_IRQ_CallBack () ;

}


/**************************************************************************************/
// APIs
//********************************
/*================================================================
 * @Fn			-MCAL_USART_Init
 * @brief 		-Initializes the USARTx with specified Pin Configurations
 * @param [in] 	-USARTx: where x is USART peripheral (1...3 depend on device)
 * @param [in] 	-UART_Config: pointer to USART_Config_t structure that contains
 * 				 configuration information for specified USART.
 * @retval 		-none
 * Note			-STM32F103C6 MCU has USARTs 1,2,3 modules only
 */
void MCAL_USART_Init(USART_TypeDef* USARTx ,USART_Config_t* UART_Config){

	uint32_t Pclk, BRR;

	//enable the CLK for USART peripheral
	if(USARTx == USART1){
		RCC_USART1_CLK_EN();
		P_UART_Cfg[0] = UART_Config;
	}
	else if(USARTx == USART2){
		RCC_USART2_CLK_EN();
		P_UART_Cfg[1] = UART_Config;
	}
	else if(USARTx == USART3){
		RCC_USART3_CLK_EN();
		P_UART_Cfg[2] = UART_Config;
	}

	//enable USART Module
	// Bit 13 UE: USART enable
	USARTx->CR[0] |= (1<<13);

	//Enable USART Tx and Rx engines according to the USART_Mode configuration item
	//USART_CR1 Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver enable
	USARTx->CR[0] |= UART_Config->USART_MODE;

	//PAYLOAD Width
	//USARTx->CR1  Bit 12 M: Word length
	USARTx->CR[0] |= UART_Config->Payload_length;

	//Configuration of parity control bit fields
	//USARTx->CR1 	Bit 10 PCE: Parity control enable     Bit 9 PS: Parity selection
	USARTx->CR[0] |= UART_Config->Parity;

	//configure the number of stop bits
	//USART_CR2  Bits 13:12 STOP: STOP bits
	USARTx->CR[1] |= UART_Config->StopBits;

	//USART hardware flow control
	//USART_CR3  Bit 9 CTSE: CTS enable   Bit 8 RTSE: RTS enable
	USARTx->CR[2] |= UART_Config->HwFlowCtl;

	//Configuration of BRR(Baudrate register)
	//PCLK1 for USART2, 3
	//PCLK2 for USART1
	if(USARTx == USART1)
		Pclk = MCAL_RCC_GetPClk2Freq();
	else
		Pclk = MCAL_RCC_GetPClk1Freq();

	BRR = UART_BRR_Register(Pclk,UART_Config->Baud_Rate);
	USARTx->BRR = BRR;

	//ENABLE / DISABLE Interrupt
	//USART_CR1
	if (UART_Config->IRQ_Enable  != UART_IRQ_Enable_NONE){

		USARTx->CR[0] |= (UART_Config->IRQ_Enable) ;
		//Enable NVIC For USARTx IRQ
		if(USARTx == USART1)		NVIC_IRQ37_USART1_Enable;
		else if(USARTx == USART2)	NVIC_IRQ38_USART2_Enable;
		else if(USARTx == USART3)	NVIC_IRQ39_USART3_Enable;
	}
}


/**================================================================
 * @Fn				-MCAL_USART_Deinit
 * @brief 			- DEInitializes UART (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-Reset the Model By RCC
 */
void MCAL_USART_Deinit(USART_TypeDef *USARTx){

	if(USARTx == USART1){
		RCC_USART1_RESET();
		NVIC_IRQ37_USART1_Disable;
	}
	else if(USARTx == USART2){
		RCC_USART2_RESET();
		NVIC_IRQ38_USART2_Disable;
	}
	else if(USARTx == USART3){
		RCC_USART3_RESET();
		NVIC_IRQ39_USART3_Disable;
	}
}


/*********************************************************************
 * @fn     			-MCAL_USART_SendData
 * @brief           -Send Buffer on UART
 * @param [in]		-USARTx: where x can be (1..3 depending on device used)
 * @param[in]       -pTxBuffer Buffer
 * @param[in]       -PollingEn   Enable pooling or dsable it
 * @return          -none
 * @Note            -Should initialize UART First
 *					When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
 *					the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
 *					because it is replaced by the parity.
 *					When receiving with the parity enabled, the value read in the MSB bit is the received parity bit
 */
void MCAL_USART_SendData(USART_TypeDef* USARTx, uint16_t* pTxBuffer,UART_PollingMechanism PollingEn){
	//loop until TXE flag up (Transmitter empty) in case Polling enabled
	if(PollingEn == enable){
		while(!( USARTx->SR & 1<<7));
	}

	// 2. Check the USART_WordLength item for 9-bit or 8-bit in a frame
	USART_Config_t* USARTxConfig = NULL;
	USARTxConfig = (USART_Config_t*)((USARTx == USART1)?  P_UART_Cfg	:
			                            ((USARTx == USART2)? (P_UART_Cfg + 1):(P_UART_Cfg + 2)));

	//Check the USART_WordLength item for 9BIT or 8BIT in a frame
	//When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//is replaced by the parity.
	//When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.

	if (USARTxConfig->Payload_length == USART_Payload_9Bits)
		//if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits
		USARTx->DR = (*pTxBuffer & (uint16_t)0x1FF);

	else if(USARTxConfig->Payload_length == USART_Payload_8Bits)
		//This is 8bit data transfer
		USARTx->DR = (*pTxBuffer  & (uint8_t)0xFF);
}


void MCAL_USART_waitTC(USART_TypeDef* USARTx){
	// wait till TC flag is set in the SR
	while(!(USARTx->SR & 1<<6));
}


/*********************************************************************
 * @fn     			-MCAL_USART_ReciveData
 * @brief           -Recive Buffer on UART
 * @param [in]		-USARTx: where x can be (1..3 depending on device used)
 * @param[in]       -pRxBuffer Buffer
 * @param[in]       -PollingEn   Enable pooling or disable it
 * @return          -none
 * @Note            -Should initialize UART First
 *					When Receive with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
 *					the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
 *					because it is replaced by the parity.
 *					When receiving with the parity enabled, the value read in the MSB bit is the received parity bit
 */
void MCAL_USART_ReceiveData(USART_TypeDef* USARTx, uint16_t* pRxBuffer,UART_PollingMechanism PollingEn){
	//loop until RXNE flag up (Read data register not empty) in case Polling enabled
	if(PollingEn == enable){
		while(!( USARTx->SR & 1<<5));
	}

	USART_Config_t* USARTxConfig = NULL;
	USARTxConfig = (USART_Config_t*)((USARTx == USART1)?  P_UART_Cfg	:
			                            ((USARTx == USART2)? (P_UART_Cfg + 1):(P_UART_Cfg + 2)));

	//if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits
	if (USARTxConfig->Payload_length == USART_Payload_9Bits){
		//check for parity
		if(USARTxConfig->Parity == UART_Parity__NONE)
			*((uint16_t*) pRxBuffer) = USARTx->DR;//if none write on register normally
		else
			*((uint16_t*) pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);//if parity enabled write on 8bits only

	}
	//This is 8bit data transfer
	else if(USARTxConfig->Payload_length == USART_Payload_8Bits){
		//check for parity
		if(USARTxConfig->Parity == UART_Parity__NONE)
			*((uint16_t*) pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);//if none read from register normally
		else
			*((uint16_t*) pRxBuffer) = (USARTx->DR & (uint8_t)0x7F);//if parity enabled read from 7bits only
	}
}


/*********************************************************************
 * @Fn				-MCAL_USART_SetPins
 * @brief 			- initialize GPIO Pins
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-Should enable the corresponding ALT  & GPIO  in RCC clock Also called after MCAL_UART_Init()
 */
void MCAL_USART_SetPins(USART_TypeDef* USARTx){
	GPIO_PinConfig_t PinCfg;
	if(USARTx == USART1){
		//PA9 TX
		PinCfg.GPIO_PinNumber = GPIO_Pin_9;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_PP;
		PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//PA10 RX
		PinCfg.GPIO_PinNumber = GPIO_Pin_10;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_In;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		if (P_UART_Cfg[0]->HwFlowCtl == UART_HwFlowCtl_CTS || P_UART_Cfg[0]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			//PA11 CTS
			PinCfg.GPIO_PinNumber = GPIO_Pin_11;
			PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
		if (P_UART_Cfg[0]->HwFlowCtl == UART_HwFlowCtl_RTS || P_UART_Cfg[0]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			//PA12 RTS
			PinCfg.GPIO_PinNumber = GPIO_Pin_12;
			PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_PP;
			PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
	}

	else if(USARTx == USART2){
		//PA2 TX
		PinCfg.GPIO_PinNumber = GPIO_Pin_2;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_PP;
		PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//PA3 RX
		PinCfg.GPIO_PinNumber = GPIO_Pin_3;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_In;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		if (P_UART_Cfg[1]->HwFlowCtl == UART_HwFlowCtl_CTS || P_UART_Cfg[1]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			//PA0 CTS
			PinCfg.GPIO_PinNumber = GPIO_Pin_0;
			PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
		if (P_UART_Cfg[1]->HwFlowCtl == UART_HwFlowCtl_RTS || P_UART_Cfg[1]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			//PA1 RTS
			PinCfg.GPIO_PinNumber = GPIO_Pin_1;
			PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_PP;
			PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
	}

	else if(USARTx == USART3){
		//PB10 TX
		PinCfg.GPIO_PinNumber = GPIO_Pin_10;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_PP;
		PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		//PB11 RX
		PinCfg.GPIO_PinNumber = GPIO_Pin_11;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_In;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		if (P_UART_Cfg[2]->HwFlowCtl == UART_HwFlowCtl_CTS || P_UART_Cfg[2]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			//PB13 CTS
			PinCfg.GPIO_PinNumber = GPIO_Pin_13;
			PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}
		if (P_UART_Cfg[2]->HwFlowCtl == UART_HwFlowCtl_RTS || P_UART_Cfg[2]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			//PB14 RTS
			PinCfg.GPIO_PinNumber = GPIO_Pin_14;
			PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_PP;
			PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}
	}
}





