#include<iostream>
using namespace std;
int i=0;
void Hanoi(int n,int source,int inter,int dest)
{
	if(n==1)
	{
		i++;
		cout<<endl<<"Step "<<i<<" : "<<"Move disk from tower "<<source<<" to "<<dest;
	}
	else
	{
		Hanoi(n-1,source,dest,inter);
		i++;
		cout<<endl<<"Step "<<i<<" : "<<"Move disk from tower "<<source<<" to "<<dest;
		Hanoi(n-1,inter,source,dest);
	}
}
int main()
{
	int n;
	cout<<"Enter no. of disks : ";
	cin>>n;
	cout<<endl<<"Steps to solve Tower of Hanoi : "<<endl;
	Hanoi(n,1,2,3);
	cout<<endl<<endl<<"Minimum no. of steps = "<<i;
	return 0;
}