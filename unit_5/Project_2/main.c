/*
 * main.c
 *
 *  Created on: Mar 4, 2022
 *      Author: Hassan
 */

#include "DataB.h"

stu_t st[50];
FIFO_buf_t St_queue ;


int main(){
	FIFO_init(&St_queue,st,50); // Initializing the buffer with 50 elements
	int choice;
	while(1){
		DPRINTF("\n===============================\n");
		DPRINTF("1.Add new Student manually\n");
		DPRINTF("2.Add new Student from file\n");
		DPRINTF("3.Find Student by roll number\n");
		DPRINTF("4.Find Student by First Name\n");
		DPRINTF("5.Find Students in certain course\n");
		DPRINTF("6.Show queue data\n");
		DPRINTF("7.Show all students\n");
		DPRINTF("8.Delete student\n");
		DPRINTF("9.Update Student\n");
		DPRINTF("10. Exit program\n");
		DPRINTF("\n===============================\n");
		DPRINTF("Enter your choice:");
		scanf("%d",&choice);
		switch(choice){
		case 1:
			add_student_manually(&St_queue);
			break;
		case 2:
			add_student_file(&St_queue);
			break;
		case 3:
			find_rl(&St_queue);
			break;
		case 4:
			find_fn(&St_queue);
			break;
		case 5:
			find_c(&St_queue);
			break;
		case 6:
			tot_s(&St_queue);
			break;
		case 7:
			show_s(&St_queue);
			break;
		case 8:
			del_s(&St_queue,st);
			break;
		case 9:
			up_s(&St_queue);
			break;
		case 10:
			exit(1);
			break;
		default:
			DPRINTF("Enter valid choice\n");
			break;
		}
	}

	return 0;
}
