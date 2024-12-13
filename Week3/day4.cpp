#include <iostream>
using namespace std;

// Class for a Node in the Doubly Linked List
class Node {
public:
    int data;   
    Node* prev; 
    Node* next; 

    Node(int value) { // Constructor
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

// Class for Doubly Linked List
class DoublyLinkedList {
private:
    Node* head;

public:
    DoublyLinkedList() { // Constructor initializes an empty list
        head = nullptr;
    }

    // Method to insert a node at the end of the list
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) { // If the list is empty
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) { // Traverse to the last node
            temp = temp->next;
        }
        temp->next = newNode;   
        newNode->prev = temp;   
    }

    // Method to display the list in forward direction
    void displayForward() {
        Node* temp = head;
        cout << "Doubly Linked List (Forward): ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Method to display the list in reverse direction
    void displayReverse() {
        if (head == nullptr) return;

        Node* temp = head;
        while (temp->next != nullptr) { // Traverse to the last node
            temp = temp->next;
        }
        cout << "Doubly Linked List (Reverse): ";
        while (temp != nullptr) { // Traverse backward
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout << endl;
    }

    // Destructor to free memory
    ~DoublyLinkedList() {
        Node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    DoublyLinkedList d11;

    dll.insertAtEnd(10);
    dll.insertAtEnd(20);
    dll.insertAtEnd(30);
    dll.insertAtEnd(40);

    dll.displayForward();
    dll.displayReverse();

    return 0;
}
