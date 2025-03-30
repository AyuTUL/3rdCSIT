//Lab 11 : WAP in C that interpolates given data set using Newton Backward difference formula
#include<stdio.h>
#define MAX 10
int fact(int n)
{
	if(n<=1)
		return 1;
	else
		return n*fact(n-1);
}
int main()
{
	system("color f0");
	int n,i,j;
	float v=0,p,xv,x[MAX],fx[MAX],bd[MAX],h,s;
	printf("Enter no. of data points : ");
	scanf("%d",&n);
	printf("Enter value of x & fx for %d data :\n",n);
	for(i=0;i<n;i++)
		scanf("%f%f",&x[i],&fx[i]);
	printf("Enter the point at which polynomial is to be evaluated : ");
	scanf("%f",&xv);
	h=(x[1]-x[0]);
	s=(xv-x[n-1])/h;
	for(i=0;i<n;i++)
		bd[i]=fx[i];
	for(i=n-1;i>0;i--)
		for(j=0;j<i;j++)
			bd[j]=(bd[j+1]-bd[j]);
	v=bd[n-1];
	for(i=1;i<n;i++)
	{
		p=1;
		for(j=1;j<=i;j++)
			p=p*(s+j-1);
		v+=(bd[n-i-1]*p)/fact(i);
	}
	printf("\nf(%g) = %.5f",xv,v);
	return 0;
}
