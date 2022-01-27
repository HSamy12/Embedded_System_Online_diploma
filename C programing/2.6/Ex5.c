/*
 * Ex5.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Hassan
 */

#include <stdio.h>

#define pi (3.14)

int main(){
	float r;
	printf("Enter the radius: ");
	fflush(stdout);
	scanf("%f",&r);

	printf("Area = %.2f",pi*r*r);

	return 0;
}

