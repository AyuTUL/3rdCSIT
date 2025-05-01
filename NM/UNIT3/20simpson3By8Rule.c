//Lab 20 : WAP in C that integrates given function using Simpson's 3/8 rule
#include<stdio.h>
#include<math.h>
#define F(x) (exp(x)/x)
float basicSimpson(float x0,float x3)
{
	float x1,x2,f0,f1,f2,f3,h,in;
    h=(x3-x0)/3;
    x1=x0+h;
    x2=x0+2*h;
    f0=F(x0);
    f1=F(x1);
    f2=F(x2);
    f3=F(x3);
    in=(3*h/8)*(f0+3*(f1+f2)+f3);
    printf("\nUsing basic Simpson's 3/8 rule,");
    return in;
}
float compSimpson(float x0,float xn,int n)
{
	float h,f0,fn,xi,sum=0.0,in;
    int i;
    if(n%3!=0) 
	{
		n+=(3-n%3);
        printf("\nSimpson's 3/8 rule requires the no. of segments to be a multiple of 3.\nAdjusting n to %d.\n",n); 
    }
    h=(xn-x0)/n;
    f0=F(x0);
    fn=F(xn);
	for(i=1;i<n;i++) 
	{
        xi=x0+i*h;
        if(i%3==0)
            sum+=2*F(xi);
        else
            sum+=3*F(xi);
    }
    in=(3*h/8)*(f0+sum+fn);
    printf("\nUsing composite Simpson's 3/8 rule,");
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
	if(n%3==0 && n==3)
		i=basicSimpson(x0,xn);
	else
		i=compSimpson(x0,xn,n);
	printf("\n\tI = %.5f",i);
	return 0;
}
