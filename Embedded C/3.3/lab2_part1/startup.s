/**************************************
*	file  		: startup.s
*	author		: Hassan Samy
*	description : performs the start 
*		mechanism for the board until 
*		reaching main function.
**************************************/

.section .vectors
.word 0x20001000		/* stack top address */
.word _reset			/* 1 Reset */
.word vector_handler	/* 2 NMI */
.word vector_handler	/* 3 Hard Fault */
.word vector_handler	/* 4 MM Fault */
.word vector_handler	/* 5 Bus Fault */
.word vector_handler	/* 6 Usage Fault */
.word vector_handler	/* 7 RESEVERD */
.word vector_handler	/* 8 RESEVERD */
.word vector_handler	/* 9 RESEVERD */
.word vector_handler	/* 10 RESEVERD */
.word vector_handler	/* 11 SV call */
.word vector_handler	/* 12 Debug reserved */
.word vector_handler	/* 13 RESEVERD */
.word vector_handler	/* 14 PendSV */
.word vector_handler	/* 15 SysTick */
.word vector_handler	/* 16 IRQ0 ...*/



.section .text
_reset:
	bl main
	b  .
.thumb_func
vector_handler:
	b _reset