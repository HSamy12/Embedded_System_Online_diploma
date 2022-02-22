/*
 * lifo.c
 *
 *  Created on: Feb 21, 2022
 *      Author: Hassan
 */


#include "lifo.h"


/* Initialize the stack buffer*/
Buffer_status LIFO_init(LIFO_buf_t* lifo ,unsigned char* buffer, unsigned int length){
	if(!lifo->head || !lifo->base) //the check if lifo buffer exist or not
		return LIFO_null;
	else{
		lifo->base = buffer;
		lifo->length = length;
		lifo->head = lifo->base;
		lifo->count =0;
		return LIFO_no_error;
	}
}

/* check if stack full */
Buffer_status LIFO_check_if_full(LIFO_buf_t* lifo){
	if(!lifo->head || !lifo->base) //the check if lifo buffer exist or not
		return LIFO_null;
	else if(lifo->head >=(lifo->base + lifo->length)) // the check for full
		return LIFO_full;
	else
		return LIFO_no_error;
}

/* push item to this stack */
Buffer_status LIFO_push(LIFO_buf_t* lifo , unsigned char item){
	if(LIFO_check_if_full(lifo) == LIFO_no_error){
		*(lifo->head)=item;
		lifo->head++;
		lifo->count++;
		return LIFO_no_error;
	}
	else
		return LIFO_check_if_full(lifo);
}

/* check if stack empty */
Buffer_status LIFO_check_if_empty(LIFO_buf_t* lifo){
	if(!lifo->head || !lifo->base) //the check if lifo buffer exist or not
		return LIFO_null;
	else if(lifo->head == lifo->base ) // the check for empty
		return LIFO_empty;
	else
		return LIFO_no_error;
}

/* pop item from stack */
Buffer_status LIFO_pop(LIFO_buf_t* lifo , unsigned char *item){
	if(LIFO_check_if_empty(lifo) == LIFO_no_error){

		lifo->head--;
		lifo->count--;
		*item=*(lifo->head);

		return LIFO_no_error;
	}
	else
		return LIFO_check_if_empty(lifo);
}

