#include<iostream>
#include<string.h>
#include<cctype>
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
				cout<<"Stack underflow\n";
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
bool isRTL(char c)
{
	return (c=='^');
}
char* convert(string exp)
{
	Stack sign;
	char* prefix=new char[exp.length()+1];
	int j=0;
	for(int i=exp.length()-1;i>=0;i--)
	{
		if(isspace(exp[i]))
			continue;
		if(isalnum(exp[i]))
			prefix[j++]=exp[i];
		else if(exp[i]==')')
			sign.push(exp[i]);
		else if(exp[i]=='(')
		{
			while(!sign.isEmpty() && sign.peek()!=')')
			{
				prefix[j++]=sign.pop();
			}
			sign.pop();
		}
		else
		{
			while(!sign.isEmpty() && (precedence(exp[i])<precedence(sign.peek()) || (precedence(exp[i])==precedence(sign.peek()) && isRTL(exp[i]))))
				prefix[j++]=sign.pop();
			sign.push(exp[i]);
		}
	}
	while(!sign.isEmpty())
		prefix[j++]=sign.pop();
	prefix[j]='\0';
	strrev(prefix);
	return prefix;
}
int main()
{
	string infix;
	cout<<"Enter infix expression : ";
	getline(cin,infix);
	char *prefix=convert(infix);
	cout<<"Prefix : "<<prefix;
	delete[] prefix;
	return 0;
}
