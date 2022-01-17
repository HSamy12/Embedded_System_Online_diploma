/*
 * Ex2_4.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){

	float a;
	printf("Enter a number: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%f",&a);

	if(a>0){
		printf("%.2f is positive",a);
	}
	else if(a==0){
		printf("You entered zero");
	}
	else{
		printf("%.2f is negative",a);
	}
}
