/********************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ********************************************************************************
*/


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif




#include "stm32f103x6.h"
#include "stm32f103x6_gpio_driver.h"
#include "stm32f103x6_USART_driver.h"
#include "stm32f103x6_EXTI_driver.h"
#include "lcd.h"




void clk_init(){
	//Enable clk for GPIOA
	RCC_GPIOA_CLK_EN();
	//Enable clk for GPIOB
	RCC_GPIOB_CLK_EN();
	//Enable clk for AFIO
	RCC_AFIO_CLK_EN();

}

unsigned short channel;

void USART_IRQ_CallBack(void){

	MCAL_USART_ReceiveData(USART1, &channel, disable);
	MCAL_USART_SendData(USART1, &channel, enable);
}

int main(void)
{	// initialization
	clk_init();
	USART_Config_t  uart_Cfg;


	uart_Cfg.Baud_Rate = USART_BaudRate_115200;
	uart_Cfg.HwFlowCtl = UART_HwFlowCtl_NONE;
	uart_Cfg.IRQ_Enable = UART_IRQ_Enable_RXNEIE;
	uart_Cfg.P_IRQ_CallBack = USART_IRQ_CallBack;
	uart_Cfg.Parity =UART_Parity__NONE;
	uart_Cfg.Payload_length = USART_Payload_8Bits;
	uart_Cfg.StopBits = UART_StopBits_1;
	uart_Cfg.USART_MODE = USART_MODE_Tx_Rx;

	MCAL_USART_Init(USART1, &uart_Cfg);
	MCAL_USART_SetPins(USART1);

    /* Loop forever */
	while(1){

	}
}

