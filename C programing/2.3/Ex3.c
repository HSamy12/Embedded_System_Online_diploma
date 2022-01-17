/*
 * Ex3.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){
	int Num1,Num2;
	printf("Enter two integers: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d %d",&Num1,&Num2);
	printf("Sum= %d",Num1+Num2);
}
