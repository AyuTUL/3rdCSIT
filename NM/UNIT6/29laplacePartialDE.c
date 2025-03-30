//Lab 29 : WAP in C that solves partial DE by using Laplace's equation
#include<stdio.h>
#include<math.h>
#define N 10
#define ERROR 0.000001
void initializeGrid(float u[][N],int n) 
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            u[i][j]=0.0;
    printf("Enter boundary values for %d x %d grid :\n",n,n);
    printf("Top boundary (%d values) : ",n);
    for(j=0;j<n;j++)
        scanf("%f",&u[0][j]);
    printf("Bottom boundary (%d values) : ",n);
    for(j=0;j<n;j++)
        scanf("%f",&u[n-1][j]);
    printf("Left boundary (%d middle values) : ",n-2);
    for(i=1;i<n-1;i++)
        scanf("%f",&u[i][0]);
    printf("Right boundary (%d middle values) : ",n-2);
    for(i=1;i<n-1;i++)
        scanf("%f",&u[i][n-1]);
}
void printGrid(float u[][N],int n) 
{
    int i,j;
    for(i=0;i<n;i++) 
	{
        for(j=0;j<n;j++)
            printf("\t%6.2f",u[i][j]);
        printf("\n");
    }
}
int main() 
{
    float u[N][N],diff,maxDiff;
    int n,i,j,itr=0;
    printf("Enter grid size : ");
    scanf("%d",&n);
    initializeGrid(u,n);
    printf("\nInitial grid :\n");
    printGrid(u,n);
    do 
	{
        maxDiff=0.0;
        for(i=1;i<n-1;i++) 
            for(j=1;j<n-1;j++) 
			{
                float oldValue=u[i][j];
                u[i][j]=(u[i+1][j]+u[i-1][j]+u[i][j+1]+u[i][j-1])/4.0;
                diff=fabs(u[i][j]-oldValue);
                if(diff>maxDiff)
                    maxDiff=diff;
            }
        itr++;
    }while(maxDiff>ERROR);
    printf("\nUsing Laplace's equation,");
    printf("\nSolution :\n");
    printGrid(u,n);
    return 0;
}