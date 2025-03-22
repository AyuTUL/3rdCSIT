//Lab 15-wap to find derivative of a function using two point backward difference formula

#include<stdio.h>
#include<conio.h>
#define F(x)(x*x+6*x+2)
int main()
{
	float f1,f2,h,xi,x1,d;
	printf("enter point at which derivative to be computed\n");
	scanf("%f",&xi);
	printf("enter value of h\n");
	scanf("%f",&h);
	x1 =xi-h;
	f1 =F(xi);
	f2 =F(x1);
	d =(f1-f2)/h;
	printf("Derivative =%f\n",d)
;
return 0;}
