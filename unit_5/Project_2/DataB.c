/*
 * DataB.c
 *
 *  Created on: Mar 4, 2022
 *      Author: Hassan
 */

#include "DataB.h"


/* function to add new student manually */
void add_student_manually(FIFO_buf_t* fifo){

	element_type* data = fifo->head;

	if(FIFO_check_state (fifo)== FIFO_no_error || FIFO_check_state (fifo)== FIFO_empty){// checks if valid for enqueue
		char temp[50];
		int i;
		DPRINTF("Enter Student roll number:");
		gets(temp);
		while(check_roll(fifo , atoi(temp))!=NULL){ //while roll number is already used
			DPRINTF("[ERROR]: roll number already exists\n");
			DPRINTF("Enter new Student roll number:");
			gets(temp);
		}
		data->roll = atoi(temp);

		DPRINTF("Enter Student First Name:");
		gets(data->Fname);

		DPRINTF("Enter Student Last Name:");
		gets(data->Lname);

		DPRINTF("Enter Student GPA:");
		gets(temp);
		data->GPA = atof(temp);

		for(i=0;i<5;i++){
			DPRINTF("Enter Student Course ID:");
			gets(temp);
			data->cid[i] = atoi(temp);

		}
		fifo->count++;

		if(fifo->head == (fifo->base + fifo->length *sizeof(element_type) )) // circular queue reached its end
			fifo->head = fifo->base;
		else
			fifo->head++;

		DPRINTF("[INFO]: Student Details are added successfully \n");
		tot_s(fifo);
	}
	else
		DPRINTF("[INFO]: Student Details failed to be added\n");

}

/* function to check existence of roll number */
element_type* check_roll(FIFO_buf_t* fifo ,int Selected_Roll){
	element_type* pCurrent = fifo->base;
	int i;

	if(FIFO_check_state(fifo)==FIFO_null){
		DPRINTF("[ERROR]: Database not exist  \n");
		return NULL;
	}
	//if the list is valid
	else{
		for(i=0;i<fifo->count;i++)   // loop to get the Roll number
		{
			if(pCurrent->roll==Selected_Roll){
				return pCurrent;
			}
			pCurrent++;
		}
		return NULL;
	}
}

/* function to find student by roll number */
void find_rl(FIFO_buf_t* fifo){
	element_type* pCurrent = fifo->base;
	int Selected_Roll;
	if (FIFO_check_state(fifo)==FIFO_null){
		DPRINTF("[ERROR]: Database doesn't exist \n");
	}
	else if (FIFO_check_state(fifo)==FIFO_empty){
		DPRINTF("[ERROR]: Database is empty \n");
	}
	else{
		DPRINTF("Enter student roll number:");
		scanf("%d",&Selected_Roll);

		pCurrent=check_roll(fifo,Selected_Roll);
		if(pCurrent!=NULL)	//check if roll exist
			print_FIFO(pCurrent);

		else
			DPRINTF("[ERROR]: Roll Number is Not Found\n");	//roll not found
	}
}

/* function to find student by name */
void find_fn(FIFO_buf_t* fifo){
	element_type* pCurrent = fifo->base;
	int i,f=0;
	char Selected_Name[20];

	if (FIFO_check_state(fifo)==FIFO_null){
		DPRINTF("[ERROR]: Database doesn't exist \n");
	}
	else if (FIFO_check_state(fifo)==FIFO_empty){
		DPRINTF("[ERROR]: Database is empty \n");
	}
	else{
		DPRINTF("Enter student First Name:");
		gets(Selected_Name);

		for(i=0;i<fifo->count;i++){	//loop to find name
			if(strcmpi(Selected_Name,pCurrent->Fname)==0){
				f=1;
				print_FIFO(pCurrent);
			}
			pCurrent++;
		}
	}
	if(f==0)		// loop finished and name not found
		DPRINTF("[ERROR]: First Name not found\n");
}

/* function to find students in a course  */
void find_c(FIFO_buf_t* fifo){
	element_type* pCurrent = fifo->base;
	int i,n,course,f=0;

	if (FIFO_check_state(fifo)==FIFO_null){
		DPRINTF("[ERROR]: Database doesn't exist \n");
	}
	else if (FIFO_check_state(fifo)==FIFO_empty){
		DPRINTF("[ERROR]: Database is empty \n");
	}
	else{
		DPRINTF("Enter course ID:");
		scanf("%d",&course);
		for(i=0;i<fifo->count;i++){   // loop to get registered student in this Course ID
			for(n=0;n<=5;n++){
				if(pCurrent->cid[n]==course){
					print_FIFO(pCurrent);
					f=1;
				}
			}
			pCurrent++;
		}
		if(f==0)
			DPRINTF("[ERROR]: No Student signed this Course\n");// loop finished and no student found
	}
}

/* function tells data about students  */
void tot_s(FIFO_buf_t* fifo){
	// check the list of students
	if(FIFO_check_state(fifo)==FIFO_null){
		DPRINTF("[ERROR] Database not exist  \n");
	}
	else if (FIFO_check_state(fifo)==FIFO_empty){
		DPRINTF("[ERROR] Database is empty \n");
	}
	else{
		DPRINTF("\n====================================\n");
		DPRINTF("[INFO]: the total number of students is : %d\n",fifo->count);
		DPRINTF("[INFO]: you can add up to %d students \n",fifo->length);
		DPRINTF("[INFO]: you can add %d more students \n",fifo->length - fifo->count);
		DPRINTF("\n========================================\n");
	}
}

