#include <iostream>
#include <algorithm>
using namespace std;

enum Color { RED, BLACK };

// Node structure for Red-Black Tree
class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Color color;

    Node(int value) {
        data = value;
        left = right = parent = nullptr;
        color = RED; // New node is always red
    }
};

// Red-Black Tree class
class RedBlackTree {
private:
    Node* root;

    // Rotate left subtree rooted with node
    Node* leftRotate(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;
        if (rightChild->left != nullptr)
            rightChild->left->parent = node;
        rightChild->parent = node->parent;
        if (node->parent == nullptr)
            root = rightChild;
        else if (node == node->parent->left)
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;
        rightChild->left = node;
        node->parent = rightChild;
        return rightChild;
    }

    // Rotate right subtree rooted with node
    Node* rightRotate(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;
        if (leftChild->right != nullptr)
            leftChild->right->parent = node;
        leftChild->parent = node->parent;
        if (node->parent == nullptr)
            root = leftChild;
        else if (node == node->parent->left)
            node->parent->left = leftChild;
        else
            node->parent->right = leftChild;
        leftChild->right = node;
        node->parent = leftChild;
        return leftChild;
    }

    // Fix violations after insertion
    void fixInsert(Node* node) {
        while (node != root && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                Node* uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    // Case 1: Uncle is red
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        // Case 2: node is right child
                        node = node->parent;
                        leftRotate(node);
                    }
                    // Case 3: node is left child
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotate(node->parent->parent);
                }
            } else {
                Node* uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    // Case 1: Uncle is red
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        // Case 2: node is left child
                        node = node->parent;
                        rightRotate(node);
                    }
                    // Case 3: node is right child
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotate(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    // Insert a node into the Red-Black Tree
    void insertNode(int value) {
        Node* newNode = new Node(value);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (value < x->data)
                x = x->left;
            else
                x = x->right;
        }

        newNode->parent = y;
        if (y == nullptr)
            root = newNode; // Tree was empty
        else if (value < y->data)
            y->left = newNode;
        else
            y->right = newNode;

        // Fix any violations
        fixInsert(newNode);
    }

    // In-order traversal of the Red-Black Tree
    void inOrder(Node* node) {
        if (node == nullptr)
            return;
        inOrder(node->left);
        cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
        inOrder(node->right);
    }

public:
    RedBlackTree() {
        root = nullptr;
    }

    // Function to insert a value into the Red-Black Tree
    void insert(int value) {
        insertNode(value);
    }

    // Perform in-order traversal
    void inOrderTraversal() {
        cout << "In-order Traversal: ";
        inOrder(root);
        cout << endl;
    }
};

// Main function to test Red-Black Tree
int main() {
    RedBlackTree tree;

    // Inserting nodes into the Red-Black Tree
    tree.insert(20);
    tree.insert(15);
    tree.insert(25);
    tree.insert(10);
    tree.insert(5);
    tree.insert(30);

    // Displaying the Red-Black tree using In-order Traversal
    tree.inOrderTraversal();

    return 0;
}
