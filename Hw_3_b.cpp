#include <iostream>
#include <algorithm> // For max function
using namespace std;

// Element class to represent keys in the BST
template <class T>
class Element {
public:
    T key; 
};


template <class T>
class BST;

// BSTNode class representing a single node in the BST
template <class T>
class BSTNode {
    friend class BST<T>; // Allows BST to access private members of BSTNode
public:
    BSTNode() : LeftChild(nullptr), RightChild(nullptr) {}
    BSTNode(const T& x) : data(x), LeftChild(nullptr), RightChild(nullptr) {}

private:
    T data;               
    BSTNode* LeftChild;   
    BSTNode* RightChild;  
};

// BST class representing the Binary Search Tree
template <class T>
class BST {
public:
    BST() : root(nullptr) {}

    // Basic tree operations
    void Insert(const T& x);
    BSTNode<T>* Search(const T& x);

    // Functions to implement
    int height();        // Returns the height of the entire tree
    int weight();        // Returns the total number of nodes in the tree
    int heightBF();      // Returns the balance factor (height difference) of the root
    int weightBF();      // Returns the weight balance factor (node count difference) of the root

private:
    BSTNode<T>* root;    // Pointer to the root node

    // Helper functions
    int height(BSTNode<T>* node);       // Recursive function to calculate height of a subtree
    int weight(BSTNode<T>* node);       // Recursive function to calculate weight of a subtree
    int heightDifference(BSTNode<T>* node); // Calculates height difference for a given node
    int weightDifference(BSTNode<T>* node); // Calculates weight difference for a given node
};

// Insert function to add a new element
template <class T>
void BST<T>::Insert(const T& x) {
    BSTNode<T>* p = root, *pp = nullptr;
    while (p) {
        pp = p;
        if (x < p->data) 
            p = p->LeftChild;
        else if (x > p->data) 
            p = p->RightChild;
        else 
            return; 
    }
    BSTNode<T>* newNode = new BSTNode<T>(x);
    if (!root) {
        root = newNode; 
    } else {
        if (x < pp->data)
            pp->LeftChild = newNode;
        else
            pp->RightChild = newNode;
    }
}

// Search function to find a key
template <class T>
BSTNode<T>* BST<T>::Search(const T& x) {
    BSTNode<T>* current = root;
    while (current) {
        if (x == current->data)
            return current;
        else if (x < current->data)
            current = current->LeftChild;
        else
            current = current->RightChild;
    }
    return nullptr; // Key not found
}

// Recursive function to calculate the height of a subtree
template <class T>
int BST<T>::height(BSTNode<T>* node) {
    if (!node) return 0; 
    int leftHeight = height(node->LeftChild);
    int rightHeight = height(node->RightChild);
    return max(leftHeight, rightHeight) + 1; // Add 1 for the current node
}

// Public height function for the whole tree
template <class T>
int BST<T>::height() {
    return height(root);
}

// Recursive function to calculate the weight (number of nodes) of a subtree
template <class T>
int BST<T>::weight(BSTNode<T>* node) {
    if (!node) return 0; // Base case: Empty subtree has weight 0
    return weight(node->LeftChild) + weight(node->RightChild) + 1;
}

// Public weight function for the whole tree
template <class T>
int BST<T>::weight() {
    return weight(root);
}

// Function to calculate height difference for a given node
template <class T>
int BST<T>::heightDifference(BSTNode<T>* node) {
    if (!node) return 0;
    return height(node->LeftChild) - height(node->RightChild);
}

// Public function to get the height balance factor of the root
template <class T>
int BST<T>::heightBF() {
    return heightDifference(root);
}

// Function to calculate weight difference for a given node
template <class T>
int BST<T>::weightDifference(BSTNode<T>* node) {
    if (!node) return 0;
    return weight(node->LeftChild) - weight(node->RightChild);
}

// Public function to get the weight balance factor of the root
template <class T>
int BST<T>::weightBF() {
    return weightDifference(root);
}



