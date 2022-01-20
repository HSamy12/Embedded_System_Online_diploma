/*
 * Ex3.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Hassan
 */

#include <stdio.h>
#include <string.h>

void Rev_Sentence(char*);


int main(){

	char s[50];
	printf("Enter a sentence: ");
	fflush(stdin);fflush(stdout);
	gets(s);
	Rev_Sentence(s);
	return 0;
}

void Rev_Sentence(char str[]){
	int i=strlen(str),j=0;
	char rev_str[50];
	while(i>0){
		rev_str[j++]= str[--i];
	}
	rev_str[j]=0;
	printf("%s",rev_str);
}
