//Lab 9: WAP in C to interpolate given data set using Newton's divided difference interpolation method
#include<stdio.h>
#define MAX 5
int main()  
{
	float x[MAX],fx[MAX],DDT[MAX][MAX],xv;
	int i,j;
	printf("Enter x values : ");
	for(i=0;i<MAX;i++)
		scanf("%f",&x[i]);
	printf("Enter f(x) values : ");
	for(i=0;i<MAX;i++)
		scanf("%f",&fx[i]);
	printf("Enter point at which polynomial is to be calculated : ");
	scanf("%f",&xv);
	for(i=0;i<MAX;i++)
	{
		DDT[i][0]=fx[i];
	}
		DDT[1][1]=(fx[1]-fx[0])/(x[1]-x[0]);
		DDT[2][1]=(fx[2]-fx[1]/(x[2]-x[1]);
		DDT[3][1]=(fx[3]-fx[1])/(x[3]-x[1]);
		DDT[4][1]=(fx[4]-fx[1])/(x[4]-x[1]);
		DDT[1][2]=(DDT[2][1]-DDT[1][1])/(x[2]-x[0]);
		DDT[2][1]=(DDT[3][1]-DDT[2][1])/(x[3]-x[1]);
		DDT[3][1]=(DDT[4][1]-DDT[3][1])/(x[4]-x[2]);
		DDT[2][3]=(DDT[2][2]-DDT[1][2])/(x[3]-x[1]);
		DDT[3][3]=(DDT[3][2]-DDT[2][2])/(x[4]-x[2]);
		DDT[2][4]=(DDT[3][3]-DDT[2][3])/(x[4]-x[0]);
	return 0;
}