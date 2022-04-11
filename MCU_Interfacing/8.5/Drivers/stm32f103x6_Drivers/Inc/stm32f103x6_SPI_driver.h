/*
 * stm32f103x6_SPI_driver.h
 *
 *  Created on: Apr 10, 2022
 *      Author: Hassan
 */

#ifndef INC_STM32F103X6_SPI_DRIVER_H_
#define INC_STM32F103X6_SPI_DRIVER_H_

//********************************
// Includes
//********************************
#include "stm32f103x6.h"
#include "stm32f103x6_gpio_driver.h"


/**************************************************************************************/
// Configuration Structures
//********************************
typedef struct{
	uint8_t	TXE:1;		//Tx Buffer empty Interrupt
	uint8_t	RXNE:1;		//Rx Buffer not empty Interrupt
	uint8_t	ERRI:1;		//Error Interrupt
	uint8_t	Reserved:5;
}SPI_IRQSrc_t;

typedef struct{
	uint8_t 	Device_Mode;				/*specifies the SPI operating mode
											this parameter must be set based on @ref SPI_Device_define*/
	uint16_t	Communication_Mode;			/*specifies SPI bidirectional mode state
											this parameter must be set based on @ref SPI_Comm_define*/
	uint8_t 	Frame_Format;				/*specifies the SPI Frame format
											this parameter must be set based on @ref SPI_Frame_define*/
	uint16_t 	Data_Size;					/*specifies the SPI data Size
											this parameter must be set based on @ref SPI_DataSize_define*/
	uint8_t 	Clk_Polarity;				/*specifies the SPI Clk polarity
											this parameter must be set based on @ref SPI_ClkPolarity_define*/
	uint8_t 	Clk_Phase;					/*specifies the SPI Clk phase
											this parameter must be set based on @ref SPI_ClkPhase_define*/
	uint16_t 	NSS;						/*specifies whether the NSS signal managed by HW (NSS Pin) or
											by SW using the SSI bit enabler
											this parameter must be set based on @ref SPI_NSS_define*/
	uint16_t 	Baud_Prescaler;				/*specifies Baud rate prescaler value which will configure
	 	 	 	 	 	 	 	 	 	 	 Tx and Rx SCK clock
											this parameter must be set based on @ref SPI_BaudPrescaler_define*/
	uint8_t		IRQ_En;						/*Enable/Disable the EXTI IRQ (will enable the IRQ mask on both EXTI and NVIC)
											this parameter must be set based on @ref SPI_IRQ_define*/
	void (*P_IRQ_CallBack)(SPI_IRQSrc_t );	//sets the C function which will be called when IRQ happen

}SPI_Config_t;

typedef enum{
	SPI_disable, SPI_enable
}SPI_PollingMechanism;

/**************************************************************************************/
// generic Macros
//********************************



/**************************************************************************************/
// Macro Configuration references
//********************************
//===============================
// @ref SPI_Device_define
//===============================
#define SPI_Device_Slave							(0x00U)		//Normal Mode upon Reset
#define SPI_Device_Master							(1U<<2)		//CR1. MSTR:1 Master configuration
//===============================
// @ref SPI_Comm_define
//===============================
#define SPI_Comm_direction_2lines					(0x0000U)	//Normal Mode upon Reset
#define SPI_Comm_direction_2lines_RxOnly			(1U<<10)	//CR1. Bit 10 RXONLY: Receive only
#define SPI_Comm_direction_1lines_RxOnly			(1U<<15)	//CR1. Bit 15 BIDIMODE: Bidirectional data mode enable
#define SPI_Comm_direction_1lines_TxOnly	((1U<<15)|(1U<<14))	//CR1. Bit 15 BIDIMODE: Bidirectional data mode enable
																//CR1. Bit 14 BIDIOE: Output enable in bidirectional mode
