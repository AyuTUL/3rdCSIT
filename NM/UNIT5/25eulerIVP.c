//Lab 25 : WAP in C that solves initial value problem using Euler's method
#include<stdio.h>
#include<math.h>
#define f(x,y) (2*y/x)
int main()
{
	float x,xp,x0,y1,y,h,y0;
	printf("Enter initial values of x and y : ");
	scanf("%f%f",&x0,&y0);
	printf("Enter the point at which function is to be evaluated : ");
	scanf("%f",&xp);
	printf("Enter step size : ");
	scanf("%f",&h);
	y=y0;
	x=x0;
	printf("Using Euler's method,");
	for(x=x0;x<xp;x+=h)
	{
		y+=(f(x,y)*h);
		printf("\n\ty(%.2f) = %.5f",x+h,y);
	}
	return 0;	
}