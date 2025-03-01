//Lab 6: WAP in C that divides a polynomial function by (x-c) using synthetic division to find quotient and remainder
#include<stdio.h>
#include<math.h>
#define MAX 30
int main()
{
	int a[MAX],b[MAX];
	int i,m,n,c,r;
	printf("Enter degree  of polynomial : ");
	scanf("%d",&n);
	printf("Enter coefficients of dividend polynomial : ");
	for(i=n;i>=0;i--)
		scanf("%d",&a[i]);
	printf("Enter constant term of divsor polynomial : ");
	scanf("%d",&c);
	b[n]=0;
	m=n;
	while(m>0)
	{
		b[m-1]=a[m]+b[m]*c;
		m--;
	}
	printf("Quotient = ");
	m=n-1;
	while(m>=0)
	{
		if(b[m]!=0)
			printf("%+dx^%d ",b[m],m);
		m--;
	}
	r=c*b[0]+a[0];
	printf("\nRemainder = %d",r);
	return 0;
}
