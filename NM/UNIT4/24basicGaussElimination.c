//Lab 24 : WAP in C that solves system of linear equations using basic Gauss elimination method method
#include <stdio.h>
#include <math.h>
#define MAX 10
void swapRows(float a[MAX][MAX+1],int row1,int row2,int n) 
{
    float temp;
    for(int i=0;i<=n;i++) 
    {
        temp=a[row1][i];
        a[row1][i]=a[row2][i];
        a[row2][i]=temp;
    }
}
int main() 
{
    int n,i,j,k,maxRow;
    float a[MAX][MAX+1],x[MAX],ratio;
	printf("Enter no. of equations : ");
    scanf("%d",&n);
    printf("Enter coefficients of the equations :\n");
    for(i=0;i<n;i++) 
	{
        printf("Equation %d : ",i+1);
        for(j=0;j<=n;j++)
            scanf("%f",&a[i][j]);
    }
    for(i=0;i<n-1;i++) 
	{
		maxRow=i;
		for(j=i+1;j<n;j++)
            if(fabs(a[j][i])>fabs(a[maxRow][i]))
                maxRow=j;
        if(maxRow!=i)
            swapRows(a,i,maxRow,n);
        if(fabs(a[i][i])<0.000001)
		{
            printf("Mathematical Error: Division by zero or pivot too small.\n");
            return 1;
        }
        for(j=i+1;j<n;j++) 
		{
            ratio=a[j][i]/a[i][i];
            for(k=i;k<=n;k++)
                a[j][k]-=ratio*a[i][k];
        }
    }
    x[n-1]=a[n-1][n]/a[n-1][n-1];
    for(i=n-2;i>=0;i--) 
	{
        x[i]=a[i][n];
        for(j=i+1;j<n;j++)
            x[i]-=a[i][j]*x[j];
        x[i]/=a[i][i];
    }
    printf("Using basic Gauss elimination method,");
    printf("\nSolution:");
    for(i=0;i<n;i++)
        printf("\nx%d = %.5f",i+1,x[i]);
    return 0;
}