//Lab 19 : WAP in C that integrates given function using Simpson's 1/3 rule
#include<stdio.h>
#include<math.h>
#define F(x) (exp(-x/2))
float basicSimpson(float x0,float x2)
{
	float x1,f0,f1,f2,h,in;
	h=(x2-x0)/2;
	x1=x0+h;
	f0=F(x0);
	f1=F(x1);
	f2=F(x2);
	in=h*(f0+4*f1+f2)/3;
	printf("\nUsing basic Simpson's 1/3 rule,");
	return in;
}
float compSimpson(float x0,float xn,int n)
{
	float h,f,f0,fn,xi,sum=0.0,in;
	int i;
	if(n%2==1) 
	{
		n+=1;
        printf("\nSimpson's 1/3 rule requires an even number of segments.\nAdjusting n to %d.\n",n);
    }
	h=(xn-x0)/n;
	f0=F(x0);
	fn=F(xn);
	for(i=1;i<n;i++)
	{
		xi=x0+i*h;
        if(i%2==1)
            sum+=4*F(xi);
        else
            sum+=2*F(xi);
    }
    in=(h/3)*(f0+sum+fn);
	printf("\nUsing composite Simpson's 1/3 rule,");
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
	if(n==2)
		i=basicSimpson(x0,xn);
	else
		i=compSimpson(x0,xn,n);
	printf("\n\tI = %.5f",i);
	return 0;
} 