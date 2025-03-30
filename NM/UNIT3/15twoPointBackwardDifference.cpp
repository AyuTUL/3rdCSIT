//Lab 15 : WAP in C that finds derivative of a function using 2 point backward difference formula
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define F(x) (1+sin(x))
int main()
{
	system("color f0");
	float f1,f2,h,xi,x1,d;
	printf("Enter the point at which 1st derivative is to be evaluated : ");
	scanf("%f",&xi);
	printf("Enter the value of h : ");
	scanf("%f",&h);
	x1=xi-h;
	f1=F(x1);
	f2=F(xi);
	d=(f2-f1)/h;
	printf("\nUsing 2-point backward difference formula,\n\tf'(%.2f)= %.5f ",xi,d);
	return 0;
}