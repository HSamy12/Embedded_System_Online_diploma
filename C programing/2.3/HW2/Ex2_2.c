/*
 * Ex2_2.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){

	char a;
	printf("Enter an alphabet: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&a);

	if(a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u' || a == 'A' || a == 'E' || a == 'I' || a == 'O' || a == 'U')
		printf("%c is a vowel",a);
	else
		printf("%c is a consonant",a);
}
