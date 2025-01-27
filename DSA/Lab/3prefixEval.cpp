#include<iostream>
#include<ctype.h>
#include<math.h>
#define MAX 100
using namespace std;
class Stack
{
	private:
		float a[MAX];
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
		void push(float item)
		{
			if(top==MAX-1)
				cout<<endl<<"Stack overflow"<<endl;
			else
				a[++top]=item;
		}
		float pop()
		{
			if(isEmpty())
			{
				cout<<endl<<"Stack underflow"<<endl;
				return 0;
			}	
			else
				return a[top--];
		}
};
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
float operate(Stack &operand,char op)
{
	float op1=operand.pop();
	float op2=operand.pop();
	return process(op1,op2,op);
}
float evaluate(string exp)
{
	Stack operand;
	for(int i=exp.length()-1;i>=0;i--)
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
		else
			operand.push(operate(operand,exp[i]));
	}
	return operand.pop();
}
int main()
{	
	string prefix;
	cout<<"Enter prefix expression : ";
	getline(cin,prefix);
	cout<<"Answer : "<<evaluate(prefix);
	return 0;
}
