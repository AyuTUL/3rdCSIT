#include<iostream>
#include<stdlib.h>
#define MAX 3
using namespace std;
class Stack
{
	private:
		int top,a[MAX],item;
	public:
		Stack()
		{
			top=-1;
		}
		void push()
		{
			if(top==MAX-1)
				cout<<endl<<"Stack overflow"<<endl;
			else
			{
				cout<<endl<<"Enter item to be pushed : ";
				cin>>item;
				a[++top]=item;
				cout<<a[top]<<" has been pushed to stack"<<endl;
			}
		}
		void pop()
		{
			if(top==-1)
				cout<<endl<<"Stack underflow"<<endl;
			else
				cout<<endl<<"Popped item = "<<a[top--];
		}
		void view()
		{
			if(top==-1)
				cout<<endl<<"Stack underflow"<<endl;
			else
			{
				cout<<"Stack :"<<endl;
				for(int i=top;i>=0;i--)
					cout<<a[i]<<endl;
			}
		}
		void peek()
		{
			if(top==-1)
				cout<<endl<<"Stack underflow"<<endl;
			else
				cout<<endl<<"Top of stack = "<<a[top]<<endl;
		}
};
int main()
{
	int ch;
	char c;
	Stack s;
	do
	{
		cout<<"Stack Operations :\n1. Push\n2. Pop\n3. View\n4. Peek\nEnter your choice : ";
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
			default:
				cout<<"Invalid input"<<endl;	
		}
		cout<<endl<<"Again? (Y/N) : ";
		cin>>c;
		system("cls");
	}while(c=='y' ||c=='Y');
	return 0;
}