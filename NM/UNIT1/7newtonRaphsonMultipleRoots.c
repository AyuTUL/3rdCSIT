//Lab 7: WAP in C for calculating multiple roots using Newton Raphson method
#include<stdio.h>
#include<math.h>
#define E 0.0001
float a[20],q[20];
float F(float x,int n) 
{
    float res=0;
    int i;
    for(i=n;i>=0;i--)
        res+=a[i]*pow(x, i);
    return res;
}
float FD(float x,int n)
{
    float res=0;
    int i;
    for(i=n;i>0;i--)
        res+=i*a[i]*pow(x,i-1);
    return res;
}
int  main()
{
	float x0,xr,fx0,fdx0,e,c;
	int i,n,m;
	printf("Enter degree of polynomial : ");
	scanf("%d",&n);
	printf("Enter coefficients of dividend polynomial : ");
	for(i=n;i>=0;i--)
		scanf("%f",&a[i]);
	printf("Enter initial guess : ");
	scanf("%f",&x0);
	printf("\nRoots of polynomial ");
	for(i=n;i>=0;i--)
		printf(" %+gx^%d ",a[i],i);
	while(n>1)
	{
		do
		{
			fx0=F(x0,n);
			fdx0=FD(x0,n);
			xr=x0-fx0/fdx0;
			e=fabs(xr-x0);
			x0=xr;
		}while(e>=E);
		printf("\nRoot %d = %.2f",n,xr);
		c=xr;
		q[n]=0;
		for(m=n-1;m>=0;m--)
			q[m]=a[m+1]+q[m+1]*c;
		for(i=n-1;i>=0;i--)
			a[i]=q[i];
		n--;
		x0=xr;
	}
	xr=-a[0]/a[1];
	printf("\nRoot %d = %.2f",n,xr);
	return 0;
}
