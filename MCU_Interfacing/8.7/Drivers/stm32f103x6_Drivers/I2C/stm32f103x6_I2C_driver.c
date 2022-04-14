/*
 * stm32f103x6_I2C_driver.c
 *
 *  Created on: Apr 12, 2022
 *      Author: Hassan
 */

//********************************
// Includes
//********************************
#include "stm32f103x6_I2C_driver.h"


/**************************************************************************************/
// Generic Macros
//********************************


/**************************************************************************************/
// Generic Variables
//********************************
I2C_Config_t I2C_Cfg[2] ;


/**************************************************************************************/
// Generic Functions
//********************************
Flag_Status I2C_Get_FlagStatus(I2C_TypeDef* I2Cx,Status flag){
	volatile uint32_t dummy =0;
	uint32_t flag1, flag2,lastevent;
	Flag_Status bitsatus = reset;
	switch(flag){
	case I2C_FLAG_BUSY:
		//		Bit 1 BUSY: Bus busy
		//		0: No communication on the bus
		//		1: Communication ongoing on the bus
		//		– Set by hardware on detection of SDA or SCL low
		//		– cleared by hardware on detection of a Stop condition.
		//		It indicates a communication in progress on the bus. This information is still updated when
		//		the interface is disabled (PE=0).
		if((I2Cx->SR[1]) & (I2C_SR2_BUSY))	bitsatus = set;
		else	bitsatus = reset;
		break;
	case EV5 :	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
		//		Bit 0 SB: Start bit (Master mode)
		//		0: No Start condition
		//		1: Start condition generated.
		//		– Set when a Start condition generated.
		//		– Cleared by software by reading the SR1 register followed by writing the DR register, or by
		//		hardware when PE=0
		if((I2Cx->SR[0]) & (I2C_SR1_SB))	bitsatus = set;
		else	bitsatus = reset;
		break;
	case EV6 :	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
		//		Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
		if((I2Cx->SR[0]) & (I2C_SR1_ADDR))	bitsatus = set;
		else	bitsatus = reset;
		//to clear ADDR1: followed by reading SR2.
		dummy = I2Cx->SR[1];
		break;
	case EV7://EV7: RxNE=1, cleared by reading DR register
		//		Bit 6 RxNE: Data register not empty (receivers)
		//		0: Data register empty
		//		1: Data register not empty
		if((I2Cx->SR[0]) & (I2C_SR1_RXNE))	bitsatus = set;
		else	bitsatus = reset;
		break;
	case EV8_1 :	//EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	case EV8 :		//EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
		//		Bit 7 TxE: Data register empty (transmitters)
		//		0: Data register not empty
		//		1: Data register empty
		if((I2Cx->SR[0]) & (I2C_SR1_TXE))	bitsatus = set;
		else	bitsatus = reset;
		break;
	case EV8_2 :	//EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
		//		Bit 2 BTF: Byte transfer finished
		//		0: Data byte transfer not done
		//		1: Data byte transfer succeeded
		if((I2Cx->SR[0]) & (I2C_SR1_TXE | I2C_SR1_BTF))	bitsatus = set;
		else	bitsatus = reset;
		break;
	case MASTER_Byte_Transmitting:
		//read both SR registers
		flag1 =  I2Cx->SR[0];
		flag2 =  I2Cx->SR[1];
		flag2 = flag2 << 16;
		//get last event from i2c status register
		lastevent = (flag1 | flag2) & ((uint32_t)0x00FFFFFF);
		//checks wether last event contains the I2C_EVENT
		if((lastevent & flag ) == flag)	bitsatus = set;
		else	bitsatus = reset;
		break;
	}
	return bitsatus;
}

void I2C_generate_Start(I2C_TypeDef* I2Cx,Functional_State state, Repeat_Start start){
	if(start != Repeated){
		//check if bus is idle as it's new start
		while(I2C_Get_FlagStatus(I2Cx, I2C_FLAG_BUSY));
	}
	//	Bit 8 START: Start generation
	//	This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
	//	In Master Mode:
	//	0: No Start generation
	//	1: Repeated start generation
	//	In Slave mode:
	//	0: No Start generation
	//	1: Start generation when the bus is free
	if(state != Disable)	I2Cx->CR[0] |= I2C_CR1_START;	//generate start
	else 					I2Cx->CR[0] &= ~I2C_CR1_START;	//disable start
}


