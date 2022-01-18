/*
 * Ex3.c
 *
 *  Created on: Jan 18, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){

	int m[5][5], t[5][5];
	int i,j,c,r;
//getting the matrix dimentions
	printf("Enter rows and columns of matrix: ");
	fflush(stdin);fflush(stdout);
	scanf("%d %d",&r,&c);
//getting the matrix
	printf("\nEnter elements of matrix:\n");
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			printf("Enter a%d%d: ",i+1,j+1);
			fflush(stdin);fflush(stdout);
			scanf("%d",&m[i][j]);
		}
	}
//making the transpose
	for(i=0;i<c;i++){
		for(j=0;j<r;j++){
			t[i][j]=m[j][i];
		}
	}
//printing
	printf("\nEntered matrix:\n");
		for(i=0;i<r;i++){
			for(j=0;j<c;j++){
				printf("%d\t",m[i][j]);
			}
			printf("\n");
		}
	printf("\nTranspose of matrix:\n");
		for(i=0;i<c;i++){
			for(j=0;j<r;j++){
				printf("%d\t",t[i][j]);
			}
			printf("\n");
		}
}
