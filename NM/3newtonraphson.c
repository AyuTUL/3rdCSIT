//Lab 3 : WAP to find a root of non linear equation using Secant method
#include<stdio.h>
#include<conio.h>
#include<math.h>
#define F(x) (x*x-x-1)
#define E 0.001
int main()
{
	float x1,x2,x3,f1,f2,f3,e;
	int i=1;
	printf("Enter 2 initial guesses x1 & x2 : ");
	scanf("%f%f",&x1,&x2);
	while(1)
	{
		f1=F(x1);
		f2=F(x2);
		x3=x2-f2*(x2-x1)/(f2-f1);
		e=fabs(x1-x2);
		printf("\nIteration %d  : \nx%d= %f\nError = %f\n",i,i+2,x3,e);
		getch();
		x1=x2;
		x2=x3;
		i++;
		if(e<E)
			break;		
	}
	printf("\nRoot = %f",x1);
}       