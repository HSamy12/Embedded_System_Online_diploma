/*
 * Ex2_1.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){

	int a;
	printf("Enter an integer you want to check: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&a);

	if(a%2 == 0)
		printf("%d is even",a);
	else
		printf("%d is odd",a);
}
