//Lab 22 : WAP in C that integrates given function using composite Simpson's 3/8 rule
#include<stdio.h>
#include<math.h>
#define F(x) (exp(x))
int main()
{
	float x0,xn,x,f0,fn,f,h,in;
	int n,i;
	printf("Enter lower & upper limits : ");
	scanf("%f%f",&x0,&xn);
	printf("Enter no. of segments in multiple of 3 : ");
	scanf("%d",&n);
	h=(xn-x0)/n;
	f0=F(x0);
	fn=F(xn);
	x=x0;
	for(i=1;i<n;i++)
	{
		x+=h;
		f=F(x);
		if(i%3==0)
			in+=2*f;
		else
			in+=3*f;
	}
	in=3*h*(in+f0+fn)/8;
	printf("Integrated value = %f",in);
	return 0;
}
