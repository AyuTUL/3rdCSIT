#include<iostream>
using namespace std;
void bubble(int *a,int n)
{
	for(int i=0;i<n-1;i++)
		for(int j=0;j<n-i-1;j++)
			if(a[j]>a[j+1])
			{
				int temp=a[j];
				a[j]=a[j+1];
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
	cout<<endl<<endl<<"After bubble sort :"<<endl;
	bubble(a,n);
	printArray(a,n);
	delete[] a;
	return 0;
}