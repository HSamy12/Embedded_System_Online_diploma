/*
 * Ex7.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){

	float a,b;
	//first value
	printf("Enter value of a: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%f",&a);
	//second value
	printf("Enter value of b: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%f",&b);
	//swapping operation
	a= a*b;
	b= a/b;
	a= a/b	;
	printf("After swapping value of a = %.2f\n",a);
	printf("After swapping value of b = %.2f\n",b);
}
