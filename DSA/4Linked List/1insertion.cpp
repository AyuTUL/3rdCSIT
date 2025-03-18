#include<iostream>
using namespace std;
struct NODE
{
	int data;
	struct Node* next;
};
typedef struct NODE Node;
class LinkedList
{
	private:
		Node* head;
	public:
		LinkedList()
		{
			head=NULL;
		}
		*Node createNode()
		{
			Node *newNode=new Node();
			cout<<endl<<"Enter data to be inserted at front : ";
			cin>>newNode->data;
			return(newNode);
		}
		void insertAtFront()
		{
			Node *newNode=createNode();
			newNode->next=head;
			head=newNode;
		}
		void insertAtEnd()
		{
			Node *newNode=createNode();
			newNode->data=item;
			if(head==NULL)
			{
				newNode->next=NULL;
				head=newNode;	
			}	
			else
			{
				Node *temp=new Node();
				temp=head;
				while(temp->next!=NULL)
					temp=temp->next;
				temp->next=newNode;
				newNode->next=NULL;
				free(temp);
			}
		}
		void insertBeforeNode()
		{
			int n;
			cout<<"Enter position of node to be inserted before : ";
			cin>>n;
			Node *newNode=createNode();
			Node *temp=new Node();
			for(int i=1;i<n-1;i++)
				temp=temp->next;
			newNode->next=temp->next;
			temp->next=newNode;
			free(temp);
		}
		void insertAfterNode()
		{
			int n;
			cout<<"Enter position of node to be inserted after : ";
			cin>>n;
			Node *newNode=createNode();
			Node *temp=new Node();
			for(int i=1;i<n;i++)
				temp=temp->next;
			newNode->next=temp->next;
			temp->next=newNode;
			free(temp);
		}
		void deleteAtFront()
		{
			if(head==NULL)
				cout<<"Linked list underflow";
			else
			{
				Node *temp=new Node();
				temp=head;
				head=temp->next;
				temp->next=NULL;
				free(temp);
			}
		}
		void deleteAtEnd()
		{
			if(head==NULL)
				cout<<"Linked list underflow";
			else if(head->next==NULL)
			{
				Node *temp=new Node();
				temp=head;
				head=NULL;
				free(temp);
			}
			else
			{
				Node *temp1=new Node();
				Node *temp2=new Node();
				temp1=head;
				while(temp1->next!=NULL)
				{
					temp2=temp1;
					temp1=temp1->next;
				}
				temp2->next=NULL;
				free(temp1);
			}
		}
		void  deleteAtNode()
		{
			int n;
			cout<<"Enter position of node to be deleted : ";
			cin>>n;
			Node *temp1=new Node();
			Node *temp2=new Node();
			temp1=head;
			for(inti=1;i<n;i++)
			{
				temp2=temp1;
				temp1=temp1->next;
			}
			temp2->next=temp->next;
			temp1->next=NULL;
			free(temp1);
		}
		void deleteBeforeNode()
		{
			
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