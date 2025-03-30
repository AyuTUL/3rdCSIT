//Lab 28 : WAP in C that solves system of ODE’s by using Euler’s method
#include<stdio.h>
#include<math.h>
#define f1(x,y,z) (z)
#define f2(x,y,z) (exp(-x)-(y)-2*(z))
int main()
{
	float x,xp,x0,y0,z0,y,z,ny,nz,h;
	printf("Enter initial values of x, y & z : ");
	scanf("%f%f%f",&x0,&y0,&z0);
	printf("Enter the point at which function is to be evaluated : ");
	scanf("%f",&xp);
	printf("Enter step size : ");
	scanf("%f",&h);
	y=y0;
	x=x0;
	z=z0;
	printf("Using Euler's method,");
	for(x=x0;x<xp;x+=h)
	{
		ny=y+(f1(x,y,z))*h;
		nz=z+(f2(x,y,z))*h;
		y=ny;
		z=nz;
		printf("\n\ty(%.2f) = %.5f",x+h,y);
		printf("\n\tz(%.2f) = %.5f\n",x+h,z);
	}
	return 0;
}