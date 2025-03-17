#include<iostream>
#include<iomanip>
#include<stdlib.h>
#define MAX 3
using namespace std;
class PriorityQueue 
{
    private:
        int a[MAX],priority[MAX],rear,front,item,itemPriority;
    public:
        PriorityQueue() 
		{
            rear=front=-1;
        }
        bool isEmpty()
		{
			return(front==-1 && rear==-1);
		}
        void enqueue()
		{
            if(rear==MAX-1)
				cout<<endl<<"Queue overflow"<<endl;
			else
			{
	            cout<<endl<<"Enter item to be queued : ";
				cin>>item;
	            cout<<"Enter priority of item : ";
	            cin>>itemPriority;
	            if(isEmpty())
					rear=front=0;
				else
					rear++;
				a[rear]=item;
	            priority[rear]=itemPriority;
	            for(int i=front;i<=rear;i++) 
	                for(int j=i+1;j<=rear;j++) 
	                    if(priority[i]>priority[j]) 
						{
	                        int tempPriority=priority[i];
	                        priority[i]=priority[j];
	                        priority[j]=tempPriority;
	                        int tempItem=a[i];
	                        a[i]=a[j];
	                        a[j]=tempItem;
	                    }
	                }
        }
        void dequeue()
        {
			if(isEmpty())
				cout<<endl<<"Queue underflow"<<endl;
			else
			{
				cout<<endl<<"Dequeued item  = "<<a[front]<<endl<<"Priority = "<<priority[front]<<endl;
				if(rear==front)
					rear=front=-1;
				else
					front++;	
			}			
		}
		void traverse()
		{
			if(isEmpty())
				cout<<endl<<"Queue underflow"<<endl;
			else
			{
				cout<<endl<<"Queue"<<setw(7)<<":  ";
				for(int i=front;i<=rear;i++)
					cout<<setw(5)<<left<<a[i];
				cout<<endl<<"Priority :  ";	
				for(int i=front;i<=rear;i++)
					cout<<setw(5)<<left<<priority[i];
				cout<<endl;
			}	
		}
};
int main() 
{
    int ch;
	char c;
	PriorityQueue p;
	do
	{
		cout<<"Ascending Priority Queue Operations :\n1. Enqueue\n2. Dequeue\n3. Traverse\n4. Exit\nEnter your choice : ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				p.enqueue();
				break;
			case 2:
				p.dequeue();
				break;
			case 3:
				p.traverse();
				break;
			case 4:
				exit(0);
			default:
				cout<<"Invalid input"<<endl;	
		}
		cout<<endl<<"Again? (Y/N) : ";
		cin>>c;
		system("cls");
	}while(c=='y' ||c=='Y');
	return 0;
}
