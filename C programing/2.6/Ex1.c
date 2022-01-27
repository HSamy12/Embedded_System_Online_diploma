/*
 * Ex1.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Hassan
 */

#include <stdio.h>

struct SStudent{
	char m_Name[50];
	int m_roll;
	float m_mark;
}s1;

int main(){
	printf("Enter information of students:\n");
	printf("Enter name: ");
	fflush(stdin);fflush(stdout);
	scanf("%s",s1.m_Name);

	printf("Enter roll number: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&s1.m_roll);

	printf("Enter marks: ");
	fflush(stdin);fflush(stdout);
	scanf("%f",&s1.m_mark);

	printf("displaying information\n");
	printf("Name: %s\n",s1.m_Name);
	printf("Roll: %d\n",s1.m_roll);
	printf("Marks: %.2f\n",s1.m_mark);

	return 0;
}

