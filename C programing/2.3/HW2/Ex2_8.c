/*
 * Ex2_8.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Hassan
 */

#include "stdio.h"

void main(){

	char op;
	float n1, n2;
	printf(" enter operation either + or - or * or / : ");
	fflush(stdin);
	fflush(stdout);
	scanf("%c",&op);
	printf("enter  two operands : ");
	fflush(stdin);
	fflush(stdout);
	scanf("%f %f",&n1,&n2);

		switch(op){

			case '+' :
				printf("%.1f %c %.1f = %.1f",n1,op,n2,n1+n2);
				break;
			case '-' :
				printf("%.1f %c %.1f = %.1f",n1,op,n2,n1-n2);
				break;
			case '*' :
				printf("%.1f %c %.1f = %.1f",n1,op,n2,n1*n2);
				break;
			case '/' :
				printf("%.1f %c %.1f = %.1f",n1,op,n2,n1/n2);
				break;
			default  :
				printf("\nError Invalid Input Operation");
				break;
		}
}
