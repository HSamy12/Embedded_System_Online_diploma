/*****************************************
*	file  		: startup.c
*	author		: Hassan Samy
*	description : performs the start 
*		mechanism for the board until 
*		reaching main function.
*****************************************/

#include "Plat_type.h"

#define SP_top 0x020001000

extern uint32 _S_DATA;
extern uint32 _E_DATA;
extern uint32 _S_bss;
extern uint32 _E_bss;
extern uint32 _E_text;

extern int main(void);
void Reset_Handler(void);

void Default_Handler()
{
	Reset_Handler();
}

void NMI_Handler(void) __attribute__((weak,alias("Default_Handler")));
void H_fault_Handler(void) __attribute__((weak,alias("Default_Handler")));
void MM_fault_Handler(void) __attribute__((weak,alias("Default_Handler")));
void Bus_fault_Handler(void) __attribute__((weak,alias("Default_Handler")));
void Usage_fault_Handler(void) __attribute__((weak,alias("Default_Handler")));

uint32 vectors[]__attribute__((section(".vectors"))) ={
	SP_top,
	(uint32)&Reset_Handler,
	(uint32)&NMI_Handler,
	(uint32)&H_fault_Handler,
	(uint32)&MM_fault_Handler,
	(uint32)&Bus_fault_Handler,
	(uint32)&Usage_fault_Handler
};

void Reset_Handler(void){	/* copy the .data from ROM to RAM*/
	uint32 DATA_Size =(uint8*)&_E_DATA - (uint8*)&_S_DATA ;
	uint8 *P_src =(uint8*)&_E_text;
	uint8 *P_dst =(uint8*)&_S_DATA;
	
	uint32 i;
	for(i=0; i<DATA_Size;i++){
		*((uint8*)P_dst++) = *((uint8*)P_src++);
	}
	/* init the .bss with 0 in RAM */
	uint32 bss_size = (uint8*)&_E_bss - (uint8*)&_S_bss ;
	P_dst =(uint8*)&_E_bss;
	for(i=0; i<bss_size;i++){
		*((uint8*)P_dst++) = (uint8)0;
	}
	
	main();
}
