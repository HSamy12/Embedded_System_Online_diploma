/*
 * stm32f103x6_USART_driver.h
 *
 *  Created on: Apr 6, 2022
 *      Author: Hassan
 */

#ifndef INC_STM32F103X6_USART_DRIVER_H_
#define INC_STM32F103X6_USART_DRIVER_H_

/***************************************************************************************/
// Includes
//********************************
#include "stm32f103x6.h"
#include "stm32f103x6_gpio_driver.h"
#include "stm32f103x6_RCC_driver.h"


/**************************************************************************************/
// Configuration Structures
//********************************
typedef struct{
	uint8_t USART_MODE;			//specifies the operating mode Tx or Rx
	//this parameter must be set from @ref USART_MODE_define.

	uint32_t Baud_Rate;			//specifies the speed for receiving/transmitting.
	//this parameter must be set from @ref USART_BaudRate_define.

	uint8_t Payload_length;		//specifies the number of Data bits Transmitted/Received per frame.
	//this parameter must be set from @ref USART_Payload_define.

	uint8_t Parity;				//specifies if parity enabled or not also type of it.
	//this parameter must be set from @ref USART_Parity_define.

	uint8_t StopBits;			//Specifies the number of stop bits transmitted
	//this parameter must be set from @ref UART_StopBits_define

	uint8_t HwFlowCtl;			//Specifies whether the hardware flow control mode is enabled or disabled
	//this parameter must be set from @ref UART_HwFlowCtl_define

	uint8_t	IRQ_Enable;			//enable or disable UART IRQ TX/RX
	//@ref UART_IRQ_Enable_define , you can select two or three parameters EX.UART_IRQ_Enable_TXE |UART_IRQ_Enable_TC

	void (*P_IRQ_CallBack)(void);//Set the C Function() which will be called once the IRQ  Happen

}USART_Config_t;

typedef enum{
	disable, enable
}UART_PollingMechanism;


/**************************************************************************************/
// Macro Configuration references
//********************************
//===============================
// @ref USART_MODE_define.
//===============================
#define USART_MODE_Tx			(uint32_t)(1 << 3)			//Bit 3 TE: Transmitter enable
#define USART_MODE_Rx			(uint32_t)(1 << 2)			//Bit 2 RE: Receiver enable
#define USART_MODE_Tx_Rx		(uint32_t)(1 << 2 | 1 << 3)	//Both enabled

//===============================
// @ref USART_BaudRate_define.
//===============================
#define USART_BaudRate_2400			(uint32_t)(2400)
#define USART_BaudRate_9600			(uint32_t)(9600)
#define USART_BaudRate_19200		(uint32_t)(19200)
#define USART_BaudRate_57600		(uint32_t)(57600)
#define USART_BaudRate_115200		(uint32_t)(115200)
#define USART_BaudRate_230400		(uint32_t)(230400)
#define USART_BaudRate_460800		(uint32_t)(460800)
#define USART_BaudRate_921600		(uint32_t)(921600)
#define USART_BaudRate_2250000		(uint32_t)(2250000)
#define USART_BaudRate_4500000		(uint32_t)(4500000)

//===============================
// @ref USART_Payload_define.
//===============================
#define USART_Payload_8Bits			(uint32_t)(0)
#define USART_Payload_9Bits			(uint32_t)(1 << 12)

//===============================
// @ref USART_Parity_define.
//===============================
#define UART_Parity__NONE           (uint32_t)(0)
#define UART_Parity__EVEN           (uint32_t)(1<<10)
#define UART_Parity__ODD			(uint32_t)(1<<10 | 1<<9)

//===============================
// @ref UART_StopBits_define.
//===============================
#define UART_StopBits_half          (uint32_t)(1<<12)
#define UART_StopBits_1             (uint32_t)(0)
#define UART_StopBits_1_half        (uint32_t)(3<<12)
#define UART_StopBits_2             (uint32_t)(2<<12)

//===============================
//@ref UART_HwFlowCtl_define
//===============================
#define UART_HwFlowCtl_NONE         (uint32_t)(0)
#define UART_HwFlowCtl_RTS          (uint32_t)(1<<8)
#define UART_HwFlowCtl_CTS          (uint32_t)(1<<9)
#define UART_HwFlowCtl_RTS_CTS      (uint32_t)(1<<8 | 1<<9)

//===============================
//@ref UART_IRQ_Enable_define
//===============================
#define UART_IRQ_Enable_NONE        (uint32_t)(0)
#define UART_IRQ_Enable_TXE         (uint32_t)(1<<7) //Transmit data register empty
#define UART_IRQ_Enable_TC          (uint32_t)(1<<6) //Transmission complete
#define UART_IRQ_Enable_RXNEIE      (uint32_t)(1<<5) //Received data ready to be read & Overrun error detected
#define UART_IRQ_Enable_PE          (uint32_t)(1<<8) //Parity error






/**************************************************************************************/
// Generic Macros
//********************************
#define USARTDIV_MUL100(PCLK,BAUD)		(unsigned int)(25*PCLK)/(4*BAUD)
#define Mantissa(PCLK,BAUD)				(unsigned int)(USARTDIV_MUL100(PCLK,BAUD)/100)
#define DIV_Fraction(PCLK,BAUD)			(unsigned int)(((USARTDIV_MUL100(PCLK,BAUD) % 100 ) * 4 ) / 25)
#define UART_BRR_Register(PCLK,BAUD)	((Mantissa(PCLK,BAUD) << 4 )|(DIV_Fraction(PCLK,BAUD) & 0xF))


/**************************************************************************************/
// APIs supports "MCAL USART Driver"
//********************************
void MCAL_USART_Init(USART_TypeDef* USARTx ,USART_Config_t* UART_Config);
void MCAL_USART_Deinit(USART_TypeDef* USARTx);

void MCAL_USART_SetPins(USART_TypeDef* USARTx);

void MCAL_USART_SendData(USART_TypeDef* USARTx, uint16_t* pTxBuffer,UART_PollingMechanism PollingEn);
void MCAL_USART_ReceiveData(USART_TypeDef* USARTx, uint16_t* pRxBuffer,UART_PollingMechanism PollingEn);

void MCAL_USART_waitTC(USART_TypeDef* USARTx);


#endif /* INC_STM32F103X6_USART_DRIVER_H_ */
