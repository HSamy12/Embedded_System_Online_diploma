/*
 * Ex3.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Hassan
 */

#include <stdio.h>


int main(){
	char str[50];
	char *ptr;
	ptr = str;
	int x;
	printf("Input a string:");
	fflush(stdin);fflush(stdout);
	scanf("%s",str);
	printf("you placed:");
	x= printf("%s",str);
	printf("\r\n");
	int i;
	ptr+= x;
	printf("reverse string:");
	for(i=x;i>=0;i--){
		printf("%c",*(ptr--));
	}
	return 0;
}

