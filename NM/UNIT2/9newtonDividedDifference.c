//Lab 9: WAP in C to interpolate given data set using Newton's divided difference interpolation method
#include<stdio.h>
#define MAX 5
int main()  
{
	float v=0,p,xv,x[10],fx[10],a[10];
	int n,i,j;
	printf("Enter order of polynomial : ");
	scanf("%d",&n);
	printf("Enter x and f(x) for %d data set : \n",n+1);
	for(i=0;i<=n;i++)
		scanf("%f%f",&x[i],&fx[i]);
	printf("Enter the point at which polynomial is to be evaluated : ");
	scanf("%f",&xv);
	for(i=0;i<n;i++)
		a[i]=fx[i];
	for(i=0;i<n;i++)
		for(j=n-1;j>i;j--)
			a[j]=(a[j]-a[j-1])/(x[j]-x[j-1-i]);
	v=0;
	for(i=0;i<n;i++)
	{
		p=1;
		for(j=0;j<=i-1;j++)
			p*=(xv-x[j]);
		v+=a[i]*p;
	}
	printf("\nf(%g) = %.4f",xv,v);
	return 0;
}
