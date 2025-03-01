#include<iostream>
using namespace std;
struct Node
{
	int data;
	struct Node* next;
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
		struct *Node insertNode()
		{
			struct Node *newNode=new Node();
			cout<<endl<<"Enter data to be inserted at front : ";
			cin>>newNode->data;
			return(newNode);
		}
		void insertAtFront()
		{
			struct Node *newNode=insertNode();
			newNode->next=head;
			head=newNode;
		}
		void insertAtEnd()
		{
			if(head==NULL)
				newNode->next=NULL;
				head=newNode;
			else
			{
				
			}
			
		}
		void traverse()
		{
			struct Node* temp=head;
			if(temp==NULL)
				cout<<endl<<"List is empty"<<endl;
			else
			{
				cout<<endl<<"Linked List :"<<endl;
				while(temp!=NULL)
				{
					cout<<temp->data<<"\t";
					temp=temp->next;
				}	
			}
			cout<<endl;
		}
};
int main()
{
	LinkedList list;
	int ch;
	char choice;
	do
	{
		system("cls");
		cout<<"Linked List Insertion Operations :\n1. At the beginning\n2. At the middle\n3. At the end\n4. Traverse\nEnter your choice : ";
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
			case 4:
				list.traverse();
				break;
			default:
				cout<<endl<<"Invalid input"<<endl;
		}
		cout<<endl<<"Again? (Y/N) : ";
		cin>>choice;
	}while(choice=='y' || choice=='Y');
	list.traverse();
	return 0;
}