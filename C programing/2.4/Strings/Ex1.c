/*
 * Ex1.c
 *
 *  Created on: Jan 19, 2022
 *      Author: Hassan
 */

#include "stdio.h"
#include "string.h"

void main(){

	char ch, str[50];
	int i,n=0;
	printf("Enter a string: ");
	fflush(stdin);fflush(stdout);
	gets(str);

	printf("Enter a character to find frequency: ");
	fflush(stdin);fflush(stdout);
	scanf("%c",&ch);

	for(i=0;i<strlen(str);i++){
		if(ch==str[i])
			n++;
	}
	printf("frequency of %c = %d",ch,n);
}
