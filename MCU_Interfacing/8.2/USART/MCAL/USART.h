/*
 * USART.h
 *
 * Created: 4/3/2022 8:57:41 PM
 *  Author: Hassan
 */ 


#ifndef USART_H_
#define USART_H_

#include <util/delay.h>
#include "../AVRMemoryMap.h"


void UART_Init(void);

void UART_Send(uint8_t data);
uint8_t UART_recive(void);
void UART_send_string(char * str);
char * UART_recieve_string(void);

#endif /* USART_H_ */