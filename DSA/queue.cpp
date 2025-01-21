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
		void enqueue()
		{
			if(rear==MAX-1)
				cout<<endl<<"Queue overflow"<<endl;
			else
			{
				cout<<endl<<"Enter item to be queued: ";
				cin>>item;
				if(rear==front==-1)
					rear=front=0;
				else
					rear++;
				a[rear]=item;
			}
		}
		void dequeue()
		{
			if(rear==-1)
				cout<<endl<<"Queue underflow"<<endl;
			else
			{
				cout<<endl<<"Popped item  = "<<a[front]<<endl;
				if(rear==front)
					rear=front;
				else
					front++;	
			}
				
		}
		void traverse()
		{
			for(int i=rear;i>front;i--)
				cout<<a[i]<<"\t";
		}
};
int main()
{
	int ch;
	char c;
	Queue q;
	do
	{
		cout<<"Queue Operations :\n1. Enqueue\n2. Dequeue\n3. Traverse\nEnter your choice : ";
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
			default:
				cout<<"Invalid input"<<endl;	
		}
		cout<<endl<<"Again? (Y/N) : ";
		cin>>c;
		system("cls");
	}while(c=='y' ||c=='Y');
}