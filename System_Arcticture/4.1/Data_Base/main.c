/*
 * Student_LL.c,main.c
 *
 *  Created on: Feb 21, 2022
 *      Author: Hassan
 */


#include "Student_LL.h"



int main(){
	char temp_text[10];
	while(1){
		DPRINTF("\nchoose one of the following:\n");
		DPRINTF("1: Add a Student\n");
		DPRINTF("2: Delete a Student\n");
		DPRINTF("3: View All Students\n");
		DPRINTF("4: Delete All Students\n");
		DPRINTF("5: Find a Student\n");
		DPRINTF("6: Find length of list\n");
		DPRINTF("7: Find middle Student\n");
		DPRINTF("8: Reverse list\n");

		DPRINTF("Your choice :");
		gets(temp_text);
		DPRINTF("\n======================\n");

		switch(atoi(temp_text)){
		case 1:
			Add_Student();
			break;
		case 2:
			Delete_Student();
			break;
		case 3:
			View_Students();
			break;
		case 4:
			Delete_ALL();
			break;
		case 5:
			Find_Student();
			break;
		case 6:
			Find_length();
			break;
		case 7:
			Find_Middle();
			break;
		case 8:
			Reverse_List();
			break;
		default:
			DPRINTF("Wrong option \n");
			break;
		}

	}

	return 0;
}
