#include<iostream>
using namespace std;
void selection(int *a,int n)
{
	for(int i=0;i<n-1;i++)
	{
		int min=i;
		for(int j=i+1;j<n;j++)
			if(a[j]<a[min])
				min=j;
		if(min!=i)
		{
			int temp=a[i];
			a[i]=a[min];
			a[min]=temp;
		}
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
	cout<<endl<<endl<<"After selection sort :"<<endl;
	selection(a,n);
	printArray(a,n);
	delete[] a;
	return 0;
}