#include<iostream>
#include<stdlib.h>
using namespace std;
struct NODE
{
	int data;
	struct NODE* next;
};
typedef struct NODE Node;
class Queue
{
	private:
		Node *front,*rear;
	public:
		Queue()
		{
			front=rear=NULL;
		}
		bool isEmpty()
		{
			return(rear==NULL);
		}
		~Queue()
		{
			while(!isEmpty())
				dequeue();
		}
		void enqueue()
		{
			Node *newNode=new Node();
			cout<<endl<<"Enter data to be enqueued : ";
			cin>>newNode->data;			
			newNode->next=NULL;
			if(isEmpty())
				front=rear=newNode;
			else
			{
				rear->next=newNode;
				rear=newNode;
			}	
			cout<<endl<<"Enqueued "<<newNode->data<<" to queue"<<endl;
		}
		void dequeue()
		{
			if(isEmpty())
				cout<<endl<<"Queue underflow"<<endl;
			else
			{
				Node *temp=front;
				cout<<endl<<"Dequeued item = "<<temp->data<<endl;
				front=front->next;
				if(front==NULL)
					rear=NULL;
				delete temp;
			}	
		}
		void traverse()
		{
			if(isEmpty())
				cout<<endl<<"Queue underflow"<<endl;
			else
			{
				cout<<endl<<"Queue :"<<endl;
				Node *temp=front;
				while(temp!=NULL)
				{
					cout<<temp->data<<"\t";
					temp=temp->next;
				}
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
				break;
			case 4:
				cout<<"Exiting program";
				return 0;
			default:
				cout<<endl<<"Invalid input"<<endl;	
		}
		cout<<endl<<"Again? (Y/N) : ";
		cin>>c;
		system("cls");
	}while(c=='y' || c=='Y');
	return 0;
}