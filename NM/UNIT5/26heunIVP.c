//Lab 26 : WAP in C that solves initial value problem using Heun's method
#include<stdio.h>
#define f(x,y) ((x)*(x)+(y)*(y))
int main()
{
	float x,xp,x0,y0,y,h,m1,m2;
	printf("Enter initial values of x and y : ");
	scanf("%f%f",&x0,&y0);
	printf("Enter the point at which function is to be evaluated : ");
	scanf("%f",&xp);
	printf("Enter step size : ");
	scanf("%f",&h);
	y=y0;
	x=x0;
	printf("Using Heun's method,");
	for(x=x0;x<xp;x+=h)
	{
		m1=f(x,y);
		m2=f(x+h,y+h*m1);
		y+=(h/2*(m1+m2));
		printf("\n\ty(%.2f) = %.5f",x+h,y);
	}
	return 0;
}