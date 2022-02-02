/*
 * Ex2.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Hassan
 */

#include <stdio.h>


int main(){
	char alpha[27]={'A'};
	char *p;
	p = alpha;

	int i=0;
	for(i=1;i<26;i++)
		alpha[i]=alpha[i-1]+1;

	for(i=0;i<26;i++)
		printf("%c ",*(p++));

	return 0;
}

