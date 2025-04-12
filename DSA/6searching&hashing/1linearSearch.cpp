#include<iostream>
using namespace std;
int linear(int a[],int n,int key)
{
	for(int i=0;i<n;i++)
		if(a[i]==key)
			return i;
	return -1;
}
void printArray(int *a,int n)
{
	for(int i=0;i<n;i++)
		cout<<a[i]<<"\t";
}
int main()
{
	int *a,n,key,pos;
	cout<<"Enter array size : ";
	cin>>n;
	a=new int[n];
	cout<<"Enter "<<n<<" elements : ";
	for(int i=0;i<n;i++)
		cin>>a[i];
	cout<<"Enter element to be searched : ";
	cin>>key;
	cout<<endl<<"Array :"<<endl;
	printArray(a,n);
	pos=linear(a,n,key);
	if(pos==-1)
		cout<<endl<<endl<<"Element "<<key<<" doesn't exist in the array";
	else
		cout<<endl<<endl<<"Element "<<key<<" found at position "<<pos+1;
	delete[] a;
	return 0;
}