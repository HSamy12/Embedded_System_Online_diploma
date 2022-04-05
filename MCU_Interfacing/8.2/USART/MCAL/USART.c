/*
 * USART.c
 *
 * Created: 4/3/2022 8:57:27 PM
 *  Author: Hassan
 */ 

#include "USART.h"

char recieve_string[20];


void UART_Init(void){
	// transmission speed
	CLEAR_BIT(UCSRA,U2X);   // Normal Speed
	
	//Frame
	//No parity by default
	//Frame Size 8 bits
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);
	CLEAR_BIT(UCSRB,UCSZ2);
	
	//select asynchronous mode
	CLEAR_BIT(UCSRC,UMSEL);
		
	// baud rate
	UBRRH = 0;
	UBRRL = 51;
	
	//select only one bit for stop
	CLEAR_BIT(UCSRC,USBS);

	//enable
	//Tx Enable
	SET_BIT(UCSRB,TXEN);
	//Rx Enable
	SET_BIT(UCSRB,RXEN);

}

void UART_Send(uint8_t data){
	while(!(READ_BIT(UCSRA,UDRE)));
			UDR = data;
}


uint8_t UART_recive(void){
	while (!(READ_BIT(UCSRA,RXC)));
		return UDR;

}

void UART_send_string(char * str)
{
	while(*str != '\0')
	{
		UART_Send(*str);
		str++;
	}
}

char * UART_recieve_string(void)
{
	uint8_t data= UART_recive();
	int i = 0;
	while(data != '#')
	{
		recieve_string[i] = data;
		data = UART_recive();
		i++;
	}
	recieve_string[i] = '\0';
	return recieve_string;
}