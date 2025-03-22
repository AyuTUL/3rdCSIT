//lab17:wap to find first of a function using newton's divided difference interpolation formula
#include<stdio.h>
#include<conio.h>
int main()
{
	int n,i,j,k;
	float factor,term,vod,xv,x[10],fx[10],a[10];
	printf("enter the number of points\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%f%f",&x[i],&fx[i]);
	}
	printf("enter the value at which derivative is required\n");
	scanf("%f",&xv);
	for(i=0;i<n;i++)
	{
		a[i]=fx[i];	
	}
	for(i=0;i<n;i++)
	{
		for(j=n-1;j>i;j--)
		{
			a[j]=(a[i]-a[j-1])/(x[j]-x[j-1-i]);
		}
	}
	vod=a[1];
	for(i=2;i<n;i++)
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
	printf("value of first derivative = %f\n",vod);
}
