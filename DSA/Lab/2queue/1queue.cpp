#include<iostream>
#include<stdlib.h>
#define MAX 3
using namespace std;
class Queue
{
	private:
		int a[MAX],rear,front,item;
	public:
		Queue()
		{
			rear=front=-1;
		}
		bool isEmpty()
		{
			return(front==-1 && rear==-1);
		}
		void enqueue()
		{
			if(rear==MAX-1)
				cout<<endl<<"Queue overflow"<<endl;
			else
			{
				cout<<endl<<"Enter item to be queued : ";
				cin>>item;
				if(isEmpty())
					rear=front=0;
				else
					rear++;
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
				if(rear==front)
					rear=front=-1;
				else
					front++;	
			}			
		}
		void traverse()
		{
			if(isEmpty())
				cout<<endl<<"Queue underflow"<<endl;
			else
			{
				cout<<endl;
				for(int i=front;i<=rear;i++)
					cout<<a[i]<<"\t";
				cout<<endl;
			}
			
		}
};
int main()
{
	int ch;
	char c;
	Queue q;
	do
	{
		cout<<"Queue Operations :\n1. Enqueue\n2. Dequeue\n3. Traverse\n4. Exit\nEnter your choice : ";
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
				break
			case 4:
				cout<<"Exiting program";
				return 0;
			default:
				cout<<"Invalid input"<<endl;	
		}
		cout<<endl<<"Again? (Y/N) : ";
		cin>>c;
		system("cls");
	}while(c=='y' ||c=='Y');
	return 0;
}