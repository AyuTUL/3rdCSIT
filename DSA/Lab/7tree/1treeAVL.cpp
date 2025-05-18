//wrong

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>

using namespace std;

// AVL Tree Node structure
struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

// Function to get height of a node
int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node
Node* newNode(int data) {
    Node* node = new Node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // New node is initially at height 1
    return node;
}

// Function to right rotate subtree rooted with y
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Function to left rotate subtree rooted with x
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node
int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree
Node* insert(Node* node, int data) {
    // 1. Perform the normal BST insertion
    if (node == NULL)
        return newNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // Equal keys not allowed
        return node;

    // 2. Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Get the balance factor of this ancestor node to check whether
    // this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the unchanged node pointer
    return node;
}

// Function to find the node with minimum value in a tree
Node* minValueNode(Node* node) {
    Node* current = node;

    // Loop down to find the leftmost leaf
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Recursive function to delete a node with given key from subtree with
// given root. It returns root of the modified subtree.
Node* deleteNode(Node* root, int data) {
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (data < root->data)
        root->left = deleteNode(root->left, data);

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (data > root->data)
        root->right = deleteNode(root->right, data);

    // If key is same as root's key, then this is the node to be deleted
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // One child case
                *root = *temp; // Copy the contents of the non-empty child
            
            delete temp;
        } else {
            // Node with two children: Get the inorder successor (smallest
            // in the right subtree)
            Node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left), height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
    // this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to search a node with given key in the tree
bool search(Node* root, int data) {
    if (root == NULL)
        return false;
    
    if (root->data == data)
        return true;
    
    if (data < root->data)
        return search(root->left, data);
    
    return search(root->right, data);
}

// Function to print the tree in-order (for debugging purposes)
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

// Function to print the tree in level-order
void printLevelOrder(Node* root) {
    if (root == NULL) {
        cout << "Tree is empty" << endl;
        return;
    }

    // Use an array as a simple queue
    // This approach avoids using STL queue which might not be allowed
    Node* queue[1000];
    int front = 0, rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear) {
        Node* current = queue[front++];
        
        cout << current->data << " (Height: " << current->height << ", Balance: " << getBalance(current) << ")  ";
        
        if (current->left != NULL)
            queue[rear++] = current->left;
        
        if (current->right != NULL)
            queue[rear++] = current->right;
    }
    cout << endl;
}

// Function to free memory
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}

int main() {
    Node* root = NULL;
    int choice, value;
    
    while (true) {
        cout << "\n==== AVL Tree Operations ====" << endl;
        cout << "1. Insert a node" << endl;
        cout << "2. Delete a node" << endl;
        cout << "3. Search for a value" << endl;
        cout << "4. Display tree" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                root = insert(root, value);
                cout << "Value " << value << " inserted successfully" << endl;
                break;
                
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                if (search(root, value)) {
                    root = deleteNode(root, value);
                    cout << "Value " << value << " deleted successfully" << endl;
                } else {
                    cout << "Value " << value << " not found in the tree" << endl;
                }
                break;
                
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if (search(root, value))
                    cout << "Value " << value << " found in the tree" << endl;
                else
                    cout << "Value " << value << " not found in the tree" << endl;
                break;
                
            case 4:
                cout << "\nTree in level order traversal:" << endl;
                printLevelOrder(root);
                cout << "\nTree in-order traversal:" << endl;
                inOrder(root);
                cout << endl;
                break;
                
            case 5:
                cout << "Exiting program..." << endl;
                freeTree(root);
                return 0;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    
    return 0;
}
