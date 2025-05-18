#include<iostream>
using namespace std;
void insertion(int *a,int n)
{
	for(int i=1;i<n;i++)
	{
		int temp=a[i],j=i-1;
		while(j>=0 && a[j]>temp)
		{
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=temp;
	}
}
int binary(int a[],int n,int key)
{
	int low=0,high=n-1,mid;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(key==a[mid])
			return mid;
		else if(key<a[mid])
			high=mid-1;
		else
			low=mid+1;
	}
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
	cout<<endl<<endl<<"Sorted array :"<<endl;
	insertion(a,n);
	printArray(a,n);
	pos=binary(a,n,key);
	if(pos==-1)
		cout<<endl<<endl<<"Element "<<key<<" doesn't exist in the array";
	else
		cout<<endl<<endl<<"Element "<<key<<" found at position "<<pos+1;
	delete[] a;
	return 0;
}