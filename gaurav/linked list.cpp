#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

void insertAtFront(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
    cout << "Node inserted at the front: " << value << endl;
}

void insertAtMiddle(Node*& head, int value, int position) {
    if (position <= 0) {
        cout << "Invalid position." << endl;
        return;
    }

    Node* newNode = new Node;
    newNode->data = value;
    Node* temp = head;
    int count = 1;

    while (temp != NULL && count < position - 1) {
        temp = temp->next;
        count++;
    }

    if (temp == NULL) {
        cout << "Position is out of bounds." << endl;
        delete newNode;
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    cout << "Node inserted at position " << position << ": " << value << endl;
}

void insertAtEnd(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    cout << "Node inserted at the end: " << value << endl;
}

void deleteFromFront(Node*& head) {
    if (head == NULL) {
        cout << "List is empty, nothing to delete." << endl;
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
    cout << "Node deleted from the front." << endl;
}

void deleteFromMiddle(Node*& head, int position) {
    if (head == NULL || position <= 0) {
        cout << "Invalid position or empty list." << endl;
        return;
    }

    Node* temp = head;
    int count = 1;

    while (temp != NULL && count < position - 1) {
        temp = temp->next;
        count++;
    }

    if (temp == NULL || temp->next == NULL) {
        cout << "Position is out of bounds." << endl;
        return;
    }

    Node* nodeToDelete = temp->next;
    temp->next = temp->next->next;
    delete nodeToDelete;
    cout << "Node deleted from position " << position << "." << endl;
}

void deleteFromEnd(Node*& head) {
    if (head == NULL) {
        cout << "List is empty, nothing to delete." << endl;
        return;
    }

    if (head->next == NULL) {
        delete head;
        head = NULL;
        cout << "Node deleted from the end." << endl;
        return;
    }

    Node* temp = head;
    while (temp->next != NULL && temp->next->next != NULL) {
        temp = temp->next;
    }

    delete temp->next;
    temp->next = NULL;
    cout << "Node deleted from the end." << endl;
}

void traverse(Node* head) {
    if (head == NULL) {
        cout << "The list is empty." << endl;
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

void deleteList(Node*& head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* head = NULL; 
    int choice, value, position;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert at the front\n";
        cout << "2. Insert at the middle\n";
        cout << "3. Insert at the end\n";
        cout << "4. Delete from the front\n";
        cout << "5. Delete from the middle\n";
        cout << "6. Delete from the end\n";
        cout << "7. Traverse (Display the list)\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                cout << "Enter the value to insert at the front: ";
                cin >> value;
                insertAtFront(head, value);
                break;

            case 2: 
                cout << "Enter the value to insert at the middle: ";
                cin >> value;
                cout << "Enter the position: ";
                cin >> position;
                insertAtMiddle(head, value, position);
                break;

            case 3: 
                cout << "Enter the value to insert at the end: ";
                cin >> value;
                insertAtEnd(head, value);
                break;

            case 4: 
                deleteFromFront(head);
                break;

            case 5: 
                cout << "Enter the position to delete from the middle: ";
                cin >> position;
                deleteFromMiddle(head, position);
                break;

            case 6: 
                deleteFromEnd(head);
                break;

            case 7:
                cout << "Linked List: ";
                traverse(head);
                break;

            case 8: 
                cout << "Exiting program.\n";
                deleteList(head);  
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 8);

    return 0;
}
