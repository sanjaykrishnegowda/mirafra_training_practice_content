
//B trees code implementation insertion deletion traverse.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// A B-tree node
class BTreeNode {
public:
    vector<int> keys; // Store keys in the node
    vector<BTreeNode*> children; // Store child pointers
    bool isLeaf; // Is true if node is leaf, else false
    int t; // Minimum degree (defines the range for number of keys)

    BTreeNode(int _t, bool _isLeaf); // Constructor

    // Function to insert a new key in this node
    void insertNonFull(int key);

    // Function to split the child node
    void splitChild(int i, BTreeNode* y);

    // Function to traverse the tree
    void traverse();

    // Function to search a key in the subtree rooted with this node
    BTreeNode* search(int key);

    // Function to delete a key in the subtree rooted with this node
    void deleteKey(int key);

    // Helper functions for deleting a key
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPredecessor(int idx);
    int getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);

    friend class BTree;
};

// A B-tree
class BTree {
public:
    BTreeNode* root; // Pointer to root node
    int t; // Minimum degree

    // Constructor
    BTree(int _t);

    // Function to insert a new key in the B-tree
    void insert(int key);

    // Function to delete a key in the B-tree
    void deleteKey(int key);

    // Function to traverse the B-tree
    void traverse();

    // Function to search a key in the B-tree
    BTreeNode* search(int key);
};

// Constructor for BTreeNode
BTreeNode::BTreeNode(int _t, bool _isLeaf) {
    t = _t;
    isLeaf = _isLeaf;
    keys = vector<int>(2 * t - 1);
    children = vector<BTreeNode*>(2 * t, nullptr);
}

// Insert a key into a non-full node
void BTreeNode::insertNonFull(int key) {
    int i = keys.size() - 1;

    if (isLeaf) {
        // Find location to insert the key
        while (i >= 0 && keys[i] > key) {
            i--;
        }
        keys.insert(keys.begin() + i + 1, key);
    } else {
        // Find child to insert into
        while (i >= 0 && keys[i] > key) {
            i--;
        }
        i++;

        if (children[i]->keys.size() == 2 * t - 1) {
            // Split the child if it's full
            splitChild(i, children[i]);
            if (keys[i] < key) {
                i++;
            }
        }
        children[i]->insertNonFull(key);
    }
}

// Split the child node
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
    int midKey = y->keys[t - 1];

    // Move the mid key to the parent
    keys.insert(keys.begin() + i, midKey);

    // Move the children of y
    for (int j = 0; j < t - 1; j++) {
        z->keys.push_back(y->keys[t + j]);
    }
    for (int j = 0; j < t; j++) {
        z->children.push_back(y->children[t + j]);
    }

    // Resize y to remove the split keys and children
    y->keys.resize(t - 1);
    y->children.resize(t);

    // Insert z as a child of this node
    children.insert(children.begin() + i + 1, z);
}

// Traverse the B-tree
void BTreeNode::traverse() {
    int i = 0;
    for (i = 0; i < keys.size(); i++) {
        if (!isLeaf) {
            children[i]->traverse();
        }
        cout << keys[i] << " ";
    }
    if (!isLeaf) {
        children[i]->traverse();
    }
}

// Search for a key in the subtree
BTreeNode* BTreeNode::search(int key) {
    int i = 0;
    while (i < keys.size() && key > keys[i]) {
        i++;
    }
    if (i < keys.size() && keys[i] == key) {
        return this;
    }
    if (isLeaf) {
        return nullptr;
    }
    return children[i]->search(key);
}

// Delete a key from the node
void BTreeNode::deleteKey(int key) {
    int idx = -1;
    for (int i = 0; i < keys.size(); i++) {
        if (keys[i] == key) {
            idx = i;
            break;
        }
    }

    if (idx != -1) {
        // Case 1: Key is in a leaf node
        if (isLeaf) {
            removeFromLeaf(idx);
        }
        // Case 2: Key is in a non-leaf node
        else {
            removeFromNonLeaf(idx);
        }
    } else {
        // Key is not in this node, search in child
        int i = 0;
        while (i < keys.size() && key > keys[i]) {
            i++;
        }

        if (children[i]->keys.size() < t) {
            fill(i);
        }

        if (children[i]->keys.size() >= t) {
            children[i]->deleteKey(key);
        } else {
            merge(i);
            children[i]->deleteKey(key);
        }
    }
}

