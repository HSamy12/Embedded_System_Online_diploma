/*
 * Ex3.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Hassan
 */

#include <stdio.h>

struct Scomplex{
	float m_Real;
	float m_Img;
};

struct Scomplex Add_Complex(struct Scomplex d1,struct Scomplex d2){
	struct Scomplex Res;
	Res.m_Real =d1.m_Real + d2.m_Real;
	Res.m_Img =d1.m_Img + d2.m_Img;
	return Res;
}

int main(){
	struct Scomplex c1,c2,r;

	printf("Enter Real and imaginary respectively:");
	fflush(stdin);fflush(stdout);
	scanf("%f %f",&c1.m_Real,&c1.m_Img);

	printf("Enter Real and imaginary respectively:");
	fflush(stdin);fflush(stdout);
	scanf("%f %f",&c2.m_Real,&c2.m_Img);

	r = Add_Complex(c1,c2);
	printf("Sum = %.2f + %.2fi",r.m_Real,r.m_Img);

	return 0;
}

