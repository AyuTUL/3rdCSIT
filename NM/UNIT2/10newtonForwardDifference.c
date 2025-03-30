//Lab 10 : WAP in C that interpolates given data set using Newton's forward difference interpolation formula
#include<stdio.h>
#define MAX 10
int fact(int n)
{
	if(n<=1)
		return 1;
	else
		return (n*fact(n-1));
}
int main()
{
	float v=0,p,xv,x[MAX],fx[MAX],fd[MAX],h,s;
	int n,i,j;
	printf("Enter no. of data points : ");
	scanf("%d",&n);
	printf("Enter value of x & fx for %d data :\n",n);
	for(i=0;i<n;i++)
		scanf("%f%f",&x[i],&fx[i]);
	printf("Enter the point at which polynomial is to be evaluated : ");
	scanf("%f",&xv);
	h=(x[1]-x[0]);
	s=(xv-x[0])/h;
	for(i=0;i<n;i++)
		fd[i]=fx[i];
	for(i=0;i<n;i++)
		for(j=n-1;j>i;j--)
			fd[j]=(fd[j]-fd[j-1]);
	v=fd[0];
	for(i=1;i<n;i++)
	{
		p=1;
		for(j=1;j<=i;j++)
			p=p*(s-j+1);
		v+=(fd[i]*p)/fact(i);
	}
	printf("\nf(%g) = %.5f",xv,v);
	return 0;
}
