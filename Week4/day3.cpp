#include <iostream>
using namespace std;

// Node structure for Binary Tree
class Node {
public:
    int data;
    Node* left;
    Node* right;

    // Constructor
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// BinaryTree class
class BinaryTree {
private:
    Node* root;

    // Helper function to insert a node recursively
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

    // Helper function for in-order traversal (left-root-right)
    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);   
            cout << node->data << " ";  
            inorder(node->right);  
        }
    }

    // Helper function to search for a value in the tree
    bool search(Node* node, int value) {
        if (node == nullptr) {
            return false;
        }

        if (node->data == value) {
            return true;
        } else if (value < node->data) {
            return search(node->left, value);  
        } else {
            return search(node->right, value); 
        }
    }

    // Helper function to find the minimum value node
    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Helper function to delete a node from the tree
    Node* deleteNode(Node* node, int value) {
        if (node == nullptr) {
            return node;
        }

        if (value < node->data) {
            node->left = deleteNode(node->left, value);  // Delete from left subtree
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value); // Delete from right subtree
        } else {
            // Node to be deleted found
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

public:
    BinaryTree() {
        root = nullptr;
    }

    // Insert a value into the binary tree
    void insert(int value) {
        root = insert(root, value);
    }

    // Perform in-order traversal of the tree
    void inorder() {
        inorder(root);
        cout << endl;
    }

    // Search for a value in the binary tree
    bool search(int value) {
        return search(root, value);
    }

    // Delete a node from the tree
    void deleteNode(int value) {
        root = deleteNode(root, value);
    }
};

// Main function to test BinaryTree operations
int main() {
    BinaryTree tree;

    // Inserting nodes into the binary tree
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // Display the tree in-order
    cout << "In-order Traversal: ";
    tree.inorder();  // Output: 20 30 40 50 60 70 80

    // Search for an element
    int searchValue = 40;
    if (tree.search(searchValue)) {
        cout << searchValue << " found in the tree." << endl;
    } else {
        cout << searchValue << " not found in the tree." << endl;
    }

    // Delete a node
    tree.deleteNode(20);
    cout << "After deleting 20, In-order Traversal: ";
    tree.inorder();  // Output: 30 40 50 60 70 80

    tree.deleteNode(70);
    cout << "After deleting 70, In-order Traversal: ";
    tree.inorder();  // Output: 30 40 50 60 80

    return 0;
}
