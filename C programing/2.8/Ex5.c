/*
 * Ex5.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Hassan
 */

#include <stdio.h>

struct Semployee{
	char Name[50];
	unsigned int ID;
};

int main(){
	struct Semployee emp1 = {"Alex",1002},emp2= {"Brook",1003};
	struct Semployee*(ptr_arr[])={&emp1,&emp2};
	struct Semployee (*(*ptr)[2]);
	ptr = &ptr_arr;
	int i;
	for(i =0; i<2;i++){
		printf("Employee Name: %s\n",(*ptr)[i]->Name);
		printf("Employee ID: %d\r\n",(*ptr)[i]->ID);

	}
	return 0;
}