void I2C_generate_ACK(I2C_TypeDef* I2Cx,Functional_State state){
	//	Bit 10 ACK: Acknowledge enable
	//	0: No acknowledge returned
	//	1: Acknowledge returned after a byte is received (matched address or data)
	if(state == Enable)	I2Cx->CR[0] |= I2C_CR1_ACK ;
	else				I2Cx->CR[0] &= ~I2C_CR1_ACK;
}

void I2C_generate_Stop(I2C_TypeDef* I2Cx,Functional_State state){
	//	Bit 9 STOP: Stop generation
	//	0: No Stop generation.
	//	1: Stop generation after the current byte transfer or after the current Start condition is sent.
	if(state == Enable)	I2Cx->CR[0] |= I2C_CR1_STOP ;
	else				I2Cx->CR[0] &= ~I2C_CR1_STOP;

}


void I2C_Send_Address(I2C_TypeDef* I2Cx,uint16_t address, Direction direction){
	//empty the direction bit
	address = address << 1;

	//add the direction bit: 0 Write / 1 Read
	address += direction;
	I2Cx->DR = address;

}


/**************************************************************************************/
// APIs
//********************************

void MCAL_I2C_Init(I2C_TypeDef* I2Cx,I2C_Config_t* I2C_Config){
	uint16_t tempreg = 0 , freqrange =0;
	uint32_t pclk1 = 8000000; //default value for PCLK1

	//enable RCC clk and
	if(I2Cx == I2C1){
		I2C_Cfg[0] = *I2C_Config;
		RCC_I2C1_CLK_EN();
	}
	else{
		I2C_Cfg[1] = *I2C_Config;
		RCC_I2C2_CLK_EN();
	}
	//check for device mode to be I2C
	if(I2C_Config->Device_Mode == I2C_Device_I2C){
		/*******************	Init Timing		***************************/
		tempreg = I2Cx->CR[1];
		//clear FREQ[5:0] bits
		tempreg &= ~(I2C_CR2_FREQ_Msk);
		//get pclk
		pclk1 = MCAL_RCC_GetPClk1Freq();
		//set FREQ[5:0] from depending on pclk1
		freqrange = (uint16_t)(pclk1/1000000);
		tempreg |= freqrange;
		I2Cx->CR[1] = tempreg;

		// configure the CCR
		I2Cx->CR[0] &= ~(I2C_CR1_PE); // disable the peripheral
		tempreg = 0;

		switch(I2C_Config->I2C_ClkSpeed){
		case I2C_SCLK_SM_100k:
		case I2C_SCLK_SM_50k :
			tempreg |= (uint16_t)(pclk1 / (I2C_Config->I2C_ClkSpeed << 1));
			I2Cx->CCR = tempreg;
			I2Cx->TRISE = freqrange +1;
			break;
		default:
			// Fast mode not supported yet
			break;
		}
		// configure to I2C_CR1
		tempreg = I2Cx->CR[0];
		tempreg = (uint16_t)(I2C_Config->ACK_Ctrl | I2C_Config->Device_Mode | I2C_Config->Genral_CallAdd_Detection | I2C_Config->Stretch_Mode );
		I2Cx->CR[0] = tempreg;

		// configure   I2C_OAR1 & I2C_OAR2
		tempreg = 0;
		if(I2C_Config->I2C_SlaveAdd.En_DualAdd == 1){
			tempreg = I2C_OAR2_ENDUAL;
			tempreg |= I2C_Config->I2C_SlaveAdd.Secondary_SlaveAdd << I2C_OAR2_ADD2_Pos;
			I2Cx->OAR[1] = tempreg;
		}
		tempreg =0;
		tempreg |= I2C_Config->I2C_SlaveAdd.Primary_SlaveAdd << I2C_SR1_ADDR_Pos;
		tempreg |= I2C_Config->I2C_SlaveAdd.Slave_Addressing_Mode;
		I2Cx->OAR[0] = tempreg;
	}
	else{
		//MSBus mode, note supported yet
	}
	if(I2C_Config->P_Slave_CallBack != NULL){
		//enable IQR
		I2Cx->CR[1] |= I2C_CR2_ITERREN;
		I2Cx->CR[1] |= I2C_CR2_ITEVTEN;
		I2Cx->CR[1] |= I2C_CR2_ITBUFEN;

		if(I2Cx == I2C1){
			NVIC_IRQ31_I2C1_EV_Enable;
			NVIC_IRQ32_I2C1_ER_Enable;
		}
		else if(I2Cx == I2C2){
			NVIC_IRQ33_I2C2_EV_Enable;
			NVIC_IRQ34_I2C2_ER_Enable;
		}
		I2Cx->SR[0] = 0;
		I2Cx->SR[1] = 0;
	}
	I2Cx->CR[0] |= I2C_CR1_PE; // enable the peripheral
}