/* function prints all students */
void show_s(FIFO_buf_t* fifo)
{
	int i,count = 0;
	element_type* pCurrent = fifo->base;
	//check if list is exit and not empty
	if(FIFO_check_state(fifo)==FIFO_null){
		DPRINTF("[ERROR] Database not exist  \n");
		return;
	}
	if (FIFO_check_state(fifo)==FIFO_empty){
		DPRINTF("[ERROR] Database is empty \n");
		return;
	}
	for(i=0;i< fifo->count;i++)
	{
		DPRINTF("\n Record Number %d>", count+1);
		print_FIFO(pCurrent);
		pCurrent++;
		count++;
	}
}

/* function  deletes student */
void del_s(FIFO_buf_t* fifo,element_type* buffer){
	element_type* pCurrent = fifo->base;
	int Selected_Roll;
	int i,n,f=0;
	if (FIFO_check_state(fifo)==FIFO_null){
		DPRINTF("[ERROR]: Database doesn't exist \n");
	}
	else if (FIFO_check_state(fifo)==FIFO_empty){
		DPRINTF("[ERROR]: Database is empty \n");
	}
	else{
		DPRINTF("Enter student roll number:");
		scanf("%d",&Selected_Roll);
		pCurrent = check_roll(fifo,Selected_Roll);
		n = (int)(fifo->base - pCurrent);
		if(pCurrent!= NULL){	//check if roll exist
			f=1;
			for(i=n;i<fifo->count;i++)
				buffer[i]=buffer[i+1];	//move rest backwards 1 step

			fifo->head--;
			fifo->count--;
			DPRINTF("[INFO]: Roll Number deleted\n");
		}
	}

	if(f==0)
		DPRINTF("[ERROR]: Roll Number is Not Found\n");	//roll not found

}

/* function  updates student */
void up_s(FIFO_buf_t* fifo){
	element_type* pCurrent = fifo->base;
	char temp[50];
	int Selected_Roll;
	int i,f=0;
	DPRINTF("\n Enter Student Roll to be Updated: ");
	scanf("%d",&Selected_Roll);

	pCurrent = check_roll(fifo,Selected_Roll);
	if(pCurrent!= NULL){	//check if roll exist
		f=1;
		print_FIFO(pCurrent);
		DPRINTF("=================================\n");
		DPRINTF("1- First Name\n");
		DPRINTF("2- Last Name \n");
		DPRINTF("3- Roll Number\n");
		DPRINTF("4- GPA\n");
		DPRINTF("5- Courses \n");
		DPRINTF("=================================\n");
		DPRINTF("Enter Data Number to be Updated:");
		gets(temp);

		switch(atoi(temp)){
		case 1:
			DPRINTF("Enter New first Name:");
			gets(pCurrent->Fname);
			break;
		case 2 :
			DPRINTF("Enter New Last Name:");
			gets(pCurrent->Lname);
			break;
		case 3 :
			DPRINTF("Enter New Roll Number:");
			gets(temp);
			pCurrent->roll=atoi(temp);
			break;
		case 4 :
			DPRINTF("Enter New GPA:");
			gets(temp);
			pCurrent->GPA=atof(temp);
			break;
		case 5 :
			DPRINTF("Enter the course id of each course\n");
			for(i=1;i<=5;i++){
				DPRINTF("Course %d ID :",i);
				gets(temp);
				pCurrent->cid[i]=atoi(temp);
			}
			break;
		default :
			DPRINTF("[ERROR]: wrong choice \n");
			return;
		}
		DPRINTF("[INFO]: student updated successfully \n");
		DPRINTF("Student information after update \n");
		print_FIFO(pCurrent);
	}
	if(f==0)
		DPRINTF("[ERROR]: Roll Number is Not Found\n");// loop finished and roll not found;
}


/* function to add new student from file*/
void add_student_file(FIFO_buf_t* fifo){
	char FName[50], LName[50];
	int RollNum, CID[5], line =1;
	float GPA;
	if(FIFO_check_state (fifo)== FIFO_no_error || FIFO_check_state (fifo)== FIFO_empty){// checks if valid for enqueue
		FILE *file;
		int i;
		file = fopen("data.txt","r");
		while (EOF != fscanf(file, "%d %s %s %f %d %d %d %d %d\n",
				&RollNum,FName,LName,&GPA,CID,CID+1,CID+2,CID+3 ,CID+4)){
			if(check_roll(fifo,RollNum)!=NULL){
				DPRINTF("[ERROR]:Roll Number %d is already reserved\n",RollNum);
				line++;
				continue; // Skip This Student
			}
			fifo->head->roll = RollNum;
			strcpy(fifo->head->Fname, FName);
			strcpy(fifo->head->Lname, LName);
			fifo->head->GPA = GPA;
			for(i=0;i<5;i++)
				fifo->head->cid[i]=CID[i];

			fifo->count++;
			fifo->head++;
			DPRINTF("[INFO]:Roll Number %d saved successfully\n",RollNum);
		}
		tot_s(fifo);
	}
	else
		DPRINTF("[INFO]: Student Details failed to be added\n");

}
