/*
 * Ex3.c
 *
 *  Created on: Jan 19, 2022
 *      Author: Hassan
 */

#include "stdio.h"
#include "string.h"

void main(){

	char str[50],rev_str[50];
	int i,n=0;

	printf("Enter the string: ");
	fflush(stdin);fflush(stdout);
	gets(str);

	i=strlen(str);
	while(i>0){
		rev_str[n++]= str[--i];
	}

	rev_str[n]=0;
	printf("Reverse string is: %s",rev_str);
}
