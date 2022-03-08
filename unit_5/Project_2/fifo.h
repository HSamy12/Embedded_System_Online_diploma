/*
 * fifo.h
 *
 *  Created on: Mar 4, 2022
 *      Author: Hassan
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DPRINTF(...)	{fflush(stdout); fflush(stdin); \
						printf(__VA_ARGS__); \
						fflush(stdout); fflush(stdin); }

/* the struct of the student details */
typedef struct {
	char Fname[20];
	char Lname[20];
	int roll;
	float GPA;
	int cid[10];
}stu_t;

/* choosing the element type(char, short, int, long, etc)*/
#define element_type  stu_t


/* data types*/
typedef struct{
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
Buffer_status FIFO_check_state (FIFO_buf_t* fifo);
void print_FIFO(element_type* buffer);

#endif /* FIFO_H_ */
