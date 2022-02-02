/*
 * Ex1.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Hassan
 */

#include <stdio.h>


int main(){
	int m = 29;
	printf("address of m =%p\n",&m);
	printf("value of m =%d\r\n",m);

	int* ab;
	ab =&m;
	printf("Now ab is assigned with the address of m.\n");
	printf("address of pointer ab =%p\n",ab);
	printf("content of pointer ab =%d\r\n",*ab);

	m=34;
	printf("The value of m assigned to %d now.\n",m);
	printf("address of pointer ab =%p\n",ab);
	printf("content of pointer ab =%d\r\n",*ab);

	*ab =7;
	printf("The pointer variable ab is assigned with the value %d now.\n",*ab);
	printf("address of m =%p\n",&m);
	printf("value of m =%d\r\n",m);
	return 0;
}

