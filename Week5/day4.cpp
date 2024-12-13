#include <iostream>
using namespace std;

// Node structure for Binary Search Tree
class Node {
public:
    int data;
    Node* left;
    Node* right;

    // Constructor to initialize a node
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Binary Search Tree class
class BST {
private:
    Node* root;

public:
    // Constructor
    BST() {
        root = nullptr;
    }

    // Insert a value into the BST
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);  // Create a new node
        }
        if (value < node->data) {
            node->left = insert(node->left, value);  
        } else {
            node->right = insert(node->right, value); 
        }
        return node;
    }

    // Wrapper method to insert values into the BST
    void insertValue(int value) {
        root = insert(root, value);
    }

    // Find the minimum node in the BST
    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;  
        }
        return node;
    }

    // Delete a node from the BST
    Node* deleteNode(Node* node, int value) {
        if (node == nullptr) {
            return node;  // Node not found
        }

        // Find the node to delete
        if (value < node->data) {
            node->left = deleteNode(node->left, value);  
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value); 
        } else {
            // Node found
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;  
                return temp;  
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;  
                return temp;  
            }
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    // Wrapper method for deleting a node
    void deleteValue(int value) {
        root = deleteNode(root, value);
    }

    // In-order Traversal (for checking the tree structure)
    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);   
            cout << node->data << " ";  
            inOrder(node->right);  
        }
    }
    void inOrderTraversal() {
        cout << "In-order Traversal: ";
        inOrder(root);
        cout << endl;
    }
};

// Main function to test Binary 
int main() {
    BST tree;

    // Inserting nodes into the BST
    tree.insertValue(50);
    tree.insertValue(30);
    tree.insertValue(70);
    tree.insertValue(20);
    tree.insertValue(40);
    tree.insertValue(60);
    tree.insertValue(80);

    // Display the BST in-order traversal
    tree.inOrderTraversal();  

    // Deleting a node with no children (leaf node)
    tree.deleteValue(20);
    tree.inOrderTraversal();  

    // Deleting a node with one child
    tree.deleteValue(30);
    tree.inOrderTraversal();  

    // Deleting a node with two children
    tree.deleteValue(50);
    tree.inOrderTraversal();  

    return 0;
}
