/*
 * main.c
 *
 * Created: 4/3/2022 8:50:57 PM
 *  Author: Hassan
 */ 


#include "HAL/Lcd/lcd.h"
#include "MCAL/USART.h"



int main(void)
{
	unsigned char * x;
	LCD_INIT();
	UART_Init();
	

	LCD_WRITE_STRING("UART Lab");

    LCD_GOTO_XY(2,1);
	UART_send_string("Sending...");
 
	
	while(1)
    {
		x = UART_recieve_string(); 
		LCD_WRITE_STRING(x);
    }
}