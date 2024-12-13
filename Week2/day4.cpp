#include <iostream>
using namespace std;

// Structure for Linked List Node 
struct Node {
    int row, col, value;
    Node* next;

    Node(int r, int c, int v) {
        row = r;
        col = c;
        value = v;
        next = nullptr;
    }
};

// Function to display a linked list representation
void displayLinkedList(Node* head) {
    Node* temp = head;
    cout << "Sparse Array (Linked List Representation):" << endl;
    while (temp != nullptr) {
        cout << "Row: " << temp->row << ", Col: " << temp->col << ", Value: " << temp->value << endl;
        temp = temp->next;
    }
}

// Function to display an array representation of Sparse Array
void displayArray(int sparseArray[][3], int size) {
    cout << "Sparse Array (Array Representation):" << endl;
    cout << "Row Col Value" << endl;
    for (int i = 0; i < size; i++) {
        cout << sparseArray[i][0] << "   " << sparseArray[i][1] << "   " << sparseArray[i][2] << endl;
    }
}

int main() {
    // Original Sparse Matrix (3x4 Matrix)
    int matrix[3][4] = {
        {0, 0, 3, 0},
        {0, 0, 0, 4},
        {5, 0, 0, 0}
    };

    // 1. Array Representation of Sparse Array
    int sparseArray[3][3]; // Max non-zero elements = 3
    int index = 0;

    cout << "Original Matrix:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << matrix[i][j] << " ";
            if (matrix[i][j] != 0) {
                sparseArray[index][0] = i;       
                sparseArray[index][1] = j;       
                sparseArray[index][2] = matrix[i][j]; 
                index++;
            }
        }
        cout << endl;
    }
    displayArray(sparseArray, index);

    // 2. Linked List Representation of Sparse Array
    Node* head = nullptr; 
    Node* tail = nullptr; 

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (matrix[i][j] != 0) {
                Node* newNode = new Node(i, j, matrix[i][j]);
                if (head == nullptr) {
                    head = newNode; 
                    tail = head;
                } else {
                    tail->next = newNode; 
                    tail = newNode;
                }
            }
        }
    }
    displayLinkedList(head);
    
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