//===============================
// @ref SPI_Frame_define
//===============================
#define SPI_Frame_MSB_First							(0x00U)		//Normal Mode upon Reset
#define SPI_Frame_LSB_First							(1U<<7)		//CR1. Bit 7 LSBFIRST: Frame format
//===============================
// @ref SPI_DataSize_define
//===============================
#define SPI_DataSize_8Bit							(0x0000U)	//Normal Mode upon Reset
#define SPI_DataSize_16Bit							(1U<<11)	//CR1. Bit 11 DFF: Data frame format
//===============================
// @ref SPI_ClkPolarity_define
//===============================
#define SPI_ClkPolarity_Low_idle					(0x00U)		//Normal Mode upon Reset
#define SPI_ClkPolarity_High_idle					(1U<<1)		//CR1. Bit1 CPOL: Clock polarity
//===============================
// @ref SPI_ClkPhase_define
//===============================
#define SPI_ClkPhase_1stClk_Data_CaptureEdge		(0x00U)		//Normal Mode upon Reset
#define SPI_ClkPhase_2ndClk_Data_CaptureEdge		(1U<<0)		//CR1. Bit 0 CPHA: Clock phase
//===============================
// @ref SPI_NSS_define
//===============================
// HW
#define SPI_NSS_HW_Slave							(0x00U)		//Normal Mode upon Reset
#define SPI_NSS_HW_Master_SSOut_en					(1U<<2)		//Bit 2 SSOE: SS output enable
#define SPI_NSS_HW_Master_SSOut_dis					~(1U<<2)	//Bit 2 SSOE: SS output disable
// SW (master or slave)
#define SPI_NSS_SW_SSI_Reset						(1U<<9)		//Bit 9 SSM: Software slave management
#define SPI_NSS_SW_SSI_Set					((1U<<9)|(1U<<8))	//Bit 9 SSM: Software slave management
																//Bit 8 SSI: Internal slave select
//===============================
// @ref SPI_BaudPrescaler_define
//===============================
#define SPI_BaudPrescaler_2					(0b000U<<3)
#define SPI_BaudPrescaler_4					(0b001U<<3)
#define SPI_BaudPrescaler_8					(0b010U<<3)
#define SPI_BaudPrescaler_16				(0b011U<<3)
#define SPI_BaudPrescaler_32				(0b100U<<3)
#define SPI_BaudPrescaler_64				(0b101U<<3)
#define SPI_BaudPrescaler_128				(0b110U<<3)
#define SPI_BaudPrescaler_256				(0b111U<<3)
//===============================
// @ref SPI_IRQ_define
//===============================
#define SPI_IRQ_Enable_NONE					(uint8_t)(0)
#define SPI_IRQ_Enable_TXEIE				(uint8_t)(1<<7) //SPI_CR2. Bit 7 TXEIE: Tx buffer empty interrupt enable
#define SPI_IRQ_Enable_RXNEIE				(uint8_t)(1<<6) //SPI_CR2. Bit 6 RXNEIE: RX buffer not empty interrupt enable
#define SPI_IRQ_Enable_ERRIE				(uint8_t)(1<<5) //SPI_CR2. Bit 5 ERRIE: Error interrupt enable

/**************************************************************************************/
// APIs supports "MCAL SPI Driver"
//********************************
void MCAL_SPI_Init(SPI_TypeDef* SPIx,SPI_Config_t* SPI_Config);
void MCAL_SPI_Deinit(SPI_TypeDef* SPIx);

void MCAL_SPI_SetPin(SPI_TypeDef* SPIx);

void MCAL_SPI_SendData(SPI_TypeDef* SPIx,uint16_t* pTxBuffer,SPI_PollingMechanism PollingEn);
void MCAL_SPI_ReciveData(SPI_TypeDef* SPIx,uint16_t* pRxBuffer,SPI_PollingMechanism PollingEn);

void MCAL_SPI_Tx_Rx(SPI_TypeDef* SPIx,uint16_t* pTxBuffer,SPI_PollingMechanism PollingEn);

#endif /* INC_STM32F103X6_SPI_DRIVER_H_ */
