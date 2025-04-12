#include<iostream>
using namespace std;
void swap(int &a,int &b)
{
	int temp=a;
	a=b;
	b=temp;
}
void maxHeapify(int *a,int i,int n)
{
	int largest,left=2*i+1,right=2*i+2;
	if(left<n && a[left]>a[i])
		largest=left;
	else
		largest=i;
	if(right<n && a[right]>a[largest])
		largest=right;
	if(largest!=i)
	{
		swap(a[i],a[largest]);
		maxHeapify(a,largest,n);
	}
}
void heap(int *a,int n)
{
	for(int i=n/2-1;i>=0;i--)
        maxHeapify(a, i, n);
    for(int i=n-1;i>0;i--)
    {
        swap(a[0],a[i]);
        maxHeapify(a,0,i);
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
	cout<<endl<<endl<<"After heap sort :"<<endl;
	heap(a,n);
	printArray(a,n);
	delete[] a;
	return 0;
}