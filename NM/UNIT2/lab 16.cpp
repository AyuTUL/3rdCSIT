//lab 15: WAP TO FIND DERIVATIVE OF A FUNCTION USING Three POINT BACKWARD DIFFERENCE FORMULA
#include<stdio.h>
#include<conio.h>
#define F(x) (3*x*x+10*x+1)
int main()
{
	float f1, f2, h, xi,x1,d,x2;
	printf("enter point at which derivative to be computed\n");
	scanf("%f",&xi);
	printf("enter value of h /n");
	scanf("%f", &h);
	x1=xi+h;
	x2=xi-h;
	f1=F(x1);
	f2=F(x2);
	d=(f1-f2)/(2*h);
	printf("derivate= %f ",d );
}