//Lab 3 : WAP to find a root of non linear equation using Secant method
#include<stdio.h>
#include<math.h>
#define F(x) (x*x-4*x-10)
#define E 0.001
int main()
{
	float x1,x2,x3,f1,f2,e;
	int i=1;
	printf("Enter 2 initial guesses x1 & x2 : ");
	scanf("%f%f",&x1,&x2);
	printf("--------------------------------------------------------------------------------------\n");
	printf("| %-9s | %-9s | %-9s | %-10s | %-9s | %-9s | %-9s |\n","Iteration","x_{i-1}","x_i","f(x_{i-1})","f(x_i)","x_{i+1}","Error");
	printf("--------------------------------------------------------------------------------------\n");
	do
	{
		f1=F(x1);
		f2=F(x2);
		x3=x2-f2*(x2-x1)/(f2-f1);
		e=fabs(x3-x2);
		printf("| %9d | %9.5f | %9.5f | %10.5f | %9.5f | %9.5f | %9.5f |\n",i,x1,x2,f1,f2,x3,e);
		x1=x2;
		x2=x3;
		i++;		
	}while(e>=E);
	printf("--------------------------------------------------------------------------------------\n");
	printf("Root = %.5f",x3);
	return 0;
}       