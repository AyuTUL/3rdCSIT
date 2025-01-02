//Lab 2 : WAP to find a root of non linear equation using Newton Raphson method
#include<stdio.h>
#include<conio.h>
#include<math.h>
#define F(x) (x*x-x-1)
#define D(x) (2*x-1)
#define E 0.001
int main()
{
	float x1,x2,f0,f1,e;
	int i=1;
	printf("Enter initial guess x1 : ");
	scanf("%f",&x1);
	while(1)
	{
		f0=F(x1);
		f1=D(x1);
		if(f1==0)
			printf("Method can't continue because of divide  by 0 error.");
		else
		{
			x2=x1-f0/f1;
			e=fabs(x1-x2);
			x1=x2;
			printf("\nIteration %d  : \nx%d= %f\nError = %f\n",i,i+1,x1,e);
			getch();
			i++;
			if(e<E)
				break;		
		}
	}
	printf("\nRoot = %f",x1);
}       