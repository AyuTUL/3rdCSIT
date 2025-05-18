#include<iostream>
#include<string>
#include<ctype.h>
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
		bool isEmpty()
		{
			return (top==-1);
		}
		void push(char item)
		{
			if(top==MAX-1)
				cout<<endl<<"Stack overflow"<<endl;
			else
				a[++top]=item;
		}
		char pop()
		{
			if(isEmpty())
			{
				cout<<endl<<"Stack underflow"<<endl;
				return '\0';
			}	
			else
				return a[top--];
		}
		char peek()
		{
			if(isEmpty())
			{
				cout<<endl<<"Stack underflow"<<endl;
				return '\0';
			}
			else
				return a[top];
		}
};
int precedence(char c)
{
	switch(c)
	{
		case '^': return 3;
		case '/':
		case '*': return 2;
		case '+':
		case '-': return 1;
		default: return 0;
	}
}
bool isOperator(char c)
{
	return (c=='^' || c=='/' || c=='*' || c=='+' || c=='-');
}
bool isRTL(char c)
{
	return (c=='^');
}
string convert(string exp)
{
	Stack sign;
	string postfix="";
	int j=0;
	for(int i=0;i<exp.length();i++)
	{
		if(isspace(exp[i]))
			continue;
		if(isalnum(exp[i]))
			postfix+=exp[i];
		else if(exp[i]=='(')
			sign.push(exp[i]);
		else if(exp[i]==')')
		{
			while(!sign.isEmpty() && sign.peek()!='(')
				postfix+=sign.pop();
			sign.pop();
		}
		else if(isOperator(exp[i]))
		{
			while(!sign.isEmpty() && (precedence(exp[i])<precedence(sign.peek()) || (precedence(exp[i])==precedence(sign.peek()) && !isRTL(exp[i]))))
				postfix+=sign.pop();
			sign.push(exp[i]);
		}
		else
		{
			cout<<endl<<"Invalid input"<<endl;
			return "";
		}
	}
	while(!sign.isEmpty())
		postfix+=sign.pop();
	return postfix;
}
int main()
{
	string infix;
	cout<<"Enter infix expression : ";
	getline(cin,infix);
	string postfix=convert(infix);
	cout<<"Postfix : ";
	for(int i=0;i<postfix.length();i++)
		cout<<postfix[i]<<' ';
	return 0;
}
