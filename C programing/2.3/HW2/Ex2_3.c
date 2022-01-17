/*
 * Ex2_3.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){

	float a, b, c;
	printf("Enter three numbers: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%f %f %f",&a,&b,&c);

	if(a>b){
		if(a>c)
			printf("Largest number =%.2f",a);
		else
			printf("Largest number =%.2f",c);
	}

	else if(b>c)
		printf("Largest number =%.2f",b);

	else
		printf("Largest number =%.2f",c);

}
