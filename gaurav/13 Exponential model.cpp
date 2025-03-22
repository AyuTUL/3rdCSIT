//lab 13: WAP to implement exponential regresion model
#include<stdio.h>
#include<conio.h>
#include<math.h>
int main()

{
	int i,j,k,n;
	float a=0,b=0,x[10],A,y[10],Y[10],sx=0,sy=0,sxy=0,sx2=0;
	printf("Enter no. of points:");
	scanf("%d",&n);
	printf("Enter value of x and fx\n");
	for(i=0;i<n;i++)
	{
		scanf("%f%f",&x[i],&y[i]);
	}
	
	for(i=0;i<n;i++)
	{
		Y[i]=log(y[i]);
	}
	for(i=0;i<n;i++)
	{
		sx=sx+x[i];
		sy=sy+Y[i];
		sxy=sxy+x[i]*Y[i];
		sx2=sx2+x[i]*x[i];
	}
	b=((n*sxy)-(sx*sy))/((n*sx2)-(sx*sx));
	a=(sy/n)-(b*sx/n);
	A=exp(a);
	printf("Fitted model is %.2fe^(%.2fx)",A,b);
	getch();
}