/*
 * Ex2.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Hassan
 */

#include <stdio.h>

int factorial(int);

int main(){

	int n;
	printf("Enter a positive integer: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);

	if(n<0)
		printf("no factorial for negative numbers");
	else
		printf("Factorial of %d = %d",n,factorial(n));
	return 0;
}

int factorial(int num){

	if(num<0)
		return 0;
	else if(num==0)
		return 1;
	else
		return num*factorial(num-1);
}
