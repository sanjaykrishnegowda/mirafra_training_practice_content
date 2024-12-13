#include <iostream>
#include <algorithm>  // For max function
using namespace std;

// Node structure for AVL Tree
class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;  

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        height = 1;  
    }
};

// AVL Tree class
class AVLTree {
private:
    Node* root;
    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }
    void updateHeight(Node* node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    int getBalanceFactor(Node* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Right rotate subtree rooted with node
    Node* rightRotate(Node* node) {
        Node* leftChild = node->left;
        Node* rightOfLeftChild = leftChild->right;

        // Perform rotation
        leftChild->right = node;
        node->left = rightOfLeftChild;

        // Update heights
        updateHeight(node);
        updateHeight(leftChild);

        return leftChild;  // New root
    }

    // Left rotate subtree rooted with node
    Node* leftRotate(Node* node) {
        Node* rightChild = node->right;
        Node* leftOfRightChild = rightChild->left;

        // Perform rotation
        rightChild->left = node;
        node->right = leftOfRightChild;

        // Update heights
        updateHeight(node);
        updateHeight(rightChild);

        return rightChild;  // New root
    }

    // Left-Right Rotation
    Node* leftRightRotate(Node* node) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right-Left Rotation
    Node* rightLeftRotate(Node* node) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Insert a node into the AVL Tree
    Node* insert(Node* node, int value) {
        if (node == nullptr)
            return new Node(value);  // Create new node if tree is empty

        // Perform normal BST insertion
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        } else {
            // Duplicate values are not allowed in the BST
            return node;
        }

        // Update the height of the current node
        updateHeight(node);

        // Get the balance factor
        int balance = getBalanceFactor(node);

        // If the node is unbalanced, then there are 4 cases to handle

        // Left-Left case (Left Heavy)
        if (balance > 1 && value < node->left->data)
            return rightRotate(node);

        // Right-Right case (Right Heavy)
        if (balance < -1 && value > node->right->data)
            return leftRotate(node);

        // Left-Right case (Left Heavy but Right child is deeper)
        if (balance > 1 && value > node->left->data)
            return leftRightRotate(node);

        // Right-Left case (Right Heavy but Left child is deeper)
        if (balance < -1 && value < node->right->data)
            return rightLeftRotate(node);

        return node;  // Return the (possibly unchanged) node pointer
    }

    // In-order traversal of the AVL tree
    void inOrder(Node* node) {
        if (node == nullptr)
            return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

public:
    // Constructor
    AVLTree() {
        root = nullptr;
    }

    // Insert a value into the AVL tree
    void insertValue(int value) {
        root = insert(root, value);
    }

    // Perform in-order traversal
    void inOrderTraversal() {
        cout << "In-order Traversal: ";
        inOrder(root);
        cout << endl;
    }
};

// Main function to test AVL Tree operations
int main() {
    AVLTree tree;

    // Inserting nodes into the AVL Tree
    tree.insertValue(50);
    tree.insertValue(30);
    tree.insertValue(20);
    tree.insertValue(40);
    tree.insertValue(70);
    tree.insertValue(60);
    tree.insertValue(80);

    // Displaying the AVL tree using In-order Traversal
    tree.inOrderTraversal();  // Output: In-order Traversal: 20 30 40 50 60 70 80

    return 0;
}
