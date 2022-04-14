/*
 * stm32f103x6_SPI_driver.c
 *
 *  Created on: Apr 10, 2022
 *      Author: Hassan
 */

//********************************
// Includes
//********************************
#include "stm32f103x6_SPI_driver.h"

/**************************************************************************************/
// Generic Macros
//********************************
#define SPI_TXE				(uint8_t)(1U<<1)
#define SPI_RXNE			(uint8_t)(1U<<0)

/**************************************************************************************/
// Generic Variables
//********************************
SPI_Config_t* P_SPI_Cfg[2] = {NULL,NULL};
SPI_Config_t P_SPI_Cfg1;
SPI_Config_t P_SPI_Cfg2;

/**************************************************************************************/
// Generic Functions
//********************************
void SPI1_IRQHandler(){
	SPI_IRQSrc_t irq_Src;

	irq_Src.RXNE = ((SPI1->SR & (1U<<0)) >> 0);
	irq_Src.TXE  = ((SPI1->SR & (1U<<1)) >> 1);
	irq_Src.ERRI = ((SPI1->SR & (1U<<4)) >> 4);

	P_SPI_Cfg[0]->P_IRQ_CallBack(irq_Src);
}

void SPI2_IRQHandler(){
	SPI_IRQSrc_t irq_Src;

	irq_Src.RXNE = ((SPI2->SR & (1U<<0)) >> 0);
	irq_Src.TXE  = ((SPI2->SR & (1U<<1)) >> 1);
	irq_Src.ERRI = ((SPI2->SR & (1U<<4)) >> 4);

	P_SPI_Cfg[1]->P_IRQ_CallBack(irq_Src);
}
/**************************************************************************************/
// APIs
//********************************
/*================================================================
 * @Fn			-MCAL_SPI_Init
 * @brief 		-Initializes the SPIx with specified Pin Configurations
 * @param [in] 	-SPIx: where x is SPI peripheral (1,2 depend on device)
 * @param [in] 	-SPI_Config: pointer to SPI_Config_t structure that contains
 * 				 configuration information for specified SPI.
 * @retval 		-none
 * Note			-none
 */
void MCAL_SPI_Init(SPI_TypeDef* SPIx,SPI_Config_t* SPI_Config){
	//Saftey for registers
	uint16_t tmpCR1 =0;
	uint16_t tmpCR2 =0;

	if(SPIx == SPI1){
		P_SPI_Cfg1 = *SPI_Config;
		P_SPI_Cfg[0] = &P_SPI_Cfg1;
		RCC_SPI1_CLK_EN();
	}
	else if(SPIx == SPI2){
		P_SPI_Cfg2 = *SPI_Config;
		P_SPI_Cfg[1] = &P_SPI_Cfg2;
		RCC_SPI2_CLK_EN();
	}

	//Enable SPI
	tmpCR1 = (1U<<6);

	//master or slave
	tmpCR1 |= SPI_Config->Device_Mode;

	//communication mode
	tmpCR1 |= SPI_Config->Communication_Mode;

	//frame format
	tmpCR1 |= SPI_Config->Frame_Format;

	//data size
	tmpCR1 |= SPI_Config->Data_Size;

	//clk polarity
	tmpCR1 |= SPI_Config->Clk_Polarity;

	//clk phase
	tmpCR1 |= SPI_Config->Clk_Phase;

	//NSS
	if(SPI_Config->NSS == SPI_NSS_HW_Master_SSOut_en){
		tmpCR2 |= SPI_Config->NSS;
	}
	else if(SPI_Config->NSS == SPI_NSS_HW_Master_SSOut_dis){
		tmpCR2 &= SPI_Config->NSS;
	}
	else{
		tmpCR1 |= SPI_Config->NSS;
	}

	//Baud rate
	tmpCR1 |= SPI_Config->Baud_Prescaler;

	//IRQ enable
	if(SPI_Config->IRQ_En != SPI_IRQ_Enable_NONE){
		tmpCR2 |= SPI_Config->IRQ_En;

		if(SPIx == SPI1){
			NVIC_IRQ35_SPI1_Enable;
		}
		else if(SPIx == SPI2){
			NVIC_IRQ36_SPI2_Enable;
		}
	}

	SPIx->CR[0]=tmpCR1;
	SPIx->CR[1]=tmpCR2;
}



/**================================================================
 * @Fn				-MCAL_SPI_Deinit
 * @brief 			- DEInitializes SPI
 * @param [in] 		- SPIx: where x can be (1,2 depending on device used)
 * @retval 			-none
 * Note				-Reset the Model By RCC
 */
void MCAL_SPI_Deinit(SPI_TypeDef* SPIx){
	if(SPIx == SPI1){
		RCC_SPI1_RESET();
		NVIC_IRQ35_SPI1_Disable;
	}
	else if(SPIx == SPI2){
		RCC_SPI2_RESET();
		NVIC_IRQ36_SPI2_Disable;
	}
}


/*********************************************************************
 * @fn     			-MCAL_SPI_SendData
 * @brief           -Send Buffer on SPI
 * @param [in]		-SPIx: where x can be (1,2 depending on device used)
 * @param[in]       -pTxBuffer Buffer
 * @param[in]       -PollingEn   Enable pooling or disable it
 * @return          -none
 * @Note            -Should initialize SPI First
 */
void MCAL_SPI_SendData(SPI_TypeDef* SPIx,uint16_t* pTxBuffer,SPI_PollingMechanism PollingEn){
	if(PollingEn == SPI_enable){
		while(!(SPIx->SR & SPI_TXE));
	}
	SPIx->DR = *pTxBuffer;
}




