/*
 * SPI_7Segment.c
 *
 * Created: 4/9/2022 11:42:21 PM
 *  Author: Hassan
 */ 

#define F_CPU 10000000UL

#include <avr/io.h>
#include <util/delay.h>



#define SS		4
#define MOSI	5
#define MISO	6
#define SCLK	7

void SPI_MasterInit(){
	DDRB |= ((1 << MOSI)|(1<<SS)|(1<<SCLK));
	
	SPCR |= ((1<< SPE)|(1<<MSTR)|(1<<SPR0));
}

void Transmit_7Seg(uint8_t cmd,uint8_t  data){
	PORTB &= ~(1<<SS);	//first make CS low before transmitting
	
	SPDR = cmd;		//send command
	while(!(SPSR & (1<<SPIF)));
	
	SPDR = data;	//send data
	while(!(SPSR & (1<<SPIF)));

	PORTB |= (1<<SS); //terminate the transmission by making CS high
}

void Sev_Seg_Init(){
	Transmit_7Seg(0x9,0xFF);	//decode for all 7 digits
	Transmit_7Seg(0xA,0x0F);	//Maximum intensity Mode
	Transmit_7Seg(0xB,0x07);	//Scan Limit set all digits 
	Transmit_7Seg(0xC,0x01);	//enable (Normal Operation)
}

int main(void)
{	uint8_t i,count=0;
	
	SPI_MasterInit();
	Sev_Seg_Init();
	
    while(1)
    {
        for (i=1;i<=8;i++,count++)
        {
			Transmit_7Seg(i,count);
			_delay_ms(50);
        }
    }
}