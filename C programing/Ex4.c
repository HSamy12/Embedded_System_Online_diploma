/*
 * Ex4.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){
	float Num1,Num2;
	printf("Enter two numbers: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%f %f",&Num1,&Num2);
	printf("Product= %f",Num1*Num2);
}
