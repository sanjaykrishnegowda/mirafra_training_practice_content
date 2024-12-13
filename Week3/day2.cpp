#include <iostream>
using namespace std;

// Class for Node
class Node {
public:
    int data;       
    Node* next;     

    Node(int value) { // Constructor to initialize a node
        data = value;
        next = nullptr;
    }
};

// Class for Linked List
class LinkedList {
private:
    Node* head; // Pointer to the head of the list

public:
    LinkedList() { // Constructor initializes an empty list
        head = nullptr;
    }

    // Method to manually create and link nodes
    void createNodes() {
        Node* first = new Node(10);
        Node* second = new Node(20);
        Node* third = new Node(30);

        head = first;          
        first->next = second;  
        second->next = third;  
    }

    // Method to display the linked list
    void displayList() const {
        cout << "Linked List Elements:" << endl;
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Destructor to free memory
    ~LinkedList() {
        Node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList list; // Create a LinkedList object

    list.createNodes();
    list.displayList();  

    return 0;
}
