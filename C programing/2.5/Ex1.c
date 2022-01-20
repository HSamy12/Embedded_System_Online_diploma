/*
 * Ex1.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Hassan
 */

#include <stdio.h>

void PrimeFind(int,int);

int main(){

	int start,end;
	printf("Enter Two numbers(intervals): ");
	fflush(stdin);fflush(stdout);
	scanf("%d %d",&start,&end);
	PrimeFind(start,end);
	return 0;
}

void PrimeFind(int s, int e){
	int i,j;
	printf("Prime numbers between %d and %d are: ",s,e);
	int not_prime =0;
	for(i=s;i<=e;i++){

		for(j=2;j<i;j++){

			if(i%j == 0 ){
				not_prime =1;
				break;
			}
		}
		if(not_prime == 0)
			printf("%d ",i);
		else
			not_prime =0;
	}
}
