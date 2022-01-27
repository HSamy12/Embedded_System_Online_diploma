/*
 * Ex2.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Hassan
 */

#include <stdio.h>

struct Sdistance{
	int m_feet;
	float m_inch;
};

struct Sdistance Add_F_I(struct Sdistance d1,struct Sdistance d2){
	struct Sdistance Res;
	Res.m_feet =d1.m_feet + d2.m_feet;
	Res.m_inch =d1.m_inch + d2.m_inch;
	if(Res.m_inch>=12){
		Res.m_inch-=12;
		Res.m_feet+=1;
	}
	return Res;
}

int main(){
	struct Sdistance d1,d2,r;

	printf("Enter information for 1st distance:\n");
	printf("Enter feet: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&d1.m_feet);
	printf("Enter inch: ");
	fflush(stdin);fflush(stdout);
	scanf("%f",&d1.m_inch);

	printf("Enter information for 2nd distance:\n");
	printf("Enter feet: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&d2.m_feet);
	printf("Enter inch: ");
	fflush(stdin);fflush(stdout);
	scanf("%f",&d2.m_inch);

	r = Add_F_I(d1,d2);
	printf("Sum of distances = %d' %.2f\"",r.m_feet,r.m_inch);

	return 0;
}

