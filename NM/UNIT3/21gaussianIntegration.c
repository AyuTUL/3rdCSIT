//Lab 21 : WAP in C that integrates given function using Gaussian integration formula
#include <stdio.h>
#include <math.h>
#define F(x) (sin(x)/x)
float transform(float t,float a,float b) 
{
    return((b-a)/2)*t+((a+b)/2);
}
float twoPoint(float a,float b) 
{
    float x1,x2,w1,w2,z1,z2,in,c;
	x1=-1/sqrt(3);
    x2=1/sqrt(3);
	w1=w2=1;
	c=(b-a)/2;
	z1=F(transform(x1,a,b));
	z2=F(transform(x2,a,b));
    in=c*(w1*z1+w2*z2);
    printf("\nUsing 2-point Gaussian integration formula,");
    return in;
}
float threePoint(float a,float b) 
{
    float x1,x2,x3,w1,w2,w3,z1,z2,z3,in,c;
	x1=-sqrt(3.0/5.0);
    x2=0.0;
    x3=sqrt(3.0/5.0);
    w1=5.0/9.0;
    w2=8.0/9.0;
    w3=5.0/9.0;
	c=(b-a)/2;
	z1=F(transform(x1,a,b));
	z2=F(transform(x2,a,b));
	z3=F(transform(x3,a,b));
    in=c*(w1*z1+w2*z2+w3*z3);
    printf("\nUsing 3-point Gaussian integration formula,");
    return in;
}
int main() 
{
    int n;
    float x0,xn,i;
	printf("Enter lower & upper limits : ");
    scanf("%f%f",&x0,&xn);
	printf("Enter number of points (2 or 3) : ");
    scanf("%d",&n);
	if(n==2)
        i=twoPoint(x0,xn);
    else if(n==3)
        i=threePoint(x0,xn);
    else 
	{
        printf("Invalid choice. Please enter 2 or 3.");
        return 1;
    }
    printf("\n\tI = %.5f",i);
    return 0;
}