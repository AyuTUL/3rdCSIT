//Lab 1: WAP in C program that finds root of function f(x)=xe^x-1 using bisection method
#include<stdio.h>
#include<math.h>
#include<conio.h>
#define E 0.001
#define F(x) (x*x-x-1)
int main()
{
	float x0,x1,x2,f0,f1,f2,e;
	int i=1;
	printf("Enter 2 initial guesses x1 & x2 : ");
	scanf("%f%f",&x1,&x2);
	f1=F(x1);
	f2=F(x2);
	if(f1*f2>0)
		printf("%f & %f do not bracket root",f1,f2);
	else
	{
		while(1)
		{
			f1=F(x1);
			f2=F(x2);
			x0=(x1+x2)/2;
			f0=F(x0);
			e=fabs(x0-x1);
			printf("\nIteration %d  : \nx0= %f\nError = %f\n",i,x0,e);
			getch();
			if(f0*f1<0)
			{
				x2=x0;
				x1=x1;
			}
			else
			{
				x1=x0;
				x2=x2;
			}
			i++;
			if(e<E)
				break;
		}
		printf("\nRoot = %f",x0);
	}
}