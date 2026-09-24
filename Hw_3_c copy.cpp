#include <iostream>
using namespace std;

template <class T>
class Element {
public:
    T key;
};

template <class T>
class BSTNode {
public:
    BSTNode() : LeftChild(nullptr), RightChild(nullptr) {}
    BSTNode(const Element<T>& x) : data(x.key), LeftChild(nullptr), RightChild(nullptr) {}
    T data;
    BSTNode* LeftChild;
    BSTNode* RightChild;
};

template <class T>
class BST {
public:
    BST() : root(nullptr) {}
    
    // Tree operations
    BSTNode<T>* Search(const Element<T>& x);
    BSTNode<T>* Search(BSTNode<T>* b, const Element<T>& x);
    BSTNode<T>* IterSearch(const Element<T>& x);
    void Insert(const Element<T>& x);
    void Delete(const Element<T>& x);
    void Reverse();
    void InOrderTraversal() { InOrderTraversal(root); }
    void InOrderTraversal(BSTNode<T>* node);
    T Get(const Element<T>& x); // Add the Get function
    
private:
    BSTNode<T>* root;
    void Reverse(BSTNode<T>* node);
    BSTNode<T>* Delete(BSTNode<T>* node, const Element<T>& x);  // Declaration of helper delete function
};

// Recursive Search
template <class T>
BSTNode<T>* BST<T>::Search(const Element<T>& x) {
    return Search(root, x);
}

template <class T>
BSTNode<T>* BST<T>::Search(BSTNode<T>* b, const Element<T>& x) {
    if (!b) return nullptr;
    if (x.key == b->data) return b;
    if (x.key < b->data)
        return Search(b->LeftChild, x);
    return Search(b->RightChild, x);
}

// Iterative Search
template <class T>
BSTNode<T>* BST<T>::IterSearch(const Element<T>& x) {
    for (BSTNode<T>* t = root; t;) {
        if (x.key == t->data) return t;
        if (x.key < t->data)
            t = t->LeftChild;
        else
            t = t->RightChild;
    }
    return nullptr;
}

// Insert a node
template <class T>
void BST<T>::Insert(const Element<T>& x) {
    BSTNode<T>* p = root, *pp = nullptr;
    while (p) {
        pp = p;
        if (x.key > p->data)  // Reversed order: right child is smaller than parent
            p = p->LeftChild;
        else if (x.key < p->data)
            p = p->RightChild;
        else
            return; // No duplicates allowed
    }
    p = new BSTNode<T>(x);
    if (root) {
        if (x.key > pp->data)
            pp->LeftChild = p;
        else
            pp->RightChild = p;
    } else {
        root = p;
    }
}

// Delete a node (Simplified for this example; you may need to adjust for full delete logic)
template <class T>
void BST<T>::Delete(const Element<T>& x) {
    root = Delete(root, x);
}

template <class T>
BSTNode<T>* BST<T>::Delete(BSTNode<T>* node, const Element<T>& x) {
    if (!node) return node;

    // Search for the node to delete
    if (x.key < node->data)
        node->LeftChild = Delete(node->LeftChild, x);
    else if (x.key > node->data)
        node->RightChild = Delete(node->RightChild, x);
    else {
        // Node to be deleted found
        if (!node->LeftChild) {
            BSTNode<T>* temp = node->RightChild;
            delete node;
            return temp;
        }
        else if (!node->RightChild) {
            BSTNode<T>* temp = node->LeftChild;
            delete node;
            return temp;
        }

        // Node with two children, get the inorder successor
        BSTNode<T>* temp = node->RightChild;
        while (temp && temp->LeftChild) temp = temp->LeftChild;
        node->data = temp->data;
        node->RightChild = Delete(node->RightChild, temp->data);
    }
    return node;
}

// Reverse the BST
template <class T>
void BST<T>::Reverse() {
    Reverse(root);
}

template <class T>
void BST<T>::Reverse(BSTNode<T>* node) {
    if (!node) return;

    // Swap the left and right children
    BSTNode<T>* temp = node->LeftChild;
    node->LeftChild = node->RightChild;
    node->RightChild = temp;

    // Recursively reverse left and right subtrees
    Reverse(node->LeftChild);
    Reverse(node->RightChild);
}

// In-Order Traversal
template <class T>
void BST<T>::InOrderTraversal(BSTNode<T>* node) {
    if (!node) return;
    InOrderTraversal(node->LeftChild);
    cout << node->data << " ";
    InOrderTraversal(node->RightChild);
}

// Get function
template <class T>
T BST<T>::Get(const Element<T>& x) {
    BSTNode<T>* node = Search(x);  // Search for the node containing the value
    if (node) {
        return node->data;  // Return the data of the found node
    } else {
        cout << "Value not found!" << endl;
        return T();  // Return a default value of type T if not found
    }
}

