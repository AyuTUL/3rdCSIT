#include<iostream>
using namespace std;
void swap(int &a,int &b)
{
	int temp=a;
	a=b;
	b=temp;
}
void quick(int *a,int left,int right)
{
	int pivot,i,j,temp;
	if(left<right)
	{
		pivot=left;
		i=left;
		j=right;
		while(i<j)
		{
			while(a[i]<=a[pivot] && i<right)
				i++;
			while(a[j]>a[pivot])
				j--;
			if(i<j)
				swap(a[i],a[j]);
		}
		swap(a[pivot],a[j]);
		quick(a,left,j-1);
		quick(a,j+1,right);
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
	cout<<endl<<endl<<"After quick sort :"<<endl;
	quick(a,0,n-1);
	printArray(a,n);
	delete[] a;
	return 0;
}
