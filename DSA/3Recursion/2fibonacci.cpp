#include<iostream>
using namespace std;
int fibo(int n)
{
	if(n<=1)
		return n;
	else
		return (fibo(n-2)+fibo(n-1));
}
int main()
{
	int n;
	cout<<"Enter nth term of Fibonacci series : ";
	cin>>n;
	if(n<=0)
		cout<<"Invalid input";
	else
	{
		for(int i=0;i<n;i++)
		cout<<fibo(i)<<"\t";
	}
	return 0;
}
