#include "uart.h"

unsigned char String_buffer[100] = "Learn-in-depth:Hassan";
unsigned char const String_buffer1[100] = "rodata";

void main(){

	Uart_Send_String(String_buffer);
}