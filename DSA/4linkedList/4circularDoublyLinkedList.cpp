#include<iostream>
#include<stdlib.h>
using namespace std;
struct NODE
{
	int data;
	struct NODE *next,*prev;
};
typedef struct NODE Node;
class CircularDoublyLinkedList
{
	private:
		Node *head,*tail;
	public:
		CircularDoublyLinkedList()
		{
			head=tail=NULL;
		}
		bool isEmpty()
		{
			return(head==NULL);
		}
		~CircularDoublyLinkedList()
		{
			while(!isEmpty())
				deleteAtFront();
		}
		Node* createNode()
		{
			Node *newNode=new Node();
			cout<<endl<<"Enter data to be inserted : ";
			cin>>newNode->data;
			newNode->prev=newNode->next=NULL;
			return(newNode);
		}
		void insertAtFront()
		{
			Node *newNode=createNode();
			if(isEmpty())
			{
				head=tail=newNode;
				newNode->next=newNode->prev=newNode;
			}
			else
			{
				newNode->next=head;
				newNode->prev=tail;
				head->prev=newNode;
				tail->next=newNode;
				head=newNode;
			}
			cout<<endl<<"Inserted "<<newNode->data<<" at the front"<<endl;
		}
		void insertAtEnd()
		{
			Node *newNode=createNode();
			if(isEmpty())
			{
				head=tail=newNode;
				newNode->next=newNode->prev=newNode;
			}
			else
			{
				newNode->next=head;
				newNode->prev=tail;
				tail->next=newNode;
				head->prev=newNode;
				tail=newNode;
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
				for(int i=1;i<n && temp->next!=head;i++)
					temp=temp->next;
				if(temp->next==head)
					insertAtEnd();
				else
				{
					Node *newNode=createNode();
					newNode->next=temp->next;
					newNode->prev=temp;	
					temp->next->prev=newNode;
					temp->next=newNode;
					cout<<endl<<"Inserted "<<newNode->data<<" at position "<<n<<endl;
				}
			}	
		}
		void deleteAtFront()
		{
			if(isEmpty())
				cout<<endl<<"Linked list is empty"<<endl;
			else if(head==tail)
			{
				cout<<endl<<"Deleted data : "<<head->data<<endl;
				delete head;
				head=tail=NULL;
			}
			else
			{
				Node *temp=head;
				head=head->next;
				head->prev=tail;
				tail->next=head;
				cout<<endl<< "Deleted data : "<<temp->data<<endl;
				delete temp;
			}
		}
		void deleteAtEnd()
		{
			if(isEmpty())
				cout<<endl<<"Linked list is empty"<<endl;
			else if(head==tail)
				deleteAtFront();
			else
			{
				Node *temp=tail;
				tail=tail->prev;
				tail->next=head;
				head->prev=tail;
				cout<<"Deleted data : "<<temp->data<<endl;
				delete temp;
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
				Node *temp=head;
				for(int i=1;i<n && temp->next!=head;i++)
					temp=temp->next;
				if(temp->next==head)
					cout<<"Position exceeds linked list length";
				else if(temp->next==head)
					deleteAtEnd();
				else
				{
					temp->prev->next=temp->next;
					temp->next->prev=temp->prev;
					cout<<"Deleted data : "<<temp->data<<endl;
					delete temp;
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
				do
				{
					if(temp->data==key)
					{
						found=true;
						break;
					}
					pos++;
					temp=temp->next;
				}while(temp!=head);
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
				do
				{
					cout<<temp->data<<"\t";
					temp=temp->next;
				}while(temp!=head);
			}
			cout<<endl;
		}
		void traverseReverse()
		{
			if(isEmpty())
				cout<<endl<<"Linked list is empty"<<endl;
			else
			{
				cout<<endl<<"Linked List (Reverse):"<<endl;
				Node* temp=tail;
				do
				{
					cout<<temp->data<<"\t";
					temp=temp->prev;
				}while(temp!=tail);
			}
			cout<<endl;
		}
};
int main()
{
	CircularDoublyLinkedList list;
	int ch1,ch2;
	char choice;
	do
	{
		system("cls");
		cout<<"Doubly Linked List Operations :\n1. Insertion\n2. Deletion\n3. Search\n4. Traverse\n5. Exit\nEnter your choice : ";
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
				cout<<endl<<"Traverse Operations :\n1. Normal traversal\n2. Reverse traversal\nEnter your choice : ";
				cin>>ch2;
				if(ch2==1)
					list.traverse();
				else
					list.traverseReverse();
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