//Lab 5 : WAP in C that evaluates a polynomial at a point using Horner method
#include<stdio.h>
#define MAX 10
int main()
{
	int a[MAX],b[MAX],v,i,xv,n;
	printf("Enter degree of polynomial : ");
	scanf("%d",&n);
	printf("Enter coefficients of polynomial of order %d (a%d - a0) : ",n,n);
	for(i=n;i>=0;i--)
		scanf("%d",&a[i]);
	printf("Enter the point at which polynomial is to be evaluated : ");
	scanf("%d",&xv);
	b[n]=a[n];
	for(i=n;i>0;i--)
		b[i-1]=a[i-1]+b[i]*xv;
	printf("\nFor polynomial f(x) =");
	for(i=n;i>=0;i--)
		printf(" %+dx^%d ",a[i],i);
	printf("\nf(%d) = ",xv);
	for(i=n;i>=0;i--)
		printf("%+d(%d)^%d ",a[i],xv,i);
	printf("= %d",b[0]);
	return 0;
}