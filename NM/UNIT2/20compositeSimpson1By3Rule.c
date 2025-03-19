//Lab 20 : WAP in C that integrates given function using composite Simpson's 1/3 rule
#include<stdio.h>
#include<math.h>
#define F(x) (exp(x))
int main()
{
	float x0,xn,x,f0,fn,f,h,in;
	int n,i;
	printf("Enter lower & upper limits : ");
	scanf("%f%f",&x0,&xn);
	printf("Enter no. of segments : ");
	scanf("%d",&n);
	h=(xn-x0)/n;
	f0=F(x0);
	fn=F(xn);
	x=x0;
	for(i=1;i<n;i++)
	{
		x+=h;
		f=F(x);
		if(i%2==1)
			in+=4*f;
		else
			in+=2*f;
	}
	in=h*(in+f0+fn)/3;
	printf("Integrated value = %f",in);
	return 0;
}
