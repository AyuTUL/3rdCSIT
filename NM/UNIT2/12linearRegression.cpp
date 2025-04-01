//Lab 12 : WAP in C that implements linear regression
#include<stdio.h>
#define MAX 10
int main()
{	
	int i,j,k,n;
	float a=0,b=0,x[MAX],y[MAX],sx=0,sy=0,sxy=0,sx2=0;
	printf("Enter no. of data points : ");
	scanf("%d",&n);
	printf("Enter value of x & fx for %d data :\n",n);
	for(i=0;i<n;i++)
		scanf("%f%f",&x[i],&y[i]);
	for(i=0;i<n;i++)
	{
		sx+=x[i];
		sy+=y[i];
		sxy+=(x[i]*y[i]);
		sx2+=(x[i]*x[i]);
	}
	b=((n*sxy)-(sx*sy))/((n*sx2)-(sx*sx));
	a=(sy/n)-(b*sx/n);
	printf("\nThe fitted linear model is:\n\t%.2f %+.2fx",a,b);
	return 0;
}
