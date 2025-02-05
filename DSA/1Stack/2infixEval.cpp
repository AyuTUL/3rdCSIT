#include<iostream>
#include<math.h>
#include<ctype.h>
#define MAX 100
using namespace std;
template<class T>
class Stack
{
	private:
		T a[MAX];
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
		void push(T item)
		{
			if(top==MAX-1)
				cout<<endl<<"Stack overflow"<<endl;
			else
				a[++top]=item;
		}
		T pop()
		{
			if(isEmpty())
			{
				cout<<endl<<"Stack underflow"<<endl;
				return T();
			}	
			else
				return a[top--];
		}
		T peek()
		{
			if(isEmpty())
			{
				cout<<endl<<"Stack underflow"<<endl;
				return T();
			}
			else
				return a[top];
		}
};
bool isOperator(char c)
{
	return (c=='^' || c=='/' || c=='*' || c=='+' || c=='-');
}
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
float process(float op1,float op2,char op)
{
	switch(op)
	{
		case '^': return pow(op1,op2);
		case '/': return op1/op2;
		case '*': return op1*op2;
		case '+': return op1+op2;
		case '-': return op1-op2;
		default: return 0;
	}
}
float operate(Stack<float> &operand,Stack<char> &sign)
{
	char op=sign.pop();
	float op1=operand.pop();
	float op2=operand.pop();
	return process(op2,op1,op);
}
float evaluate(string exp)
{
	Stack<char> sign;
	Stack<float> operand;
	for(int i=0;i<exp.length();i++)
	{
		if(isspace(exp[i]))
			continue;
		if(isdigit(exp[i]))
		{
			float num=0;
			while(isdigit(exp[i]))
			{
				num=num*10+(exp[i]-'0');
				i++;
			}
			i--;
			operand.push(num);
		}
		else if(exp[i]=='(')
			sign.push(exp[i]);
		else if(exp[i]==')')
		{
			while(!sign.isEmpty() && sign.peek()!='(')
				operand.push(operate(operand,sign));
			sign.pop();
		}
		else if(isOperator(exp[i]))
		{
			while(!sign.isEmpty() && precedence(exp[i])<precedence(sign.peek()))
				operand.push(operate(operand,sign));
			sign.push(exp[i]);
		}
		else
		{
			cout<<endl<<"Invalid output"<<endl;
			return 0;
		}
	}
	while(!sign.isEmpty())
		operand.push(operate(operand,sign));
	return operand.pop();
}
int main()
{
	string infix;
	cout<<"Enter infix expression : ";
	getline(cin,infix);
	cout<<"Answer : "<<evaluate(infix);
	return 0;
}
