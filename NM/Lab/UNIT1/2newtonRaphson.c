//Lab 2 : WAP to find a root of non linear equation using Newton Raphson method
#include<stdio.h>
#include<conio.h>
#include<math.h>
#define F(x) (pow(x,3)-5*x+3)
#define D(x) (3*x*x-5)
#define E 0.001
int main()
{
	float x1,x2,f1,f2,e;
	int i=1;
	printf("Enter initial guess x1 : ");
	scanf("%f",&x1);
	printf("-------------------------------------------------------------------------\n");
	printf("| %-9s | %-9s | %-9s | %-9s | %-9s | %-9s |\n","Iteration","x_n","f(x_n)","f'(x_n)","x_{n+1}","Error");
	printf("-------------------------------------------------------------------------\n");
	do
	{
		f1=F(x1);
		f2=D(x1);
		if(f1==0)
			printf("Method can't continue because of divide by 0 error.");
		else
		{
			x2=x1-f1/f2;
			e=fabs(x2-x1);
			printf("| %9d | %9f | %9f | %9f | %9f | %9f |\n",i,x1,f1,f2,x2,e);
			x1=x2;
			i++;	
		}
	}while(e>=E);
	printf("-------------------------------------------------------------------------\n");
	printf("\nRoot = %f",x1);
	return 0;
}       
