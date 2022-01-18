/*
 * Ex4.c
 *
 *  Created on: Jan 18, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){

	int arr[10], t[10];
	int i,n,x,loc;

	printf("Enter no of elements: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);

//getting the matrix
	for(i=0;i<n;i++){
			fflush(stdin);fflush(stdout);
			scanf("%d",&arr[i]);
	}

	printf("Enter the element to be inserted: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&x);

	printf("Enter the location: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&loc);
	loc =loc-1;

//shifting after
	for(i=loc;i<=n;i++){
		t[i+1]=arr[i];
	}
//placing the element
	t[loc]=x;
//placing before element
	for(i=0;i<loc;i++){
		t[i]=arr[i];
	}
//printing new array
	for(i=0;i<=n;i++){
		printf("%d ",t[i]);
	}
}