void MCAL_I2C_Deinit(I2C_TypeDef* I2Cx){
	if(I2Cx == I2C1){
		NVIC_IRQ31_I2C1_EV_Disable;
		NVIC_IRQ32_I2C1_ER_Disable;
		RCC_I2C1_RESET();
	}
	else if(I2Cx == I2C2){
		NVIC_IRQ33_I2C2_EV_Disable;
		NVIC_IRQ34_I2C2_ER_Disable;
		RCC_I2C2_RESET();
	}
}

void MCAL_I2C_SetPin(I2C_TypeDef* I2Cx){
	GPIO_PinConfig_t PinCfg;
	if(I2Cx == I2C1){
		//I2C1_SCL PB6
		PinCfg.GPIO_PinNumber = GPIO_Pin_6;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_OD;
		PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);
		//I2C1_SDA PB7
		PinCfg.GPIO_PinNumber = GPIO_Pin_7;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_OD;
		PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);
	}
	else if(I2Cx == I2C2){
		//I2C2_SCL PB10
		PinCfg.GPIO_PinNumber = GPIO_Pin_10;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_OD;
		PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);
		//I2C2_SDA PB11
		PinCfg.GPIO_PinNumber = GPIO_Pin_11;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_OD;
		PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);
	}
}


void MCAL_I2C_Master_Tx(I2C_TypeDef* I2Cx,uint16_t Slave_Address,uint8_t* data,uint32_t dataLen,Stop_Condition stop,Repeat_Start start){
	uint32_t i;
	//1. generate a start condition by setting start bit in I2C_CR1
	I2C_generate_Start(I2Cx, Enable, start);

	//2. wait for event 5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	while(!I2C_Get_FlagStatus(I2Cx, EV5));

	//3. send slave address
	I2C_Send_Address(I2Cx, Slave_Address, Write);

	//4. check for acknowledge EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!I2C_Get_FlagStatus(I2Cx, EV6));

	//5. check for TRA, BUSY, MSL, TXE flags
	while(!I2C_Get_FlagStatus(I2Cx, MASTER_Byte_Transmitting));

	//6. send all the data
	for(i = 0 ; i<dataLen;i++){
		I2Cx->DR = data[i];
		//7. wait event EV8
		//EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
		while(!I2C_Get_FlagStatus(I2Cx, EV8));
	}
	//8.wait for EV8_2
	//EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	while(!I2C_Get_FlagStatus(I2Cx, EV8_2));

	if(stop == with_stop){
	//9.send stop condition
		I2C_generate_Stop(I2Cx, Enable);
	}
}


void MCAL_I2C_Master_Rx(I2C_TypeDef* I2Cx,uint16_t Slave_Address,uint8_t* data,uint32_t dataLen,Stop_Condition stop,Repeat_Start start){

	uint8_t index = I2Cx == I2C1 ? 0:1;
	uint32_t i;
	//1. generate a start condition by setting start bit in I2C_CR1
	I2C_generate_Start(I2Cx, Enable, start);

	//2. wait for event 5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	while(!I2C_Get_FlagStatus(I2Cx, EV5));

	//3. send slave address
	I2C_Send_Address(I2Cx, Slave_Address, Read);

	//4. check for acknowledge EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!I2C_Get_FlagStatus(I2Cx, EV6));

	I2C_generate_ACK(I2Cx,Enable);

	if(dataLen){
		for(i=dataLen ; i>1 ; i--){
			while(!I2C_Get_FlagStatus(I2Cx, EV7));
			//5. read data from register
			*data = I2Cx->DR;
			//increment buffer address
			data++;
		}
		//6. send NACK to stop receiving
		I2C_generate_ACK(I2Cx,Disable);

		if(stop == with_stop){
		//7.send stop condition
			I2C_generate_Stop(I2Cx, Enable);
		}
		//re-enable ACK
		if(I2C_Cfg[index].ACK_Ctrl == I2C_ACK_Ctrl_Enable){
			I2C_generate_ACK(I2Cx,Disable);

		}
	}
}


void MCAL_I2C_Slave_Tx(I2C_TypeDef* I2Cx,uint8_t data){

	I2Cx->DR = data;
}


uint8_t MCAL_I2C_Slave_Rx(I2C_TypeDef* I2Cx){

return (uint8_t)(I2Cx->DR);
}



void I2C1_EV_IRQHandler(){

}

void I2C1_ER_IRQHandler(){

}


void I2C2_EV_IRQHandler(){

}


void I2C2_ER_IRQHandler(){

}


