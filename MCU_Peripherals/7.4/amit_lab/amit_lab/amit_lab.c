/*
 * amit_lab.c
 *
 * Created: 3/30/2022 6:17:53 PM
 *  Author: Hassan
 */ 

#include "AVRMemoryMap.h"
#include "Lcd/lcd.h"
#include "Keypad/keypad.h"


int main(void)
{	
	LCD_INIT();
	LCD_WRITE_STRING("Eng. Hassan Samy");
	_delay_ms(1000);
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
    while(1)
    {
        //TODO:: Please write your application code 
    }
}