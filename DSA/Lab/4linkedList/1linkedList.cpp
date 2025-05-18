#include<iostream>
#include<stdlib.h>
using namespace std;
struct NODE
{
	int data;
	struct NODE* next;
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
		bool isEmpty()
		{
			return(head==NULL);
		}
		~LinkedList()
		{
			while(!isEmpty())
				deleteAtFront();
		}
		Node* createNode()
		{
			Node *newNode=new Node();
			cout<<endl<<"Enter data to be inserted : ";
			cin>>newNode->data;
			newNode->next=NULL;
			return(newNode);
		}
		void insertAtFront()
		{
			Node *newNode=createNode();
			newNode->next=head;
			head=newNode;
			cout<<endl<<"Inserted "<<newNode->data<<" at the front"<<endl;
		}
		void insertAtEnd()
		{
			Node *newNode=createNode();
			if(isEmpty())
				head=newNode;	
			else
			{
				Node *temp=head;
				while(temp->next!=NULL)
					temp=temp->next;
				temp->next=newNode;
			}
			cout<<endl<<"Inserted "<<newNode->data<<" at the end"<<endl;
		}
		void insertAtMiddle(int n)
		{
			if(n<=0 || isEmpty())
				insertAtFront();
			else
			{
				Node *temp=head;
				for(int i=1;i<n && temp!=NULL;i++)
					temp=temp->next;
				if(temp==NULL)
					insertAtEnd();
				else
				{
					Node *newNode=createNode();
					newNode->next=temp->next;
					temp->next=newNode;
					cout<<endl<<"Inserted "<<newNode->data<<" at position "<<n<<endl;
				}
			}	
		}
		void deleteAtFront()
		{
			if(isEmpty())
				cout<<endl<<"Linked list is empty"<<endl;
			else
			{
				Node *temp=head;
				head=temp->next;
				cout<<endl<<"Deleted data : "<<temp->data<<endl;
				delete temp;
			}
		}
		void deleteAtEnd()
		{
			if(isEmpty())
				cout<<endl<<"Linked list is empty"<<endl;
			else if(head->next==NULL)
				deleteAtFront();
			else
			{
				Node *temp1=head;
				Node *temp2=NULL;
				while(temp1->next!=NULL)
				{
					temp2=temp1;
					temp1=temp1->next;
				}
				temp2->next=NULL;
				cout<<"Deleted data : "<<temp1->data<<endl;
				delete temp1;
			}
		}
		void deleteAtMiddle(int n)
		{
			if(isEmpty())
				cout<<endl<<"Linked list is empty"<<endl;
			else if(n<=0)
				cout<<"Invalid position";
			else if(n==1)
				deleteAtFront();
			else
			{
				Node *temp1=head;
				Node *temp2=NULL;
				for(int i=1;i<n && temp1!=NULL;i++)
				{
					temp2=temp1;
					temp1=temp1->next;
				}
				if(temp1==NULL)
					cout<<"Position exceeds linked list length";
				else
				{
					temp2->next=temp1->next;
					cout<<"Deleted data : "<<temp1->data<<endl;
					delete temp1;
				}
			}
		}
		void search()
		{
			if(isEmpty())
				cout<<endl<<"Linked list is empty"<<endl;
			else
			{
				bool found=false;
				int key,pos=1;
				cout<<endl<<"Enter data to be searched : ";
				cin>>key;
				Node *temp=head;
				while(temp!=NULL)
				{
					if(temp->data==key)
					{
						found=true;
						break;
					}
					temp=temp->next;
					pos++;
				}
				if(found)
					cout<<endl<<"Element "<<key<<" found at position "<<pos<<endl;
				else
					cout<<endl<<"Element "<<key<<" not found in linked list"<<endl;	
			}		
		}
		void traverse()
		{
			if(isEmpty())
				cout<<endl<<"Linked list is empty"<<endl;
			else
			{
				cout<<endl<<"Linked List :"<<endl;
				Node* temp=head;
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
	int ch1,ch2;
	char choice;
	do
	{
		system("cls");
		cout<<"Linked List Operations :\n1. Insertion\n2. Deletion\n3. Search\n4. Traverse\n5. Exit\nEnter your choice : ";
		cin>>ch1;
		switch(ch1)
		{
			case 1:
				cout<<endl<<"Insertion Operations :\n1. Insert at the beginning\n2. Insert before nth node\n3. Insert after nth node\n4. Insert at the end\nEnter your choice : ";
				cin>>ch2;
				if(ch2==1)
					list.insertAtFront();
				else if(ch2==2)
				{
					int n;
					cout<<endl<<"Enter position of node to insert before : ";
					cin>>n;
					if(n<=1)
						list.insertAtFront();
					else
						list.insertAtMiddle(n-1);
				}
				else if(ch2==3)
				{
					int n;
					cout<<endl<<"Enter position of node to insert after : ";
					cin>>n;
					list.insertAtMiddle(n);
				}
				else if(ch2==4)
					list.insertAtEnd();
				else
					cout<<"Invalid input";
				break;
			case 2:
				cout<<endl<<"Deletion Operations :\n1. Delete at the beginning\n2. Delete before nth node\n3. Delete after nth node\n4. Delete at the end\nEnter your choice : ";
				cin>>ch2;
				if(ch2==1)
					list.deleteAtFront();
				else if(ch2==2)
				{
					int n;
					cout<<endl<<"Enter position of node to delete before : ";
					cin>>n;
					if(n<=1)
						cout<<"Invalid position (no node before position 1)";
					else
						list.deleteAtMiddle(n-1);
				}
				else if(ch2==3)
				{
					int n;
					cout<<endl<<"Enter position of node to delete after : ";
					cin>>n;
					list.deleteAtMiddle(n+1);
				}
				else if(ch2==4)
					list.deleteAtEnd();
				else
					cout<<"Invalid input";
				break;
			case 3:
				list.search();
				break;
			case 4:
				list.traverse();
				break;
			case 5:
				cout<<"Exiting program";
				return 0;
			default:
				cout<<endl<<"Invalid input"<<endl;
		}
		cout<<endl<<"Again? (Y/N) : ";
		cin>>choice;
	}while(choice=='y' || choice=='Y');
	return 0;
}