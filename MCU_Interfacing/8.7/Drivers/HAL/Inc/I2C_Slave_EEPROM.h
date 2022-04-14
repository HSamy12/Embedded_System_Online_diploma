/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: Apr 14, 2022
 *      Author: Hassan
 */

#ifndef INC_I2C_SLAVE_EEPROM_H_
#define INC_I2C_SLAVE_EEPROM_H_

//********************************
// Includes
//********************************
#include "stm32f103x6_I2C_driver.h"

/**************************************************************************************/
// Generic Macros
//********************************
#define EEPROM_Slave_Address			(0x2A)

/**************************************************************************************/
// APIs
//********************************
void EEPROM_Init();

void EEPROM_Write_NBytes(uint32_t Mem_Address, uint8_t* Data, uint8_t dataLen);
void EEPROM_ReadByte(uint32_t Mem_Address, uint8_t* Data, uint8_t dataLen);




#endif /* INC_I2C_SLAVE_EEPROM_H_ */
