/*
 * Ex2_5.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){

	char a;
	printf("Enter a character: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&a);

	if((a>=65 && a<=90)||(a>=97 && a<=122))
		printf("%c is an alphabet",a);

	else
		printf("%c is not an alphabet",a);

}
