/*
 * Ex4.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Hassan
 */

#include <stdio.h>

int power(int,int);

int main(){

	int num, pow;
	printf("Enter base number: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&num);
	printf("Enter power number(positive integer): ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&pow);
	if(pow<0)
		printf("please enter positive integer");
	else
		printf("%d^%d = %d",num,pow,power(num,pow));
	return 0;
}

int power(int n,int p){
	if(p==0)
		return 1;
	else
		return n*power(n,p-1);
}
