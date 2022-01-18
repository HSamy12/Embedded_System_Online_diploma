/*
 * Ex2.c
 *
 *  Created on: Jan 18, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){

	float arr[10];
	int i,n;
	float Sum =0;

	printf("Enter number of data: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);
	for(i=0;i<n;i++){
		printf("%d. Enter a number:",i+1);
		fflush(stdin);fflush(stdout);
		scanf("%f",&arr[i]);
		Sum+=arr[i];
	}

	printf("Average = %.2f",Sum/n);
}
