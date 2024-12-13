#include <iostream>
using namespace std;

// Node structure for Binary Tree
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

// Binary Tree class
class BinaryTree {
private:
    Node* root;

    // Pre-order Traversal (Root, Left, Right)
    void preOrder(Node* node) {
        if (node != nullptr) {
            cout << node->data << " ";  
            preOrder(node->left);       
            preOrder(node->right);      
        }
    }

    // In-order Traversal (Left, Root, Right)
    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);       
            cout << node->data << " ";  
            inOrder(node->right);      
        }
    }

    // Post-order Traversal (Left, Right, Root)
    void postOrder(Node* node) {
        if (node != nullptr) {
            postOrder(node->left);     
            postOrder(node->right);    
            cout << node->data << " ";  
        }
    }

public:
    // Constructor
    BinaryTree() {
        root = nullptr;
    }

    // Insert a value in the Binary Tree
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);  
        } else {
            node->right = insert(node->right, value); 
        }
        return node;
    }

    // Wrapper methods for traversals
    void preOrderTraversal() {
        cout << "Pre-order Traversal: ";
        preOrder(root);
        cout << endl;
    }

    void inOrderTraversal() {
        cout << "In-order Traversal: ";
        inOrder(root);
        cout << endl;
    }

    void postOrderTraversal() {
        cout << "Post-order Traversal: ";
        postOrder(root);
        cout << endl;
    }

    // Method to insert a value into the tree
    void insertValue(int value) {
        root = insert(root, value);
    }
};

// Main function to test Binary Tree and traversals
int main() {
    BinaryTree tree;

    // Insert nodes into the tree
    tree.insertValue(50);
    tree.insertValue(30);
    tree.insertValue(70);
    tree.insertValue(20);
    tree.insertValue(40);
    tree.insertValue(60);
    tree.insertValue(80);

    // Display the tree traversals
    tree.preOrderTraversal();   
    tree.inOrderTraversal();    
    tree.postOrderTraversal(); 

    return 0;
}
