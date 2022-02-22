/*
 * lifo.h
 *
 *  Created on: Feb 21, 2022
 *      Author: Hassan
 */

#ifndef LIFO_H_
#define LIFO_H_

#include <stdio.h>
#include <stdlib.h>

/* typedef of LIFO*/
typedef struct{
	unsigned int length;
	unsigned int count;
	unsigned char *base;
	unsigned char *head;

}LIFO_buf_t;


typedef enum{
	LIFO_no_error,	LIFO_full,	LIFO_empty,		LIFO_null
}Buffer_status;

/*API functions*/
Buffer_status LIFO_init(LIFO_buf_t* lifo ,unsigned char* buffer, unsigned int length);
Buffer_status LIFO_push(LIFO_buf_t* lifo , unsigned char item);
Buffer_status LIFO_pop(LIFO_buf_t* lifo , unsigned char *item);
Buffer_status LIFO_check_if_full(LIFO_buf_t* lifo);
Buffer_status LIFO_check_if_empty(LIFO_buf_t* lifo);

#endif /* LIFO_H_ */
