#include<iostream>
#include<stdlib.h>
#define MAX 3
using namespace std;
class CircularQueue
{
	private:
		int a[MAX],rear,front,item;
	public:
		CircularQueue()
		{
			rear=front=-1;
		}
		bool isEmpty()
		{
			return(front==-1 && rear==-1);
		}
		void enqueue()
		{
			if((front==0 && rear==MAX-1) || ((front==rear+1)%MAX))
				cout<<endl<<"Queue overflow"<<endl;
			else
			{
				cout<<endl<<"Enter item to be queued: ";
				cin>>item;
				if(front==-1 && rear==-1)
					rear=front=0;
				else
					rear=(rear+1)%MAX;
				a[rear]=item;
			}
		}
		void dequeue()
		{
			if(isEmpty())
				cout<<endl<<"Queue underflow"<<endl;
			else
			{
				cout<<endl<<"Dequeued item  = "<<a[front]<<endl;
				if(front==rear)
					rear=front=-1;
				else
					front=(front+1)%MAX;
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
	int ch;
	char c;
	CircularQueue q;
	do
	{
		cout<<"Circular Queue Operations :\n1. Enqueue\n2. Dequeue\n3. Traverse\n4. Exit\nEnter your choice : ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				q.enqueue();
				break;
			case 2:
				q.dequeue();
				break;
			case 3:
				q.traverse();
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
