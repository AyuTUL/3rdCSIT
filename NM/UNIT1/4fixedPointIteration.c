//Lab 4 : WAP in C that finds a root of non-linear equation x*e^x-1=0 using fixed point iteration method
#include<stdio.h>
#include<math.h>
#define F(x) (x*exp(x)-1)
#define G(x) (1/exp(x))
#define E 0.001
int main()
{
	float x0,x1,f0,e;
	int i=1;
	printf("Enter initial guess x0 : ");
	scanf("%f",&x0);
	printf("-------------------------------------------------\n");
	printf("| %-9s | %-9s | %-9s | %-9s |\n","Iteration","x","g(x)","Error");
	printf("-------------------------------------------------\n");
	do
	{
		x1=G(x0);
		e=fabs(x1-x0);
		printf("| %9d | %9.5f | %9.5f | %9.5f |\n",i,x0,x1,e);
		x0=x1;
		i++;
	}while(e>=E);
	printf("-------------------------------------------------\n");
	printf("Root = %.5f",x1);
	return 0;
}	       
