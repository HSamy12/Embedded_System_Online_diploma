/*
 * Ex5.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){
	char c;
	printf("Enter a character: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&c);
	printf("ASCII value of %c = %d",c,c);
}
