#include <iostream>
#include <queue>
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

    // Wrapper method to insert values into the tree
    void insertValue(int value) {
        root = insert(root, value);
    }

    // Level-order Traversal using Queue
    void levelOrderTraversal() {
        if (root == nullptr) {
            cout << "The tree is empty." << endl;
            return;
        }

        queue<Node*> q;   
        q.push(root);      

        while (!q.empty()) {
            Node* currentNode = q.front();  
            q.pop();  

            cout << currentNode->data << " ";  

            if (currentNode->left != nullptr) {
                q.push(currentNode->left);
            }

            // Add the right child to the queue if it exists
            if (currentNode->right != nullptr) {
                q.push(currentNode->right);
            }
        }
        cout << endl;
    }
};

// Main function to test Binary Tree and Level-order Traversal
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

    // Display the Level-order traversal
    cout << "Level-order Traversal: ";
    tree.levelOrderTraversal();  

    return 0;
}
