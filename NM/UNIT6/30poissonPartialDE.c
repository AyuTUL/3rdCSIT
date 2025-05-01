#include<stdio.h>
#include<math.h>
#define N 10
#define ERROR 0.00001
#define F(x,y) (x*y)
void initializeGrid(float u[][N],int n,float f) 
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            u[i][j]=f;
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
    float h,f;
    printf("Enter grid size : ");
    scanf("%d",&n);
    printf("Enter boundary value : ");
    scanf("%f",&f);
    printf("Enter step size : ");
    scanf("%f",&h);
    initializeGrid(u,n,f);
    printf("\nInitial grid :\n");
    printGrid(u,n);
    do
    {
        maxDiff=0.0;
        for(i=1;i<n-1;i++)
            for(j=1;j<n-1;j++) 
			{
                float x=j*h;
                float y=(n-1-i)*h;
                float oldValue=u[i][j];
                u[i][j]=(u[i+1][j]+u[i-1][j]+u[i][j+1]+u[i][j-1]-h*h*F(x, y))/4.0;
                diff=fabs(u[i][j]-oldValue);
                if(diff>maxDiff)
                    maxDiff=diff;
            }
        itr++;
    }while(maxDiff>ERROR);
    printf("\nUsing Poisson's equation,");
    printf("\nSolution :\n");
    printGrid(u,n);
    return 0;
}
