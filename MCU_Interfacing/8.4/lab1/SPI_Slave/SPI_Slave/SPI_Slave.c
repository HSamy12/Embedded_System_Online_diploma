/*
 * SPI_Slave.c
 *
 * Created: 4/9/2022 10:26:22 PM
 *  Author: Hassan
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 10000000UL

#define SS		4
#define MOSI	5
#define MISO	6
#define SCLK	7

void SPI_SlaveInit(){
	DDRB |= (1 << MISO);
	DDRB &= ~(1 << MOSI) & ~(1 << SS) & ~(1 << SCLK);
	SPCR = (1<< SPE);
}

uint8_t SPI_SlaveRecive(uint8_t data){
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}
int main(void)
{
	SPI_SlaveInit();
	DDRA = 0xFF;
	uint8_t dat;
	
	while(1)
	{
		for(dat = 255; dat>0; dat-- ){
			PORTA = SPI_SlaveRecive(dat);
		}
		
	}
}