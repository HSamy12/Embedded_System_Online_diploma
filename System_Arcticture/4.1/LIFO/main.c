/*
 * main.c
 *
 *  Created on: Feb 21, 2022
 *      Author: Hassan
 */

#include "lifo.h"

#define buffer_length 5

int main(){
	unsigned char Static_buffer[buffer_length];
	unsigned char *Dynamic_buffer = (unsigned char*)malloc(buffer_length);
	unsigned char i,temp;
	LIFO_buf_t S_buff , D_buff;

	//Initializing dynamic buffer
	LIFO_init(&D_buff, Dynamic_buffer,buffer_length);

	//pushing to lifo
	printf("\n LIFO Dynamic push items =");
	for(i=0;i<buffer_length;i++){
		printf(" %d,",i);
		LIFO_push(&D_buff , i);
	}

	//poping from lifo
	printf("\n LIFO Dynamic poped items =");
	for(i=0;i<buffer_length;i++){
		LIFO_pop(&D_buff , &temp);
		printf(" %d,",temp);
	}

	//Initializing Static buffer
	LIFO_init(&S_buff, Static_buffer,buffer_length);

	//pushing to lifo
	printf("\n LIFO Static push items =");
	for(i=0;i<buffer_length;i++){
		printf(" %d,",i);
		LIFO_push(&S_buff , i);
	}

	//poping from lifo
	printf("\n LIFO Static poped items =");
	for(i=0;i<buffer_length;i++){
		LIFO_pop(&S_buff , &temp);
		printf(" %d,",temp);
	}

	return 0;
}
