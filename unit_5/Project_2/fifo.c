/*
 * fifo.c
 *
 *  Created on: Mar 4, 2022
 *      Author: Hassan
 */

#include "fifo.h"

/* initializing the queue buffer*/
Buffer_status FIFO_init(FIFO_buf_t* fifo ,element_type* buffer ,unsigned int buf_length){
	fifo->base = buffer;
	fifo->head = fifo->base;
	fifo->tail = fifo->base;
	fifo->length =buf_length;
	fifo->count = 0;
	if ( fifo->base && fifo->length )
		return FIFO_no_error;
	else
		return FIFO_null;
}

/* check the fifo state */
Buffer_status FIFO_check_state (FIFO_buf_t* fifo){

	if(!fifo->head || !fifo->base || !fifo->tail) //check if fifo exists
		return FIFO_null;

	else if(fifo->count >= fifo->length ) //check if it's full
		return FIFO_full;

	else if(fifo->count == 0 ) //check if it's empty
		return FIFO_empty;

	else
		return FIFO_no_error;
}


/* print an element */
void print_FIFO(element_type* data){
	int i;
	DPRINTF("\n=======PRINTING STUDENT=======\n");
	DPRINTF("\n Student Roll Number: %d",data->roll);
	DPRINTF("\n Student First Name: %s",data->Fname);
	DPRINTF("\n Student Last Name: %s",data->Lname);
	DPRINTF("\n Student GPA: %.2f",data->GPA);
	DPRINTF("\n Student Courses ID: ");

	for(i=0;i<5;i++)
		DPRINTF("\n Course %d ID :%d",i+1 ,data->cid[i]);

	DPRINTF("\n==============================\n");
}
