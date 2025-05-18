#include<iostream>
using namespace std;
void insertion(int *a,int n)
{
	for(int i=1;i<n;i++)
	{
		int temp=a[i];
		int j=i-1;
		while(j>=0 && a[j]>temp)
		{
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=temp;
	}
}
void printArray(int *a,int n)
{
	for(int i=0;i<n;i++)
		cout<<a[i]<<"\t";
}
int main()
{
	int *a,n;
	cout<<"Enter array size : ";
	cin>>n;
	a=new int[n];
	cout<<"Enter "<<n<<" elements : ";
	for(int i=0;i<n;i++)
		cin>>a[i];
	cout<<endl<<"Before sorting :"<<endl;
	printArray(a,n);
	cout<<endl<<endl<<"After insertion sort :"<<endl;
	insertion(a,n);
	printArray(a,n);
	delete[] a;
	return 0;
}