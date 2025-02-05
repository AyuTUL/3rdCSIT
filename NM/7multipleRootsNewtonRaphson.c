//Lab 7: WAP in C for calculating multiple roots using Newton Raphson method
//wrong
#include<stdio.h>
#include<math.h>
#define F(x) (a[4]*x*x*x*x+a[3]*x*x*x+a[2]*x*x+a[1]*x+a[0])
#define FD(x) (4*a[4]*x*x*x+3*a[3]*x*x+2*a[2]*x+a[1])
#define E 0.0001
float a[20],q[20];
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
	while(n>1)
	{
		while(1)
		{
			fx0=F(x0);
			fdx0=FD(x0);
			xr=x0-fx0/fdx0;
			e=(xr-x0)/xr;
			if(fabs(e)<E)
			{
				printf("Root %d = %.2f\n",n,xr);
				break;
			}
			x0=xr;
		}
		c=xr;
		q[n]=0;
		m=n-1;
		while(m>=0)
		{
			q[m]=a[m+1]+q[m+1]*c;
			m--;
		}
		for(i=n;i>=0;i--)
			a[i]=q[i];
		n--;
		x0=xr;
	}
	xr=-a[0]/a[1];
	printf("Root %d = %.2f\n",n,xr);
	return 0;
}