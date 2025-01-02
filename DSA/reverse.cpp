#include<iostream>
#include<string.h>
#define MAX 100
using namespace std;
class Stack
{
	private:
		char a[MAX];
		int length,top;
	public:
		Stack()
		{
			top=-1;
			cout<<"Enter  infix expression : ";
			cin>>a;
			length=strlen(a);
			strrev(a);
		}
		bool isOperator(char c)
		{
			if(c=='('  || c==')'  || c=='^'  || c=='/'  || c=='*'  || c=='+'  || c=='-')
				return(true);
			else
				return(false);
		}
		int precedence(char c)
		{
			if(c=='^')
				return 1;
			else if(c=='/' || c=='*')
				return 2;
			else if(c=='+' || c=='-')
				return 3;	
		}
		void scan()
		{
			for(int i=0;i<length;i++)
			{
				if(isOperator(a[i]))
				{
					push(a[i],);
				}
			}
		}
		void push(Stack s)
		{
			if(top==MAX-1)
				cout<<endl<<"Stack overflow"<<endl;
			else
			{
				s.a[++top]=
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
				cout<<"Stack  is empty";
			else
			{
				cout<<"Stack :"<<endl;
				for(int i=top;i>=0;i--)
					cout<<a[i]<<endl;
			}
		}
};
int main()
{
	Stack infix,operator,prefix;
	infix.scan();
	s.precedence();
	return 0;
}