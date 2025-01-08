//lab 4: WAP to find a root of non-linear equation x*e^x-1=0 using fixed point iteration method
#include<stdio.h>
#include<conio.h>
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
	while(1)
	{
		x1=G(x0);
		e=fabs(x1-x0);
		printf("\nIteration %d  : \nx%d= %f\nError = %f\n",i,i,x1,e);
		getch();
		if(e<E)
			break;
		x0=x1;
		i++;
	}
	printf("\nRoot = %f",x1);
	return 0;
}	       