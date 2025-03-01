//lab 15: WAP TO FIND DERIVATIVE OF A FUNCTION USING TWO POINT BACKWARD DIFFERENCE FORMULA
#include<stdio.h>
#include<conio.h>
#define F(x) (x*x+6*x+2)
int main()
{
	float f1, f2, h, xi,x1,d;
	printf("enter point at which derivative to be computed:\n");
	scanf("%f",&xi);
	printf("enter value of h:\n");
	scanf("%f", &h);
	x1=xi-h;
	f1=F(x1);
	f2=F(xi);
	d=(f2-f1)/h;
	printf("derivate= %f ",d );
}