/*
 * lcd.c
 *
 *  Created on: Mar 26, 2022
 *      Author: Hassan
 */
#include "../Inc/lcd.h"

GPIO_PinConfig_t PinCfg;

void wait_ms(uint32_t time){
	volatile uint32_t i,j;
	for(i=0;i<time;i++)
		for(j=0;j<255;j++);
}

void LCD_lcd_kick(){
	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_SET);
	wait_ms(50);
	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET);
}

void LCD_clear_screen(){
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}


void LCD_GOTO_XY(unsigned char line, unsigned char position){
	if (line == 1)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
		}
	}
	if (line == 2)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
		}
	}
}

void LCD_INIT(){

	wait_ms(20);

	// configuring EN_SWITCH,RS_SWITCH and RW_SWITCH as floating input
	PinCfg.GPIO_PinNumber = RS_SWITCH;
	PinCfg.GPIO_MODE = GPIO_MODE_Out_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = RW_SWITCH;
	PinCfg.GPIO_MODE = GPIO_MODE_Out_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = EN_SWITCH;
	PinCfg.GPIO_MODE = GPIO_MODE_Out_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	// configuring DATA  pins 0:7 as output Push-Pull
	PinCfg.GPIO_PinNumber = GPIO_Pin_0;
	PinCfg.GPIO_MODE = GPIO_MODE_Out_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_Pin_1;
	PinCfg.GPIO_MODE = GPIO_MODE_Out_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_Pin_2;
	PinCfg.GPIO_MODE = GPIO_MODE_Out_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_Pin_3;
	PinCfg.GPIO_MODE = GPIO_MODE_Out_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_Pin_4;
	PinCfg.GPIO_MODE = GPIO_MODE_Out_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_Pin_5;
	PinCfg.GPIO_MODE = GPIO_MODE_Out_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_Pin_6;
	PinCfg.GPIO_MODE = GPIO_MODE_Out_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_Pin_7;
	PinCfg.GPIO_MODE = GPIO_MODE_Out_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);

	wait_ms(15);
	LCD_clear_screen();

	#ifdef EIGHT_BIT_MODE
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	#endif
	#ifdef FOUR_BIT_MODE
		//LCD_WRITE_COMMAND(0x02);		/* send for 4 bit initialization of LCD  */
		//LCD_WRITE_COMMAND(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
		//LCD_WRITE_COMMAND(0x0c);              /* Display on cursor off*/
		//LCD_WRITE_COMMAND(0x06);              /* Increment cursor (shift cursor to right)*/
		//LCD_WRITE_COMMAND(0x01);
	LCD_WRITE_COMMAND(0x02);
	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	#endif

	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);	
}

void LCD_check_lcd_isbusy(){

	PinCfg.GPIO_PinNumber = GPIO_Pin_0;
	PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_Pin_1;
	PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_Pin_2;
	PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_Pin_3;
	PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_Pin_4;
	PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_Pin_5;
	PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_Pin_6;
	PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_Pin_7;
	PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);


	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	LCD_lcd_kick();
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	
}


void LCD_WRITE_COMMAND(unsigned char command){
	#ifdef EIGHT_BIT_MODE
//		LCD_check_lcd_isbusy();
		MCAL_GPIO_WritePort(LCD_CTRL, command);

		MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
		MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);

		wait_ms(1);
		LCD_lcd_kick();
	#endif
	#ifdef FOUR_BIT_MODE
		LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
		LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
		LCD_lcd_kick ();
		LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
		LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
		LCD_lcd_kick();
	#endif
}

void LCD_WRITE_CHAR(unsigned char character){
	#ifdef EIGHT_BIT_MODE
//		LCD_check_lcd_isbusy();
		MCAL_GPIO_WritePort(LCD_PORT, character);

		MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
		MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);

		wait_ms(1);
		LCD_lcd_kick();
	#endif
	#ifdef FOUR_BIT_MODE
		LCD_check_lcd_isbusy();
		LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
		LCD_CTRL |= 1<<RS_SWITCH; //turn RS ON for Data mode.
		LCD_CTRL &= ~ (1<<RW_SWITCH);//turn RW off so you can write.
		LCD_lcd_kick();
		LCD_PORT = (LCD_PORT & 0x0F) | (character << 4);
		LCD_CTRL |= 1<<RS_SWITCH; //turn RS ON for Data mode.
		LCD_CTRL &= ~ (1<<RW_SWITCH);//turn RW off so you can write.
		LCD_lcd_kick ();
	#endif
}

void LCD_WRITE_STRING(char* string){
	int count = 0;
	while (*string > 0){
		count++;
		LCD_WRITE_CHAR(*string++);
		if (count == 16)
		{
			LCD_GOTO_XY(2,0);
		}
		else if (count == 32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);
			count = 0;
		}
	}
}
