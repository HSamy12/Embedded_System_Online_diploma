/*
 * Ex5.c
 *
 *  Created on: Jan 18, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){

	int arr[10];
	int i,n,Search;

	printf("Enter no of elements: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);

//getting the matrix
	for(i=0;i<n;i++){
			fflush(stdin);fflush(stdout);
			scanf("%d",&arr[i]);
	}

	printf("Enter the element to be searched: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&Search);

	for(i=0;i<n;i++){
		if(arr[i]==Search){
			printf("Number found at location = %d",i+1);
			break;
		}
	}
	if(i==n)
		printf("the number cannot be found");
}
