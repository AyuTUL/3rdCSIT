//Lab 16 : WAP in C that finds derivative of a function using 3 point formula
#include<stdio.h>
#define F(x) (3*x*x+10*x+1)
int main()
{
	float f1,f2,h,xi,x1,x2,d;
	printf("Enter the point at which derivative is to be evaluated : ");
	scanf("%f",&xi);
	printf("Enter the value of h : ");
	scanf("%f",&h);
	x1=xi+h;
	x2=xi-h;
	f1=F(x1);
	f2=F(x2);
	d=(f1-f2)/(2*h);
	printf("\nUsing 3-point formula,\n\tf'(%.2f)= %.5f ",xi,d);
	return 0;
}