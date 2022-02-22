/*
 * Student_LL.c
 *
 *  Created on: Feb 21, 2022
 *      Author: Hassan
 */


#include "Student_LL.h"

/* the head ptr for first link*/
 SStudent* gpFirstStudent= NULL;

/* function for filling the data */
void fill_the_record(SStudent* n_student){
	char temp_text[10];

	DPRINTF("Enter Student ID:");
	gets(temp_text);
	n_student->student.ID = atoi(temp_text);

	DPRINTF("Enter Student Name:");
	gets(n_student->student.Name);

	DPRINTF("Enter Student height:");
	gets(temp_text);
	n_student->student.height = atof(temp_text);
}

/* function to add a new student */
void Add_Student(){
	SStudent* P_Last_St;
	SStudent* P_New_St;

	if (gpFirstStudent == NULL){	//if list empty
		P_New_St = (SStudent*)malloc(sizeof(SStudent));	// create node
		gpFirstStudent = P_New_St;	// point to first node
	}
	else{
		P_Last_St = gpFirstStudent; 		// start from the first node
		while(P_Last_St->P_Next_Student)	//searching till you find last node
			P_Last_St = P_Last_St->P_Next_Student;

		P_New_St = (SStudent*)malloc(sizeof(SStudent)); //create new node
		P_Last_St->P_Next_Student=P_New_St ;		// link old last node to it
		}

	fill_the_record(P_New_St);
	P_New_St->P_Next_Student =NULL;
}

/* function to delete certain node */
void Delete_Student(){
	char temp_text[10];
	int selected_ID;

	DPRINTF("Enter ID to be deleted:");
	gets(temp_text);
	selected_ID = atoi(temp_text);

	if(gpFirstStudent){
		SStudent* P_Prev_Stu = NULL;
		SStudent* P_Select_Stu = gpFirstStudent;

		while(P_Select_Stu){	//loop on all nodes

			if(P_Select_Stu->student.ID == selected_ID){	//  find ID similar to this

				if(P_Prev_Stu)
					P_Prev_Stu->P_Next_Student = P_Select_Stu->P_Next_Student;
				else
					gpFirstStudent = P_Select_Stu->P_Next_Student;

				free(P_Select_Stu);
			}
			P_Prev_Stu = P_Select_Stu;
			P_Select_Stu = P_Select_Stu->P_Next_Student;
		}
	}
	else{
	DPRINTF("Failed to find ID: %d",selected_ID);
	}
}

/* function viewing all records */
void View_Students(){
	int count;
	SStudent * P_Current_Stu = gpFirstStudent;
	if(gpFirstStudent == NULL)
		DPRINTF("\n==============List is empty=============\n");

	while(P_Current_Stu){
		DPRINTF("record number %d\n",count+1);
		DPRINTF("ID: %d\n",P_Current_Stu->student.ID);
		DPRINTF("Name: %s\n",P_Current_Stu->student.Name);
		DPRINTF("Height: %.2f\n",P_Current_Stu->student.height);
		DPRINTF("\n======================\n");

		P_Current_Stu=P_Current_Stu->P_Next_Student;
		count++;
	}
}

/* function to delete all records */
void Delete_ALL(){
	SStudent * P_Current_Stu = gpFirstStudent;
	if(gpFirstStudent == NULL)
		DPRINTF("\n==============List is empty=============\n");

	while(P_Current_Stu){
		SStudent* temp_ptr = P_Current_Stu;
		P_Current_Stu=P_Current_Stu->P_Next_Student;
		free(temp_ptr);
	}
	gpFirstStudent = NULL;
}

/* function to find certain node and prints it */
void Find_Student(){
	char temp_text[10];
	int index, count = 0;

	DPRINTF("Enter index:");
	gets(temp_text);
	index = atoi(temp_text);

	if(gpFirstStudent){
		SStudent* P_Select_Stu = gpFirstStudent;

		for(count = 0;count<index;count++){	//loop till reach the index
				P_Select_Stu=P_Select_Stu->P_Next_Student;

		}
		if(count == index){	// print its data
			DPRINTF("the index =%d\n",count);
			DPRINTF("ID: %d\n",P_Select_Stu->student.ID);
			DPRINTF("Name: %s\n",P_Select_Stu->student.Name);
			DPRINTF("Height: %.2f\n",P_Select_Stu->student.height);
			DPRINTF("\n======================\n");
		}
	}
	else{
	DPRINTF("Failed to find index: %d",index);
	}
}

/* function finds the number of nodes in linked list */
void Find_length(){
	int count=0;
	SStudent * P_Current_Stu = gpFirstStudent;
	while(P_Current_Stu){
		P_Current_Stu=P_Current_Stu->P_Next_Student;
		count++;
	}
	DPRINTF("number of nodes in list = %d\n",count);

}

/* function to find middle student */
void Find_Middle(){
	SStudent * P_Fast_Stu = gpFirstStudent;
	SStudent * P_Slow_Stu = gpFirstStudent;

	while(P_Fast_Stu != NULL){
		P_Fast_Stu = P_Fast_Stu->P_Next_Student;
		if(P_Fast_Stu == NULL)
			break;
		P_Slow_Stu = P_Slow_Stu->P_Next_Student;
		P_Fast_Stu = P_Fast_Stu->P_Next_Student;
	}
	DPRINTF("ID: %d\n",P_Slow_Stu->student.ID);
	DPRINTF("Name: %s\n",P_Slow_Stu->student.Name);
	DPRINTF("Height: %.2f\n",P_Slow_Stu->student.height);
	DPRINTF("\n======================\n");

}

/* function to reverse the list*/
void Reverse_List(){
	SStudent * P_Current_Stu = gpFirstStudent;
	SStudent * P_Prev_Stu = NULL;
	SStudent * P_Next_Stu;

	while(P_Current_Stu != NULL){
		P_Next_Stu = P_Current_Stu->P_Next_Student;
		P_Current_Stu->P_Next_Student = P_Prev_Stu;
		P_Prev_Stu = P_Current_Stu;
		P_Current_Stu =	P_Next_Stu;
	}
	gpFirstStudent = P_Prev_Stu;
}

