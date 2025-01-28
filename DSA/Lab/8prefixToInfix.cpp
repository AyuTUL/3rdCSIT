#include<iostream>
#include<string>
#include<cctype>
#define MAX 100
using namespace std;
class Stack
{
	private:
		string a[MAX];
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
		void push(string item)
		{
			if(top==MAX-1)
				cout<<endl<<"Stack overflow"<<endl;
			else
				a[++top]=item;
		}
		string pop()
		{
			if(isEmpty())
			{
				cout<<endl<<"Stack underflow"<<endl;
				return "";
			}	
			else
				return a[top--];
		}
		string peek()
		{
			if(isEmpty())
			{
				cout<<endl<<"Stack underflow"<<endl;
				return "";
			}
			else
				return a[top];
		}
};
bool isOperator(char c)
{
	return (c=='^' || c=='/' || c=='*' || c=='+' || c=='-');
}
string newString(Stack &operand,char op)
{
	string op1=operand.pop();
	string op2=operand.pop();
	return op1+op2+op;
}
string convert(string exp)
{
	Stack operand;
	for(int i=exp.length()-1;i>=0;i--)
	{
		if(isspace(exp[i]))
			continue;
		if(isalnum(exp[i]))
			operand.push(string(1,exp[i]));
		else if(isOperator(exp[i]))
			operand.push(newString(operand,exp[i]));
		else
		{
			cout<<endl<<"Invalid input"<<endl;
			return "";
		}
	}
	return operand.pop();
}
int main()
{
	string prefix;
	cout<<"Enter prefix expression : ";
	getline(cin,prefix);
	string postfix=convert(prefix);
	cout<<"Postfix : ";
	for(int i=0;i<postfix.length();i++)
		cout<<postfix[i]<<' ';
	return 0;
}
