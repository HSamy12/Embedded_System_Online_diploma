/*
 * Ex6.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){

	float a,b,temp;
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
	temp = a;
	a= b;
	b= temp;

	printf("After swapping value of a = %.2f\n",a);
	printf("After swapping value of b = %.2f\n",b);
}
