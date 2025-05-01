//Lab 27 : WAP in C that solves initial value problem using Runge Kutta method
#include<stdio.h>
#define f(x,y) ((x)/(y))
int main()
{
	float x,xp,x0,y0,y,h,m1,m2,m3,m4;
	printf("Enter initial values of x and y : ");
	scanf("%f%f",&x0,&y0);
	printf("Enter the point at which function is to be evaluated : ");
	scanf("%f",&xp);
	printf("Enter step size : ");
	scanf("%f",&h);
	y=y0;
	x=x0;
	printf("Using Runge Kutta method,");
	for(x=x0;x<xp;x+=h)
	{
		m1=f(x,y);
		m2=f(x+h/2.0,y+h*m1/2.0);
		m3=f(x+h/2.0,y+h*m2/2.0);
		m4=f(x+h,y+h*m3);
		y+=((m1+2*(m2+m3)+m4)*h/6.0);
		printf("\n\tm1 = %.5f\n\tm2 = %.5f\n\tm3 = %.5f\n\tm4 = %.5f\n\ty(%.2f) = %.5f\n",m1,m2,m3,m4,x+h,y);
	}
	return 0;
}
