//Lab 8: WAP in C to interpolate given data set using Lagrange interpolation 
#include<stdio.h>
#define MAX 10
int main()
{
	float fx[MAX],x[MAX],p,xv,v=0;
	int n,i,j;
	printf("Enter order of polynomial : ");
	scanf("%d",&n);
	printf("Enter x and f(x) for %d data set : \n",n+1);
	for(i=0;i<=n;i++)
		scanf("%f%f",&x[i],&fx[i]);
	printf("Enter the point at which polynomial is to be evaluated : ");
	scanf("%f",&xv);
	for(i=0;i<=n;i++)
	{
		p=1;
		for(j=0;j<=n;j++)
			if(i!=j)
				p*=(xv-x[j])/(x[i]-x[j]);
		v+=p*fx[i];
	}
	printf("Value of polynomial = %f",v);
	return 0;
}
