#include <iostream>
using namespace std;

// Class for Node
class Node {
public:
    int data;       
    Node* next;     

    Node(int value) { // Constructor for Node
        data = value;
        next = nullptr;
    }
};

// Class for Singly Linked List
class SinglyLinkedList {
private:
    Node* head; 

public:
    SinglyLinkedList() { // Constructor initializes an empty list
        head = nullptr;
    }

    // Method to insert a new node at the end of the list
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) { 
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) { 
            temp = temp->next;
        }
        temp->next = newNode; // Link the last node to the new node
    }

    // Method to display the linked list
    void displayList() const {
        cout << "Singly Linked List Elements:" << endl;
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Destructor to free allocated memory
    ~SinglyLinkedList() {
        Node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    SinglyLinkedList list; // Create a Singly Linked List object

    // Inserting nodes into the linked list
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtEnd(40);

    // Displaying the list
    list.displayList();

    return 0;
}
