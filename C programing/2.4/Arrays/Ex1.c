/*
 * Ex1.c
 *
 *  Created on: Jan 18, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){

	float m1[2][2], m2[2][2];
	int i,j;

	printf("Enter elements of 1st matrix:\n");
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			printf("Enter a%d%d: ",i+1,j+1);
			fflush(stdin);fflush(stdout);
			scanf("%f",&m1[i][j]);
		}
	}

	printf("Enter elements of 2nd matrix:\n");
		for(i=0;i<2;i++){
			for(j=0;j<2;j++){
				printf("Enter b%d%d: ",i+1,j+1);
				fflush(stdin);fflush(stdout);
				scanf("%f",&m2[i][j]);
			}
		}

	printf("\nSum of Matrix:\n");
	for(i=0;i<2;i++){
			for(j=0;j<2;j++){
				printf("%.1f\t",m1[i][j]+m2[i][j]);
			}
			printf("\r\n");
		}
}
