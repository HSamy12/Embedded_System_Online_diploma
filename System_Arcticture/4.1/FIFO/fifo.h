/*
 * fifo.h
 *
 *  Created on: Feb 21, 2022
 *      Author: Hassan
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <stdio.h>

/* choosing the element type(char, short, int, long, etc)*/
#define element_type unsigned int

/* data types*/
typedef struct
{
	unsigned int length;
	unsigned int count;
	element_type *base;
	element_type *tail;
	element_type *head;
}FIFO_buf_t;

typedef enum{
	FIFO_no_error,	FIFO_full,	FIFO_empty,		FIFO_null
}Buffer_status;

/* API functions*/
Buffer_status FIFO_init(FIFO_buf_t* fifo ,element_type* buffer ,unsigned int length);
Buffer_status FIFO_enqueue (FIFO_buf_t* fifo ,element_type data );
Buffer_status FIFO_dequeue (FIFO_buf_t* fifo ,element_type* ptr_data);
Buffer_status FIFO_check_if_full (FIFO_buf_t* fifo);
Buffer_status FIFO_check_if_empty (FIFO_buf_t* fifo);
void FIFO_print(FIFO_buf_t* fifo);

#endif /* FIFO_H_ */
