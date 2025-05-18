#include<iostream>
#include<stdlib.h>
using namespace std;
struct Node {
    int key,height;
    Node *left,*right;
};
int height(Node* node) {
    return node?node->height:0;
}
int maxVal(int a,int b) {
    return (a>b)?a:b;
}
Node* newNode(int key) {
    Node* node=new Node();
    node->key=key;
    node->left=node->right=NULL;
    node->height=1;
    return node;
}
Node* rightRotate(Node* y) {
    if(!y || !y->left) return y;
    Node* x=y->left;
    Node* T2=x->right;
    x->right=y;
    y->left=T2;
    y->height=maxVal(height(y->left),height(y->right))+1;
    x->height=maxVal(height(x->left),height(x->right))+1;
    return x;
}
Node* leftRotate(Node* x) {
    if(!x || !x->right) return x;
    Node* y=x->right;
    Node* T2=y->left;
    y->left=x;
    x->right=T2;
    x->height=maxVal(height(x->left),height(x->right))+1;
    y->height=maxVal(height(y->left),height(y->right))+1;
    return y;
}
int getBalance(Node* node) {
    return node?height(node->left)-height(node->right):0;
}
Node* insert(Node* node,int key) {
    if(!node) return newNode(key);
    if(key<node->key)
        node->left=insert(node->left,key);
    else if(key>node->key)
        node->right=insert(node->right,key);
    else {
        cout<<"Duplicate key not allowed : "<<key<<endl;
        return node;
    }
    node->height=1+maxVal(height(node->left),height(node->right));
    int balance=getBalance(node);
    if(balance>1 && key<node->left->key)
        return rightRotate(node);
    if(balance<-1 && key>node->right->key)
        return leftRotate(node);
    if(balance>1 && key>node->left->key) {
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance<-1 && key<node->right->key) {
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
Node* minValueNode(Node* node) {
    Node* current=node;
    while(current && current->left)
        current=current->left;
    return current;
}
Node* deleteNode(Node* root,int key) {
    if(!root) {
        cout<<"Key not found : "<<key<<endl;
        return root;
    }
    if(key<root->key)
        root->left=deleteNode(root->left,key);
    else if(key>root->key)
        root->right=deleteNode(root->right,key);
    else {
        if(!root->left || !root->right) {
            Node* temp=root->left?root->left:root->right;
            delete root;
            return temp;
        } 
		else {
            Node* temp=minValueNode(root->right);
            root->key=temp->key;
            root->right=deleteNode(root->right,temp->key);
        }
    }
    root->height=1+maxVal(height(root->left),height(root->right));
    int balance=getBalance(root);
    if(balance>1 && getBalance(root->left)>=0)
        return rightRotate(root);
    if(balance>1 && getBalance(root->left)<0) {
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance<-1 && getBalance(root->right)<=0)
        return leftRotate(root);
    if(balance<-1 && getBalance(root->right)>0) {
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
void preOrder(Node* root) {
    if(root) {
        cout<<root->key<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }
}
void freeTree(Node* root) {
    if(!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}
int main() {
    Node* root=NULL;
    int choice,key;
    do {
        cout<<"AVL Tree Menu :\n1. Insert a node\n2. Delete a node\n3. Pre-order traversal\n4. Exit\nEnter your choice: ";
        cin>>choice;
        switch(choice) {
            case 1:
                cout<<"Enter value to insert: ";
                cin>>key;
                root=insert(root,key);
                break;
            case 2:
                cout<<"Enter value to delete: ";
                cin>>key;
                root=deleteNode(root,key);
                break;
            case 3:
                cout<<"Pre-order traversal : ";
                preOrder(root);
                cout<<endl;
                break;
            case 4:
                cout<<"Exiting program"<<endl;
                freeTree(root);
                break;
            default:
                cout<<"Invalid choice"<<endl;
        }
        cout<<endl;
    }while(choice!=5);
    return 0;
}