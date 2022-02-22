/*
 * fifo.c
 *
 *  Created on: Feb 21, 2022
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

/* check if the fifo is full or not*/
Buffer_status FIFO_check_if_full (FIFO_buf_t* fifo){

	if(!fifo->head || !fifo->base || !fifo->tail) //check if fifo exists
		return FIFO_null;

	else if(fifo->count >= fifo->length ){ //check if it's full
		printf("the queue is full \n");
		return FIFO_full;
	}
	else
		return FIFO_no_error;
}

/* Adding a new element*/
Buffer_status FIFO_enqueue (FIFO_buf_t* fifo ,element_type data ){

	if(FIFO_check_if_full (fifo)== FIFO_no_error){// checks if valid for enqueue
		*(fifo->head) = data;
		fifo->count++;

		if(fifo->head == (fifo->base + fifo->length *sizeof(element_type) )) // circular queue reached its end
			fifo->head = fifo->base;
		else
			fifo->head++;
		return FIFO_no_error;
	}
	else
		return FIFO_check_if_full (fifo);
}

/* check if the fifo is empty*/
Buffer_status FIFO_check_if_empty (FIFO_buf_t* fifo){

	if(!fifo->head || !fifo->base || !fifo->tail) //check if fifo exists
		return FIFO_null;

	else if(fifo->count == 0 ){ //check if it's empty
		printf("the queue is empty \n");
		return FIFO_empty;
	}
	else
		return FIFO_no_error;
}

/* dequeue of an element*/
Buffer_status FIFO_dequeue (FIFO_buf_t* fifo ,element_type* ptr_data){
	if(FIFO_check_if_empty (fifo) == FIFO_no_error){// checks if valid for dequeue
		*ptr_data = *(fifo->tail);
		fifo->count--;

		if(fifo->tail == (fifo->base + fifo->length *sizeof(element_type) ))
			fifo->tail = fifo->base;
		else
			fifo->tail++;

		return FIFO_no_error;
	}
	else
		return FIFO_check_if_empty (fifo);
}

/*print all element of the queue*/
void FIFO_print(FIFO_buf_t* fifo){
	if(FIFO_check_if_empty (fifo) == FIFO_no_error){ // checks if empty
		element_type *temp;
		temp = (fifo->tail);
		int i;
		printf("\n====== Printing data ========\n");
		for(i=0; i < fifo->count ; i++){
			printf("\t %X \n",*temp);
			temp++;
		}
		printf("=============================\n");

	}
}

