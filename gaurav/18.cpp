//lab 18: WAP to integrate a given function using trapezoidal rule
#include<stdio.h>
#include<conio.h>
#include<math.h>
#define F(x) (exp(-x)) 
trapezoidal(float x0,float x1)
{
	float f0,f1,i,h;
	h=(x1-x0);
	f0=F(x0);
	f1=F(x1);
	i=(f0+f1)*(h/2);
	printf("Integration:%f\n",i);
}

int main()
{
	float x0,x1;
	printf("Enter value of lower and uper limits:");
	scanf("%f%f",&x0,&x1);
	trapezoidal(x0,x1);
}
