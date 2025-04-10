#include<iostream>
using namespace std;
void merge(int *a,int start,int mid,int end)
{
	int p=start,q=mid+1,temp[end-start+1],k=0;
	for(int i=start;i<=end;i++)
		if(p>mid)
			temp[k++]=a[q++];
		else if(q>end)
			temp[k++]=a[p++];
		else if(a[p]<a[q])
			temp[k++]=a[p++];
		else
			temp[k++]=a[q++];
	for(int i=0;i<k;i++)
		a[start++]=temp[i];
}
void mergeSort(int a[],int start, int end)
{
	if(start<end)
	{
		int mid=(start+end)/2;
		mergeSort(a,start,mid);
		mergeSort(a,mid+1,end);
		merge(a,start,mid,end);
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
	cout<<endl<<endl<<"After merge sort :"<<endl;
	mergeSort(a,0,n-1);
	printArray(a,n);
	delete[] a;
	return 0;
}
