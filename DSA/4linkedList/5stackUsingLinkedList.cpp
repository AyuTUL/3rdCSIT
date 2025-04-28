#include<iostream>
#include<stdlib.h>
using namespace std;
struct NODE
{
	int data;
	struct NODE *next;
};
typedef struct NODE Node;
class Stack
{
	private:
		Node *top;
	public:
		Stack()
		{
			top=NULL;
		}
		bool isEmpty()
		{
			return(top==NULL);
		}
		~Stack()
		{
			while(!isEmpty())
				pop();
		}
		void push()
		{
			Node *newNode=new Node();
			cout<<endl<<"Enter data to be pushed : ";
			cin>>newNode->data;			
			if(isEmpty())
				newNode->next=NULL;
			else
				newNode->next=top;
			top=newNode;
			cout<<endl<<"Pushed "<<top->data<<" to stack"<<endl;
		}
		void pop()
		{
			if(isEmpty())
				cout<<endl<<"Stack underflow"<<endl;
			else
			{
				cout<<endl<<"Popped item = "<<top->data<<endl;
				Node *temp=top;
				top=top->next;
				delete temp;
			}	
		}
		void view()
		{
			if(isEmpty())
				cout<<endl<<"Stack underflow"<<endl;
			else
			{
				cout<<endl<<"Stack :"<<endl;
				Node *temp=top;
				while(temp!=NULL)
				{
					cout<<temp->data<<endl;
					temp=temp->next;
				}
			}
		}
		void peek()
		{
			if(isEmpty())
				cout<<endl<<"Stack underflow"<<endl;
			else
				cout<<endl<<"Top of stack = "<<top->data<<endl;
		}
};
int main()
{
	int ch;
	char c;
	Stack s;
	do
	{
		cout<<"Stack Operations :\n1. Push\n2. Pop\n3. View\n4. Peek\n5. Exit\nEnter your choice : ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				s.push();
				break;
			case 2:
				s.pop();
				break;
			case 3:
				s.view();
				break;
			case 4:
				s.peek();
				break;
			case 5:
				cout<<"Exiting program";
				return 0;
			default:
				cout<<endl<<"Invalid input"<<endl;	
		}
		cout<<endl<<"Again? (Y/N) : ";
		cin>>c;
		system("cls");
	}while(c=='y' ||c=='Y');
	return 0;
}