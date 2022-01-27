/*
 * Ex4.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Hassan
 */

#include <stdio.h>

struct SStudent{
	char m_Name[50];
	int m_roll;
	int m_mark;
};

void Enter_data(struct SStudent arr[],int size){
	printf("Enter information of students:\n");
	int i;
	for(i=0;i<size;i++){
		arr[i].m_roll = i+1;
		printf("for roll number %d\n",arr[i].m_roll);
		printf("Enter name: ");
		fflush(stdin);fflush(stdout);
		scanf("%s",arr[i].m_Name);
		printf("Enter marks: ");
		fflush(stdin);fflush(stdout);
		scanf("%d",&arr[i].m_mark);
	}
}

void Display_data(struct SStudent arr[],int size){
	printf("displaying information\n");
	int i;
	for(i=0;i<size;i++){
		printf("Displaying information for roll number %d:\n",arr[i].m_roll);
		printf("Name: %s\n",arr[i].m_Name);
		printf("Marks: %d\n",arr[i].m_mark);
	}
}

int main(){
	struct SStudent students[10];

	Enter_data(students,3);

	Display_data(students,3);
	return 0;
}

