/*
 * Ex4.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Hassan
 */

#include <stdio.h>


int main(){
	int arr[15];
	int *ptr;
	ptr = arr;
	int x;
	printf("Input the number of elements to store in the array (max 15) :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&x);

	int i;

	for(i=0;i<x;i++){
		printf("element - %d:",i+1);
		fflush(stdin);fflush(stdout);
		scanf("%d",&arr[i]);
	}

	ptr+= x;
	printf("\nelements of array in reverse order are:\n");
	for(i=x;i>0;i--){

		printf("element - %d :%d\n",i,*(--ptr));
	}
	return 0;
}