/*********************************************************************
 * @fn     			-MCAL_SPI_ReciveData
 * @brief           -Recive Buffer on SPI
 * @param [in]		-SPIx: where x can be (1,2 depending on device used)
 * @param[in]       -pRxBuffer Buffer
 * @param[in]       -PollingEn   Enable pooling or disable it
 * @return          -none
 * @Note            -Should initialize SPI First
 */
void MCAL_SPI_ReciveData(SPI_TypeDef* SPIx,uint16_t* pRxBuffer,SPI_PollingMechanism PollingEn){
	if(PollingEn == SPI_enable){
		while(!(SPIx->SR & SPI_RXNE));
	}
	*pRxBuffer = SPIx->DR;
}


/*********************************************************************
 * @fn     			-MCAL_SPI_Tx_Rx
 * @brief           -Send and receive Buffer on SPI
 * @param [in]		-SPIx: where x can be (1,2 depending on device used)
 * @param[in]       -pTxBuffer Buffer
 * @param[in]       -PollingEn   Enable pooling or disable it
 * @return          -none
 * @Note            -Should initialize SPI First
 */
void MCAL_SPI_Tx_Rx(SPI_TypeDef* SPIx,uint16_t* pTxBuffer,SPI_PollingMechanism PollingEn){
	MCAL_SPI_SendData(SPIx,pTxBuffer,PollingEn);

	MCAL_SPI_ReciveData(SPIx,pTxBuffer,PollingEn);
}



/*********************************************************************
 * @Fn				-MCAL_SPI_SetPins
 * @brief 			- initialize GPIO Pins
 * @param [in] 		- SPIx: where x can be (1,2 depending on device used)
 * @retval 			-none
 * Note				-Should enable the corresponding ALT  & GPIO  in RCC clock Also called after MCAL_SPI_Init()
 */
void MCAL_SPI_SetPin(SPI_TypeDef* SPIx){
	GPIO_PinConfig_t PinCfg;
	if(SPIx == SPI1){
		//PA4:SPI1_NSS
		//PA5:SPI1_SCK
		//PA6:SPI1_MISO
		//PA7:SPI1_MOSI
		if(P_SPI_Cfg[0]->Device_Mode == SPI_Device_Master){
			//PA4:SPI1_NSS
			if(P_SPI_Cfg[0]->NSS == SPI_NSS_HW_Master_SSOut_dis){ //Hardware master /slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_Pin_4;
				PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}
			else if(P_SPI_Cfg[0]->NSS == SPI_NSS_HW_Master_SSOut_en){
				//Hardware master/ NSS output enabled Alternate function push-pull
				PinCfg.GPIO_PinNumber = GPIO_Pin_4;
				PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_PP;
				PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}
			//PA5:SPI1_SCK master Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_Pin_5;
			PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_PP;
			PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA6:SPI1_MISO Full duplex / master Input floating
			PinCfg.GPIO_PinNumber = GPIO_Pin_6;
			PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA7:SPI1_MOSI Full duplex / master Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_Pin_7;
			PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_PP;
			PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
		else{//Slave
			if(P_SPI_Cfg[0]->NSS == SPI_NSS_HW_Slave){
				//PA4:SPI1_NSS Hardware master /slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_Pin_4;
				PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}
			//PA5:SPI1_SCK Slave Input floating
			PinCfg.GPIO_PinNumber = GPIO_Pin_5;
			PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA6:SPI1_MISO Full duplex / slave (point to point) Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_Pin_6;
			PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_PP;
			PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA7:SPI1_MOSI Full duplex / slave Input floating
			PinCfg.GPIO_PinNumber = GPIO_Pin_7;
			PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
	}
	else if(SPIx == SPI2){
		//PB12:SPI2_NSS
		//PB13:SPI2_SCK
		//PB14:SPI2_MISO
		//PB15:SPI2_MOSI
		if(P_SPI_Cfg[1]->Device_Mode == SPI_Device_Master){
			//PB12:SPI2_NSS
			if(P_SPI_Cfg[1]->NSS == SPI_NSS_HW_Master_SSOut_dis){ //Hardware master /slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_Pin_12;
				PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}
			else if(P_SPI_Cfg[1]->NSS == SPI_NSS_HW_Master_SSOut_en){
				//Hardware master/ NSS output enabled Alternate function push-pull
				PinCfg.GPIO_PinNumber = GPIO_Pin_12;
				PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_PP;
				PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}
			//PB13:SPI2_SCK master Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_Pin_13;
			PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_PP;
			PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//PB14:SPI2_MISO Full duplex / master Input floating
			PinCfg.GPIO_PinNumber = GPIO_Pin_14;
			PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//PB15:SPI2_MOSI Full duplex / master Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_Pin_15;
			PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_PP;
			PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}
		else{//Slave
			if(P_SPI_Cfg[0]->NSS == SPI_NSS_HW_Slave){
				//PB12:SPI2_NSS Hardware master /slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_Pin_12;
				PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}
			//PB13:SPI1_SCK Slave Input floating
			PinCfg.GPIO_PinNumber = GPIO_Pin_13;
			PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//PB14:SPI1_MISO Full duplex / slave (point to point) Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_Pin_14;
			PinCfg.GPIO_MODE = GPIO_MODE_AF_Out_PP;
			PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//PB15:SPI1_MOSI Full duplex / slave Input floating
			PinCfg.GPIO_PinNumber = GPIO_Pin_15;
			PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}
	}
}


