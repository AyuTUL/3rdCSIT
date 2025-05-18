#include<iostream>
#include<stdlib.h>
#define MAX 3
using namespace std;
class Deque
{
	private:
		int a[MAX],rear,front,item;
	public:
		Deque()
		{
			rear=front=-1;
		}
		bool isFull()
		{
			return((front==0 && rear==MAX-1) || (front==rear+1));
		}
		bool isEmpty()
		{
			return(front==-1);
		}
		void enqueueAtFront()
		{
			if(isFull())
				cout<<endl<<"Queue overflow"<<endl;
			else
			{
				cout<<endl<<"Enter item to be queued : ";
				cin>>item;
				if(isEmpty())
					front=rear=0;
				else if(front==0)
					front=MAX-1;
				else
					front--;
				a[front]=item;
			}
		}
		void enqueueAtRear()
		{
			if(isFull())
				cout<<endl<<"Queue overflow"<<endl;
			else
			{
				cout<<endl<<"Enter item to be queued : ";
				cin>>item;
				if(isEmpty())
					front=rear=0;
				else if(rear==MAX-1)
					rear=0;
				else
					rear++;
				a[rear]=item;
			}
		}
		void dequeueAtFront()
		{
			if(isEmpty())
				cout<<endl<<"Queue underflow"<<endl;
			else
			{
				cout<<endl<<"Dequeued item  = "<<a[front]<<endl;
				if(front==rear)
					front=rear=-1;
				else if(front==MAX-1)
					front=0;
				else
					front++;	
			}			
		}
		void dequeueAtRear()
		{
			if(isEmpty())
				cout<<endl<<"Queue underflow"<<endl;
			else
			{
				cout<<endl<<"Dequeued item  = "<<a[rear]<<endl;
				if(front==rear)
					front=rear=-1;
				else if(rear==0)
					rear=MAX-1;
				else
					rear--;	
			}			
		}
		void traverse()
		{
			if(isEmpty())
				cout<<endl<<"Queue underflow"<<endl;
			else
			{
				cout<<endl;
				for(int i=front;i!=rear;i=(i+1)%MAX)
					cout<<a[i]<<"\t";
				cout<<a[rear]<<endl;
			}	
		}
};
int main()
{
	int ch1,ch2;
	char c;
	Deque d;
	do
	{
		cout<<"Double Ended Operations :\n1. Enqueue\n2. Dequeue\n3. Traverse\n4. Exit\nEnter your choice : ";
		cin>>ch1;
		switch(ch1)
		{
			case 1:
				cout<<endl<<"Enqueue Operations :\n1. Enqueue at the beginning\n2. Enqueue at the end\nEnter your choice : ";
				cin>>ch2;
				if(ch2==1)
					d.enqueueAtFront();
				else if(ch2==2)
					d.enqueueAtRear();
				else
					cout<<"Invalid input"<<endl;
				break;
			case 2:
				cout<<endl<<"Dequeue Operations :\n1. Dequeue at the beginning\n2. Dequeue at the end\nEnter your choice : ";
				cin>>ch2;
				if(ch2==1)
					d.dequeueAtFront();
				else if(ch2==2)
					d.dequeueAtRear();
				else
					cout<<"Invalid input"<<endl;
				break;
			case 3:
				d.traverse();
				break;
			case 4:
				exit(0);
			default:
				cout<<"Invalid input"<<endl;	
		}
		cout<<endl<<"Again? (Y/N) : ";
		cin>>c;
		system("cls");
	}while(c=='y' ||c=='Y');
	return 0;
}
