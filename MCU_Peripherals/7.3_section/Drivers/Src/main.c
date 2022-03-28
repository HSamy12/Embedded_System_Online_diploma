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
#include "lcd.h"
#include  "keypad.h"

void clk_init(){
	//Enable clk for GPIOA
	RCC_GPIOA_CLK_EN();
	//Enable clk for GPIOB
	RCC_GPIOB_CLK_EN();
}

void GPIO_init(){
	GPIO_PinConfig_t PinCfg;

	// configuring pin A1 as floating input
	PinCfg.GPIO_PinNumber = GPIO_Pin_1;
	PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	// configuring pin B1 as Push Pull output
	PinCfg.GPIO_PinNumber = GPIO_Pin_1;
	PinCfg.GPIO_MODE = GPIO_MODE_Out_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	// configuring pin A13 as floating input
	PinCfg.GPIO_PinNumber = GPIO_Pin_13;
	PinCfg.GPIO_MODE = GPIO_MODE_In_FLO;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	// configuring pin B13 as Push Pull output
	PinCfg.GPIO_PinNumber = GPIO_Pin_13;
	PinCfg.GPIO_MODE = GPIO_MODE_Out_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Speed_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);
}

//void wait_ms(uint32_t time){
//	volatile uint32_t i,j;
//	for(i=0;i<time;i++)
//		for(j=0;j<255;j++);
//}

int main(void)
{	 // initialization
	unsigned char key_pressed;
	clk_init();
	LCD_INIT();
	Keypad_init();

	// use key pad
	LCD_WRITE_STRING("Hello My Friend");
	wait_ms(5);
	LCD_clear_screen();

    /* Loop forever */
	while(1){
			key_pressed = Keypad_getkey();
			switch(key_pressed){
			case 'A':
				break;
			case '?':
				LCD_clear_screen();
				break;
			default:
				LCD_WRITE_CHAR(key_pressed);
				break;
			}

	}
}

