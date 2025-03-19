//Lab 19 : WAP in C that integrates given function using basic Simpson's 1/3 rule
#include<stdio.h>
#include<math.h>
#define F(x) (exp(x))
int main()
{
	float x0,x1,x2,f0,f1,f2,h,i;
	printf("Enter lower & upper limits : ");
	scanf("%f%f",&x0,&x2);
	h=(x2-x0)/2;
	x1=x0+h;
	f0=F(x0);
	f1=F(x1);
	f2=F(x2);
	i=h*(f0+4*f1+f2)/3;
	printf("Integrated value = %f",i);
	return 0;
}
