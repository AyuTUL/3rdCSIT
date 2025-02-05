//Lab 10: WAP in C to interpolate given data set using Newton's forward difference interpolation formula
#include<stdio.h>
#include<conio.h>
#define MAX 10
int fact(int n)
{
	if(n==0)
		return 1;
	else
		return (n*fact(n-1));
}
int main()
{
	int n,i,j;
	float v=0,p,xp,x[MAX],fx[MAX],fd[MAX],h,s;
	printf("Enter no.of data points : ");
	scanf("%d",&n);
	printf("Enter value at which polynomial is to be interpolated : ");
	scanf("%f",&xp);
	printf("Enter value of x & fx for %d data : ",n);
	for(i=0;i<n;i++)
		scanf("%f%f",&x[i],&fx[i]);
	h=(x[1]-x[0]);
	s=(xp-x[0])/h;
	for(i=0;i<n;i++)
		fd[i]=fx[i];
	for(i=0;i<n;i++)
		for(j=n-1;j>i;j--)
			fd[j]=(fd[j]-fd[j-1]);
	v=fd[0];
	for(i=0;i<n;i++)
	{
		p=1;
		for(j=1;j<=i;j++)
			p=p*(s-j+1);
		v=v+(fd[i]*p)/fact(i);
	}
	printf("Value of polynomial at %.2f = %.4f",xp,v);
	return 0;
}