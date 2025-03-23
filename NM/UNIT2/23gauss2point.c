//Lab 23:WAP in C to integrate a given function using Gauss 2 point formula
#include<stdio.h>
#include<math.h>
#define F(x) (exp(x))
int main()
{
	float w1,w2,x1,x2,in;
	w1=1;
	w2=1;
	x1=-1/sqrt(3);
	x2=1/sqrt(3);
	in=w1*F(x1)+w2*F(x2);
	printf("Using Gaussian 2-point formula,\n I = %f",in);
	return 0;
}