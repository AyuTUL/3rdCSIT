//Lab 17: WAP  in  C to find 1st derivative of function using Newton's divided difference interpolation
#include<stdio.h>
#define MAX 10
int main()
{
	int n,i,k,j;
	float factor,term,vod,xv,x[MAX],fx[MAX],a[MAX];
	printf("Enter no. of data points : ");
	scanf("%d",&n);
	printf("Enter value of x & fx for %d data :\n",n);
	for(i=0;i<n;i++)
		scanf("%f%f",&x[i],&fx[i]);
	printf("Enter the point at which 1st derivative is to be evaluated : ");
	scanf("%f",&xv);
	for(i=0;i<n;i++)
		a[i]=fx[i];
	for(i=0;i<n;i++)
		for(j=n-1;j>i;j--)
			a[j]=(a[j]-a[j+1])/(x[j]-x[j-i-1]);
	vod=a[1];
	for(i-2;i<n;i++)
	{
		term=0;
		for(j=0;j<i;j++)
		{
			factor=1;
			for(k=0;k<i;k++)
			{
				if(k!=j)
					factor=factor*(xv-x[k]);
			}
			term=term+factor;
		}
		vod=vod+(a[i]*term);
	}
	printf("Value of 1st derivative = %f",vod);
	return 0;
}