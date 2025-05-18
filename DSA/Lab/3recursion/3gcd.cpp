#include<iostream>
using namespace std;
int gcd(int a,int b)
{
	if(b==0)
		return a;
	else
		return (gcd(b,a%b));
}
int main()
{
	int a,b;
	cout<<"Enter 2 integers : ";
	cin>>a>>b;
	if(a<0 || b<0)
		cout<<"GCD of negative integers doesn't exist.";
	else if(a==0 && b==0)
		cout<<"GCD of both zero doesn't exist.";
	else
		cout<<"GCD  of "<<a<<" & "<<b<<" = "<<gcd(a,b);
	return 0;
}