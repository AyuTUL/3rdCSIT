#include<iostream>
#include<string.h>
#define MAX 100
using namespace std;
class Stack
{
	private:
		char a[MAX];
		int top;
	public:
		Stack()
		{
			top=-1;
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
			return 0;
		}
		void push(char c)
		{
			if(top==MAX-1)
				cout<<endl<<"Stack overflow"<<endl;
			else
			{
				a[++top]=c;
			}
		}
		char pop()
		{
			if(top==-1)
			{
				cout<<endl<<"Stack underflow"<<endl;
				return '\0';
			}
			return(a[top--]);
		}
		char peek()
		{
			if(top==-1)
			{
				cout<<"Stack is empty";
				return '\0';
			}
			return(a[top]);
		}
		char* infixToPostfix(char* infix)
		{
			Stack s;
			char* postfix;
			int j=0;
			for(int i=0;infix[i]!='\0';i++)
			{
				char c;
				c=infix[i];
				if(!isOperator(c) && c!='(' && c!=')')
					postfix[j++]=c;
				else if(c=='(')
					s.push(c);
				else if(c==')')
				{
					while(s.top!=-1 && s.peek()!='(')
						postfix[j++]=s.pop();
					s.pop();
				}
				else
				{
					while(s.top!=-1 && precedence(s.peek())<=precedence(c))
						postfix[j++]=s.pop();
					s.push(c);
				}
			}
			while(s.top!=-1)
				postfix[j++]=s.pop();
			postfix[j]='\0';
		return(postfix);
		}
};
int main()
{
	Stack infix;
	char infixExp[MAX],postfixExp[MAX];
	cout<<"Enter infix expression : ";
	cin>>infixExp;
	cout<<"Postfix expression : "<<infix.infixToPostfix(infixExp)<<endl;
	return 0;
}