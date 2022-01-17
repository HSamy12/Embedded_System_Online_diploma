/*
 * Ex2_7.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){

	int a, i, Sum =1;
	printf("Enter an integer: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&a);
	
	if(a<0)
		printf("Error!!! foactorial for negative doesn't exist");

	else{
		for (i=1;i<=a;i++){
			Sum*=i;
		}

		printf("Sum = %d",Sum);
	}
}
