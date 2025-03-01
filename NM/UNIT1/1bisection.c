//Lab 1: WAP in C program that finds root of function f(x)=xe^x-1 using bisection method
#include<stdio.h>
#include<math.h>
#define E 0.001
#define F(x) (x*exp(x)-1)
int main()
{
	float x0,x1,x2,f0,f1,f2,e;
	int i=1;
	printf("Enter 2 initial guesses x1 & x2 : ");
	scanf("%f%f",&x1,&x2);
	f1=F(x1);
	f2=F(x2);
	if(f1*f2>0)
		printf("%f & %f do not bracket root",x1,x2);
	else
	{
		printf("-------------------------------------------------------------------------------------------------\n");
		printf("| %-9s | %-9s | %-9s | %-9s | %-9s | %-9s | %-9s | %-9s |\n","Iteration","x1","x2","x0","f(x1)","f(x2)","f(x0)","Error");
		printf("-------------------------------------------------------------------------------------------------\n");
		do
		{
			x0=(x1+x2)/2;
			f0=F(x0);
			e=fabs(x2-x1);
			printf("| %9d | %9f | %9f | %9f | %9f | %9f | %9f | %9f |\n",i,x1,x2,x0,f1,f2,f0,e);
			if(f0*f1<0)
			{
				x2=x0;
				f2=f0;
			}
			else
			{
				x1=x0;
				f1=f0;
			}
			i++;
		}while(e>=E);
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("\nRoot = %f",x0);
	}
	return 0;
}
