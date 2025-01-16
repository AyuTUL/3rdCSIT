#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<math.h>
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
			{
				a[++top]=item;
			}
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
				cout<<"Stack underflow\n";
				return T();
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
int process(int op1,int op2,char op)
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
int operate(Stack<int> &operand,Stack<char> &sign)
{
	char op=sign.pop();
	int op1=operand.pop();
	int op2=operand.pop();
	return process(op2,op1,op);
}
void evaluate(char exp[])
{
	Stack<char> sign;
	Stack<int> operand;
	int length=strlen(exp);
	for(int i=0;i<length;i++)
	{
		if(isspace(exp[i]))
			continue;
		if(isdigit(exp[i]))
		{
			int num=0;
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
			{
				operand.push(operate(operand,sign));
			}
			sign.pop();
		}
		else
		{
			while(!sign.isEmpty() && precedence(exp[i])<precedence(sign.peek()))
				operand.push(operate(operand,sign));
			sign.push(exp[i]);
		}
	}
	while(!sign.isEmpty())
		operand.push(operate(operand,sign));
	cout<<operand.pop();
}

int main()
{
	char infix[MAX];
	cout<<"Enter  infix expression : ";
	cin>>infix;
	evaluate(infix);
	return 0;
}
