/*
 * Student_LL.h
 *
 *  Created on: Feb 21, 2022
 *      Author: Hassan
 */

#ifndef STUDENT_LL_H_
#define STUDENT_LL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DPRINTF(...)	{fflush(stdout); fflush(stdin); \
						printf(__VA_ARGS__); \
						fflush(stdout); fflush(stdin); }

/*typedef of the data and links to be used*/
typedef struct{
	int ID;
	char Name[50];
	float height;
}SData;

typedef struct SSt{
	SData student;
	struct SSt * P_Next_Student;
}SStudent;


/*API functions*/
void fill_the_record(SStudent* n_student);
void Add_Student();
void Delete_Student();
void View_Students();
void Delete_ALL();
void Find_Student();
void Find_length();
void Reverse_List();
void Find_Middle();

#endif /* STUDENT_LL_H_ */
