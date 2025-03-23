#include<iostream>
using namespace std;
struct Node
{
	int data;
	Node* next;
};
class LinkedList
{
	private:
		struct Node* head;
	public:
		LinkedList()
		{
			head=NULL;
		}
		void insertAtFront()
		{
			Node*newNode=new Node();
			cout<<"Enter data to be inserted at front : ";
			cin>>newNode->data;
			newNode->next=head;
			head=newNode;
		}
		void traverse()
		{
			Node* temp=head;
			if(temp==NULL)
				cout<<endl<<"List is empty"<<endl;
			else
			{
				cout<<"Linked List :"<<endl;
				while(temp!=NULL)
				{
					cout<<temp->data<<"\t";
					temp=temp->next;
				}	
			}
		}
};
int main()
{
	LinkedList list;
	int ch;
	char choice;
	do
	{
		cout<<"Linked List Insertion Operations :\n1. At the beginning\n2. At the middle\n3. At the end\nEnter your choice  : ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				list.insertAtFront();
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				cout<<endl<<"Invalid input"<<endl;
		}
		cout<<"Again? (y/n) : ";
		cin>>choice;
	}while(choice=='y' || choice=='Y');
	list.traverse();
	return 0;
}