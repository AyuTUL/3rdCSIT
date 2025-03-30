//Lab 23 : WAP in C that solves system of linear equations using Gauss Seidel method
#include<stdio.h>
#include<math.h>
#define MAX 20
void diagonalDominant(int n,float a[MAX][MAX+1]) 
{
    int i,j,k,maxRow;
    float temp;
    for(i=0;i<n;i++) 
	{
        maxRow=i;
        for(j=i+1;j<n;j++) 
		{
            if(fabs(a[j][i])>fabs(a[maxRow][i]))
                maxRow=j;
        }
        if(maxRow!=i)
            for(k=0;k<=n;k++)
			{
                temp=a[i][k];
                a[i][k]=a[maxRow][k];
                a[maxRow][k]=temp;
            }
    }
}
int main()
{
	int n,i,j,itr=1;
    float a[MAX][MAX+1],tolerance,x[MAX]={0},x_old[MAX],error;
    printf("Enter no. of equations : ");
    scanf("%d",&n);
    printf("Enter coefficients of the equations :\n");
    for(i=0;i<n;i++) 
	{
        printf("Equation %d : ",i+1);
        for(j=0;j<=n;j++)
            scanf("%f",&a[i][j]);
    }
	printf("Enter tolerable error : ");
	scanf("%f",&tolerance);
	diagonalDominant(n,a);
	printf("Using Gauss Seidel method,");
	printf("\n-------------------------------------------------\n");
    printf("| Iteration |");
    for(i=0;i<n;i++)
        printf("%5c%-5d |",'x',i+1);
    printf("\n-------------------------------------------------\n");
	do 
	{
        error=0;
        for (i=0;i<n;i++)
            x_old[i]=x[i];
        for(i=0;i<n;i++) 
		{
            x[i]=a[i][n];
            for(j=0;j<n;j++) 
                if(i!=j)
                    x[i]-=a[i][j]*x[j];
            x[i]/=a[i][i];
            if(fabs(x[i]-x_old[i])>error)
                error=fabs(x[i]-x_old[i]);
        }
        printf("| %9d |",itr);
        for(i=0;i<n;i++) 
            printf(" %9.5f |",x[i]);
        printf("\n");
        itr++;
    }while(error>tolerance);
    printf("-------------------------------------------------\n");
	printf("Solution:");
    for(i=0;i<n;i++)
        printf("\nx%d = %.5f",i+1,x[i]);
	return 0;
}