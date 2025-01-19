//Lab 5: WAP in C program to evaluate polynomial 3x^3+2x^2+4x+5 at x=3 using Horner method
#include<stdio.h>
#define MAX 5
int main()
{
	int a[MAX],b[MAX],v,i,xv,n;
	printf("Enter degree of polynomial : ");
	scanf("%d",&n);
	printf("Enter coefficients of polynomial of order %d (a0 - a%d) : ",n,n);
	for(i=0;i<=n;i++)
		scanf("%d",&a[i]);
	printf("Enter the point at which polynomial is to evaluated : ");
	scanf("%d",&xv);
	b[n]=a[n];
	for(i=n;i>=0;i--)
		b[i-1]=a[i-1]+b[i]*xv;
	printf("Value of polynomial at x=%d : %d",xv,b[0]);
	return 0;
}