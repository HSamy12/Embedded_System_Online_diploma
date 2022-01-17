/*
 * Ex2_6.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){

	unsigned int a;
	int i, Sum =0;
	printf("Enter an integer: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%u",&a);

	for (i=1;i<=a;i++){
		Sum+=i;
	}

	printf("Sum = %d",Sum);

}
