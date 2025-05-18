#include<iostream>
#define MAX 100
using namespace std;
class Queue
{
    private:
        int a[MAX],rear,front;
    public:
        Queue()
        {
            rear=front=-1;
        }
        bool isEmpty()
        {
            return(front==-1 && rear==-1);
        }
        bool isFull()
        {
            return(rear==MAX-1);
        }
		void enqueue(int item)
        {
            if(isFull())
                cout<<endl<<"Queue overflow"<<endl;
            else
            {
                if(isEmpty())
                    rear=front=0;
                else
                    rear++;
                a[rear]=item;
            }
        }
        int dequeue()
        {
            if(isEmpty())
            {
                cout<<endl<<"Queue underflow"<<endl;
                return -1;
            }
            else
            {
                int dequeued=a[front];
                if(rear==front)
                    rear=front=-1;
                else
                    front++;    
                return dequeued;
            }            
        }
		int getFront()
        {
            if(isEmpty())
            {
                cout<<endl<<"Queue underflow"<<endl;
                return -1;
            }
            return a[front];
        }
        void traverse()
        {
            if(isEmpty())
                cout<<endl<<"Queue underflow" << endl;
            else
            {
                cout<<endl;
                for(int i=front;i<=rear;i++)
                    cout<<a[i]<<"\t";
                cout<<endl;
            }
        }
};
int getMax(int *a,int n) 
{
    int max=a[0];
    for(int i=1;i<n;i++)
        if(a[i]>max)
            max=a[i];
    return max;
}
void radix(int *a,int n) 
{
    int max=getMax(a,n),divisor=1;
    Queue q[10];
    while(max/divisor>0) 
    {
        for(int i=0;i<n;i++) 
		{
            int digit=(a[i]/divisor)%10;
            q[digit].enqueue(a[i]);
        }
        int index=0;
        for(int digit=0;digit<10;digit++)
            while(!q[digit].isEmpty())
                a[index++]=q[digit].dequeue();
        divisor*=10;
    }
}
void printArray(int *a,int n)
{
    for(int i=0;i<n;i++)
        cout<<a[i]<<"\t";
    cout<<endl;
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
	cout<<endl<<endl<<"After radix sort :"<<endl;
	radix(a,n);
	printArray(a,n);
	delete[] a;
	return 0;
}