// Remove the key from a leaf node
void BTreeNode::removeFromLeaf(int idx) {
    keys.erase(keys.begin() + idx);
}

// Remove the key from a non-leaf node
void BTreeNode::removeFromNonLeaf(int idx) {
    int key = keys[idx];

    // Case 1: Predecessor is in the left child
    if (children[idx]->keys.size() >= t) {
        int pred = getPredecessor(idx);
        keys[idx] = pred;
        children[idx]->deleteKey(pred);
    }
    // Case 2: Successor is in the right child
    else if (children[idx + 1]->keys.size() >= t) {
        int succ = getSuccessor(idx);
        keys[idx] = succ;
        children[idx + 1]->deleteKey(succ);
    }
    // Case 3: Both children have less than t keys, merge them
    else {
        merge(idx);
        children[idx]->deleteKey(key);
    }
}

// Get the predecessor of the key in the left child
int BTreeNode::getPredecessor(int idx) {
    BTreeNode* cur = children[idx];
    while (!cur->isLeaf) {
        cur = cur->children[cur->keys.size()];
    }
    return cur->keys[cur->keys.size() - 1];
}

// Get the successor of the key in the right child
int BTreeNode::getSuccessor(int idx) {
    BTreeNode* cur = children[idx + 1];
    while (!cur->isLeaf) {
        cur = cur->children[0];
    }
    return cur->keys[0];
}

// Fill the child node if it has less than t keys
void BTreeNode::fill(int idx) {
    if (idx > 0 && children[idx - 1]->keys.size() >= t) {
        borrowFromPrev(idx);
    } else if (idx < keys.size() && children[idx + 1]->keys.size() >= t) {
        borrowFromNext(idx);
    } else {
        if (idx < keys.size()) {
            merge(idx);
        } else {
            merge(idx - 1);
        }
    }
}

// Borrow a key from the previous sibling
void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx - 1];

    child->keys.insert(child->keys.begin(), keys[idx - 1]);
    keys[idx - 1] = sibling->keys[sibling->keys.size() - 1];
    sibling->keys.pop_back();

    if (!child->isLeaf) {
        child->children.insert(child->children.begin(), sibling->children[sibling->children.size() - 1]);
        sibling->children.pop_back();
    }
}

// Borrow a key from the next sibling
void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);
    keys[idx] = sibling->keys[0];
    sibling->keys.erase(sibling->keys.begin());

    if (!child->isLeaf) {
        child->children.push_back(sibling->children[0]);
        sibling->children.erase(sibling->children.begin());
    }
}

// Merge the child node with a sibling
void BTreeNode::merge(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);
    child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());

    if (!child->isLeaf) {
        child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());
    }

    keys.erase(keys.begin() + idx);
    children.erase(children.begin() + idx + 1);
}

// Constructor for BTree
BTree::BTree(int _t) {
    root = new BTreeNode(_t, true);
    t = _t;
}

// Insert a key into the B-tree
void BTree::insert(int key) {
    if (root->keys.size() == 2 * t - 1) {
        // If root is full, split it
        BTreeNode* s = new BTreeNode(t, false);
        s->children[0] = root;
        s->splitChild(0, root);
        root = s;
    }
    root->insertNonFull(key);
}

// Delete a key from the B-tree
void BTree::deleteKey(int key) {
    if (root == nullptr) {
        cout << "The tree is empty!" << endl;
        return;
    }
    root->deleteKey(key);

    // If the root node has no keys, make the first child the new root
    if (root->keys.size() == 0) {
        BTreeNode* oldRoot = root;
        if (root->isLeaf) {
            root = nullptr;
        } else {
            root = root->children[0];
        }
        delete oldRoot;
    }
}

// Traverse the B-tree
void BTree::traverse() {
    if (root != nullptr) {
        root->traverse();
    }
    cout << endl;
}

// Search for a key in the B-tree
BTreeNode* BTree::search(int key) {
    return root->search(key);
}

// Main function to test B-tree implementation
int main() {
    BTree tree(3); // Create a B-tree with minimum degree 3

    // Insert keys into the B-tree
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);
    tree.insert(7);
    tree.insert(17);

    // Traverse the B-tree
    cout << "B-tree traversal: ";
    tree.traverse();

    // Delete key from the B-tree
    tree.deleteKey(6);
    cout << "B-tree traversal after deleting 6: ";
    tree.traverse();

    tree.deleteKey(20);
    cout << "B-tree traversal after deleting 20: ";
    tree.traverse();

    return 0;
}
