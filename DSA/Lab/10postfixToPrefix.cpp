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
				cout<<"Stack underflow\n";
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
	return op+op2+op1;
}
string convert(string exp)
{
	Stack operand;
	for(int i=0;i<exp.length();i++)
	{
		if(isspace(exp[i]))
			continue;
		if(isalnum(exp[i]))
			operand.push(string(1,exp[i]));
		else if(isOperator(exp[i]))
			operand.push(newString(operand,exp[i]));
		else
		{
			cout<<"Invalid input"<<endl;
			return "";
		}
	}
	return operand.pop();
}
int main()
{
	system("color f0");
	string postfix;
	cout<<"Enter postfix expression : ";
	getline(cin,postfix);
	string prefix=convert(postfix);
	cout<<"Prefix : ";
	for(int i=0;i<prefix.length();i++)
		cout<<prefix[i]<<' ';
	return 0;
}
