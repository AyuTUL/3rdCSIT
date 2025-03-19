//Lab 21 : WAP in C that integrates given function using basic Simpson's 3/8 rule
#include<stdio.h>
#include<math.h>
#define F(x) (exp(x))
int main()
{
	float x0,x1,x2,x3,x,f0,f1,f2,f3,h,i;
	printf("Enter lower & upper limits : ");
	scanf("%f%f",&x0,&x3);
	h=(x3-x0)/3;
	x1=x0+h;
	x2=x0+2*h;
	f0=F(x0);
	f1=F(x1);
	f2=F(x2);
	f3=F(x3);
	i=3*h*(f0+3*f1+3*f2+f3)/8;
	printf("Integrated value = %f",i);
	return 0;
}
