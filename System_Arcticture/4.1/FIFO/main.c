/*
 * main.c
 *
 *  Created on: Feb 21, 2022
 *      Author: Hassan
 */


#include "fifo.h"

element_type buffer[6];
FIFO_buf_t uart_buffer;


int main(){

	int i;
	element_type temp;
	if(FIFO_init(&uart_buffer,buffer,6)==FIFO_no_error)
		printf("\nInitialized successfully\n");

	for(i=0;i<7;i++){
		printf("FIFO enqueue (%x) \n",i);
		if(FIFO_enqueue(&uart_buffer,i) == FIFO_no_error)
			printf("FIFO enqueue (%x) successful\n",i);
		else
			printf("FIFO enqueue (%x) failed\n",i);
	}
	FIFO_print(&uart_buffer);

	FIFO_dequeue(&uart_buffer,&temp);
	printf("\nFIFO dequeue Data = %X\n",temp);
	FIFO_dequeue(&uart_buffer,&temp);
	printf("\nFIFO dequeue Data = %X\n",temp);

	FIFO_print(&uart_buffer);

	for(i=0;i<2;i++){
		printf("FIFO enqueue (%x) \n",i);
		if(FIFO_enqueue(&uart_buffer,i) == FIFO_no_error)
			printf("FIFO enqueue (%x) successful\n",i);
		else
			printf("FIFO enqueue (%x) failed\n",i);
	}

	FIFO_print(&uart_buffer);
	return 0;
}
