#include<iostream>
using namespace std;
void shell(int *a,int n)
{
	for(int gap=n/2;gap>0;gap/=2)
		for(int i=gap;i<n;i++)
		{
			int temp=a[i],j;
			for(j=i;j>=gap && a[j-gap]>temp;j-=gap)
				a[j]=a[j-gap];
			a[j]=temp;
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
	cout<<endl<<endl<<"After shell sort :"<<endl;
	shell(a,n);
	printArray(a,n);
	delete[] a;
	return 0;
}
