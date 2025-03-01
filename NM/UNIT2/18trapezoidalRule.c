//Lab18 : WAP in C to integrate a given functionusing Trapezoidal rule
#include<stdio.h>
#include<math.h>
#define F(x) (exp(-x))
float basicTrapezoidal(float x0,float x1)
{
	float h,f0,f1,i;
	h=x1-x0;
	f0=F(x0);
	f1=F(x1);
	i=(f0+f1)*h/2;
	return i;
}
float compTrapezoidal(float x0,float x1,int n)
{
	float h,f0,fn,xi;
	int i;
	h=x1-x0;
	f0=F(x0);
	fn=F(xn);
	for(i=1;i<n-1;i++)
	{
		xi=x0+i*h;
		f=F(xi);
		sum=sum+2*f;
	}
	i=(f0+sum+fn)*h/2;
	return i;
}

int main()
{
	int n;
	float x0,x1,i;
	printf("Enter lower & upper limit : ");
	scanf("%f%f",&x0,&x1);
	printf("Enter no. of segments  : ");
	scanf("%d",&n);
	if(n==1)
		i=basicTrapezoidal(x0,x1);
	else
		i=compTrapezoidal(x0,x1,n);
	printf("Integrated value = %f",trapezoid(x0,x1));
   }   