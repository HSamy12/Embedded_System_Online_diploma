/*
 * SPI_Master.c
 *
 * Created: 4/9/2022 9:14:06 PM
 *  Author: Hassan
 */ 


#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 10000000UL

#define SS		4
#define MOSI	5
#define MISO	6
#define SCLK	7

void SPI_MasterInit(){
	DDRB |= ((1 << MOSI)|(1<<SS)|(1<<SCLK));
	
	SPCR |= ((1<< SPE)|(1<<MSTR)|(1<<SPR0));
}

uint8_t SPI_MasterSend(uint8_t data){
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}
int main(void)
{	
	SPI_MasterInit();
	DDRA = 0xFF;
	uint8_t dat;
	
    while(1)
    {
		for(dat = 0; dat< 256; dat++){
			_delay_ms(500);
			PORTA = SPI_MasterSend(dat);
		}	
		
	}
}