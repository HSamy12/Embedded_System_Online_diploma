/*
 * Ex2.c
 *
 *  Created on: Jan 19, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){

	char str[50];
	int i;
	printf("Enter a string: ");
	fflush(stdin);fflush(stdout);
	gets(str);



	for(i=0;i<50;i++){
		if(str[i]==0)
			break;
	}

	printf("\nLength of string = %d",i);
}
