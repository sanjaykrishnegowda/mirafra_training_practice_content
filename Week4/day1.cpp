#include <iostream>
using namespace std;

// Class for Node
class Node {
public:
    int data;       
    Node* next;     

    Node(int value) { 
        data = value;
        next = nullptr;
    }
};

// Class for Circular Linked List
class CircularLinkedList {
private:
    Node* head; 

public:
    CircularLinkedList() { // Constructor initializes an empty list
        head = nullptr;
    }

    // Method to insert a node at the end of the circular list
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) { 
            head = newNode;
            newNode->next = head;  // Point the new node to itself (circular)
        } else {
            Node* temp = head;
            while (temp->next != head) { // Traverse to the last node
                temp = temp->next;
            }
            temp->next = newNode;  
            newNode->next = head;  
        }
    }

    // Method to display the circular linked list
    void displayList() const {
        if (head == nullptr) {
            cout << "The list is empty." << endl;
            return;
        }
        Node* temp = head;
        cout << "Circular Linked List Elements:" << endl;
        do {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head);  
        cout << endl;
    }

    // Destructor to free memory
    ~CircularLinkedList() {
        if (head == nullptr) return;

        Node* temp = head;
        Node* nextNode;
        do {
            nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != head);
    }
};

int main() {
    CircularLinkedList list; 

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtEnd(40);

    list.displayList(); 

    return 0;
}
