//Lab 13 : WAP in C that implements exponential regresion
#include<stdio.h>
#include<math.h>
int main()
{
	int i,n;
	float A=0,b=0,x[10],a,y[10],Y[10],sx=0,sy=0,sxy=0,sx2=0;
	printf("Enter no. of data points : ");
	scanf("%d",&n);
	printf("Enter value of x & fx for %d data :\n",n);
	for(i=0;i<n;i++)
		scanf("%f%f",&x[i],&y[i]);
	for(i=0;i<n;i++)
		Y[i]=log(y[i]);
	for(i=0;i<n;i++)
	{
		sx=sx+x[i];
		sy=sy+Y[i];
		sxy=sxy+x[i]*Y[i];
		sx2=sx2+x[i]*x[i];
	}
	b=((n*sxy)-(sx*sy))/((n*sx2)-(sx*sx));
	A=(sy/n)-(b*sx/n);
	a=exp(A);
	printf("\nThe fitted linear model is:\n\t%.2fe^(%.2fx)",a,b);
	return 0;
}