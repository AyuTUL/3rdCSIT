#include<iostream>
using namespace std;
int fact(int n)
{
	if(n<=1)
		return 1;
	else 
		return (n*fact(n-1));
}
int main()
{
	int n;
	cout<<"Enter integer : ";
	cin>>n;
	if(n<0)
		cout<<"Factorial of negative integer doesn't exist.";
	else
		cout<<n<<"! = "<<fact(n);
	return 0;
}