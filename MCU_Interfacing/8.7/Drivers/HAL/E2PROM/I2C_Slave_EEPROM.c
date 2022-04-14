/*
 * I2C_Slave_EEPROM.c
 *
 *  Created on: Apr 14, 2022
 *      Author: Hassan
 */

//********************************
// Includes
//********************************
#include "I2C_Slave_EEPROM.h"



/**************************************************************************************/
// APIs
//********************************
void EEPROM_Init(){
	//I2C Init
	// PB6 : I2C1_SCL
	// PB7 : I2C1_SDL
	I2C_Config_t I2C1Cfg;

	//I2C controller act as master
	I2C1Cfg.Genral_CallAdd_Detection = I2C_ENGC_Enable;
	I2C1Cfg.ACK_Ctrl = I2C_ACK_Ctrl_Enable;
	I2C1Cfg.I2C_ClkSpeed = I2C_SCLK_SM_100k;
	I2C1Cfg.Device_Mode = I2C_Device_I2C;
	I2C1Cfg.P_Slave_CallBack = NULL;
	I2C1Cfg.Stretch_Mode = I2C_StretchMode_Enable;

	MCAL_I2C_SetPin(I2C1);
	MCAL_I2C_Init(I2C1, &I2C1Cfg);
}


void EEPROM_Write_NBytes(uint32_t Mem_Address, uint8_t* Data, uint8_t dataLen){

	uint8_t i, buffer[256];
	buffer[0] = (uint8_t)(Mem_Address >> 8);	//Upper memory address
	buffer[1] = (uint8_t)(Mem_Address);			//lower memory address

	for(i=2;i<(dataLen+2);i++)
		buffer[i] = Data[i-2];


	MCAL_I2C_Master_Tx(I2C1, EEPROM_Slave_Address, buffer, dataLen+2, with_stop, Not_repeated);

}


void EEPROM_ReadByte(uint32_t Mem_Address, uint8_t* Data, uint8_t dataLen){
	uint8_t buffer[2];
	buffer[0] = (uint8_t)(Mem_Address >> 8);	//Upper memory address
	buffer[1] = (uint8_t)(Mem_Address);			//lower memory address

	//write  address to read from
	MCAL_I2C_Master_Tx(I2C1, EEPROM_Slave_Address, buffer ,2, without_stop, Not_repeated);

	//send to master
	MCAL_I2C_Master_Rx(I2C1, EEPROM_Slave_Address, Data,dataLen, with_stop, Repeated);

}
