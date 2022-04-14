/*
 * stm32f103x6_I2C_driver.h
 *
 *  Created on: Apr 12, 2022
 *      Author: Hassan
 */

#ifndef INC_STM32F103X6_I2C_DRIVER_H_
#define INC_STM32F103X6_I2C_DRIVER_H_

//********************************
// Includes
//********************************
#include "stm32f103x6.h"
#include "stm32f103x6_RCC_driver.h"
#include "stm32f103x6_gpio_driver.h"


/**************************************************************************************/
// Configuration Structures
//********************************
typedef enum{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_MATCHED,
	I2C_EV_DATA_REQ,	//the app layer should send data
	I2C_EV_DATA_RCV		//the app layer should read data
}Slave_State;

typedef enum{
	I2C_FLAG_BUSY,		//BUSY: Bus busy, It indicates a communication in progress on the bus. This information is still updated when the interface is disabled (PE=0).
	EV5,				//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	EV6,				//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	EV7,				//EV7: RxNE=1, cleared by reading DR register
	EV8_1,				//EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	EV8,				//EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
	EV8_2,				//EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	MASTER_Byte_Transmitting = ((uint32_t)0x00070080)

}Status;


typedef struct{
	uint8_t		En_DualAdd;		//Enable 1 / Disable 0
	uint16_t	Primary_SlaveAdd;
	uint16_t	Secondary_SlaveAdd;
	uint16_t	Slave_Addressing_Mode; // @ref Slave_Addressing_define
}I2C_Slave_Address_t;

typedef struct{
	uint8_t 	Device_Mode;				/*specifies the I2C operating mode
											this parameter must be set based on @ref I2C_Device_define*/
	uint32_t	I2C_ClkSpeed;				/*specifies the I2C clock line Speed
											this parameter must be set based on @ref I2C_SCLK_define*/
	uint16_t	Stretch_Mode;				/*specifies whether stretch ON or OFF
											this parameter must be set based on @ref I2C_StretchMode_define*/
	I2C_Slave_Address_t	I2C_SlaveAdd;		/* this parameter specifies the address of device when on slave mode
											this parameter is set based on @ref I2C_Slave_Addressing_define*/
	uint16_t	ACK_Ctrl;					/* this parameter enables / disables acknowledge bit
											this parameter must be set based on @ref I2C_ACK_Ctrl_define*/

	uint16_t	Genral_CallAdd_Detection;	/*this parameter enables / disables general call
											this parameter must be set based on @ref I2C_ENGC_define*/
	void (*P_Slave_CallBack)(Slave_State);	//sets the C function which will be called when IRQ happen

}I2C_Config_t;

typedef enum{
	without_stop,
	with_stop
}Stop_Condition;

typedef enum{
	Not_repeated,
	Repeated
}Repeat_Start;

typedef enum{
	Disable,
	Enable
}Functional_State;

typedef enum{
	reset,
	set
}Flag_Status;

typedef enum{
	Write,
	Read
}Direction;



/**************************************************************************************/
// generic Macros
//********************************



/**************************************************************************************/
// Macro Configuration references
//********************************
//===============================
// @ref I2C_Device_define
//===============================
//I2C_CR1 register Bit 1 SMBUS: SMBus mode
//0: I2C mode
//1: SMBus mode
#define I2C_Device_I2C				(0U)
#define I2C_Device_SMBus			I2C_CR1_SMBUS

//===============================
// @ref I2C_SCLK_define
//===============================
/******
 * standard speed up to 100khz
 * fast speed up to 400khz
 * configure clock before enabling the peripheral
 * from  FREQ[5:0]: Peripheral clock frequency
 * configure clock control register (CCR)
 * 		Thigh = CCR * Tpclk1
 * 		SM or FM
 * Configure rise time register (I2C_TRISE)
 */
#define	I2C_SCLK_SM_50k				(50000U)
#define	I2C_SCLK_SM_100k			(100000U)
#define	I2C_SCLK_FM_200k			(200000U)	//Fast mode not supported yet
#define	I2C_SCLK_FM_400k			(400000U)	//Fast mode not supported yet

//===============================
// @ref I2C_StretchMode_define
//===============================
// in I2C_CR1 Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
//0: Clock stretching enabled
//1: Clock stretching disabled
#define I2C_StretchMode_Enable		(0U)
#define I2C_StretchMode_Disable		I2C_CR1_NOSTRETCH

//===============================
// @ref I2C_Slave_Addressing_define
//===============================
#define I2C_Slave_Addressing_7Bit		(0U)
#define I2C_Slave_Addressing_10Bit		(1U<<15)

//===============================
// @ref I2C_ACK_Ctrl_define
//===============================
//Bit 10 ACK: Acknowledge enable
//0: No acknowledge returned
//1: Acknowledge returned after a byte is received (matched address or data)
#define I2C_ACK_Ctrl_Enable				(I2C_CR1_ACK)
#define I2C_ACK_Ctrl_Disble				(0U)

//===============================
// @ref I2C_ENGC_define
//===============================
//Bit 6 ENGC: General call enable
//0: General call disabled. Address 00h is NACKed.
//1: General call enabled. Address 00h is ACKed
#define I2C_ENGC_Enable				(I2C_CR1_ENGC)
#define I2C_ENGC_Disble				(0U)


/**************************************************************************************/
// APIs supports "MCAL I2C Driver"
//********************************
void MCAL_I2C_Init(I2C_TypeDef* I2Cx,I2C_Config_t* I2C_Config);
void MCAL_I2C_Deinit(I2C_TypeDef* I2Cx);

void MCAL_I2C_SetPin(I2C_TypeDef* I2Cx);

void MCAL_I2C_Master_Tx(I2C_TypeDef* I2Cx,uint16_t Slave_Address,uint8_t* data,uint32_t dataLen,Stop_Condition stop,Repeat_Start start);
void MCAL_I2C_Master_Rx(I2C_TypeDef* I2Cx,uint16_t Slave_Address,uint8_t* data,uint32_t dataLen,Stop_Condition stop,Repeat_Start start);

void MCAL_I2C_Slave_Tx(I2C_TypeDef* I2Cx,uint8_t data);
uint8_t MCAL_I2C_Slave_Rx(I2C_TypeDef* I2Cx);


#endif /* INC_STM32F103X6_I2C_DRIVER_H_ */
