//Lab 18 : WAP in C that integrates given function using Trapezoidal rule
#include<stdio.h>
#include<math.h>
#define F(x) (x*x*x+2)
float basicTrapezoidal(float x0,float x1)
{
	float h,f0,f1,in;
	h=x1-x0;
	f0=F(x0);
	f1=F(x1);
	in=(f0+f1)*h/2;
	printf("\nUsing basic trapezoidal rule,");
	return in;
}
float compTrapezoidal(float x0,float xn,int n)
{
	float h,f,f0,fn,xi,sum=0.0,in;
	int i;
	h=(xn-x0)/n;
	f0=F(x0);
	fn=F(xn);
	for(i=1;i<n;i++)
	{
		xi=x0+i*h;
		f=F(xi);
		sum+=(2*f);
	}
	in=(f0+sum+fn)*h/2;
	printf("\nUsing composite trapezoidal rule,");
	return in;
}
int main()
{
	int n;
	float x0,xn,i;
	printf("Enter lower & upper limits : ");
	scanf("%f%f",&x0,&xn);
	printf("Enter no. of segments : ");
	scanf("%d",&n);
	if(n==1)
		i=basicTrapezoidal(x0,xn);
	else
		i=compTrapezoidal(x0,xn,n);
	printf("\n\tI = %.5f",i);
	return 0;
}   