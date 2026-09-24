#include <iostream>
using namespace std;

// Definition for a TreeNode
template<typename T>
struct TreeNode {
    T value;              // Value stored in the node
    TreeNode* left;       // Left child
    TreeNode* right;      // Right child
    TreeNode* next;       // Points to the next node with the same value (in the list)

    TreeNode(T val) : value(val), left(nullptr), right(nullptr), next(nullptr) {}
};

// Definition for a ListNode (header node for nodes with the same value)
template<typename T>
struct ListNode {
    TreeNode<T>* treeNode;  // Points to the first TreeNode with the same value
    ListNode* next;         // Points to the next ListNode (for different values)

    ListNode(TreeNode<T>* tn) : treeNode(tn), next(nullptr) {}
};

// Linked Binary Tree class
template<typename T>
class LinkedBinaryTree {
private:
    TreeNode<T>* root;  // Root of the binary tree
    ListNode<T>* header;  // Head of the list of linked lists (nodes with same value)

public:
    LinkedBinaryTree() : root(nullptr), header(nullptr) {}

    // Function to insert a value into the binary tree
    void insert(T value) {
        root = insertRec(root, value);
    }

    // Function to print the tree (in-order traversal)
    void printTree() {
        printTreeRec(root);
        std::cout << std::endl;
    }

    // Function to print the linked lists of nodes with the same value
    void printLinkedLists() {
        ListNode<T>* temp = header;
        while (temp) {
            std::cout << "Nodes with value " << temp->treeNode->value << ": ";
            TreeNode<T>* node = temp->treeNode;
            while (node) {
                std::cout << node->value << " ";
                node = node->next;
            }
            std::cout << std::endl;
            temp = temp->next;
        }
    }

private:
    // Recursive function to insert a value into the binary tree
    TreeNode<T>* insertRec(TreeNode<T>* node, T value) {
        if (!node) {
            node = new TreeNode<T>(value);
            linkNodeToList(node);
            return node;
        }

        if (value < node->value) {
            node->left = insertRec(node->left, value);
        } else if (value > node->value) {
            node->right = insertRec(node->right, value);
        }

        return node;
    }

    // Function to link a node to a list of nodes with the same value
    void linkNodeToList(TreeNode<T>* node) {
        ListNode<T>* temp = header;
        ListNode<T>* prev = nullptr;

        // Find if a list with the same value already exists
        while (temp && temp->treeNode->value != node->value) {
            prev = temp;
            temp = temp->next;
        }

        // If no such list exists, create a new header for this value
        if (!temp) {
            temp = new ListNode<T>(node);
            if (prev) {
                prev->next = temp;
            } else {
                header = temp;
            }
        } else {
            // Add the node to the existing list of nodes with the same value
            node->next = temp->treeNode;
            temp->treeNode = node;
        }
    }

    // In-order traversal of the binary tree (for testing purposes)
    void printTreeRec(TreeNode<T>* node) {
        if (node) {
            printTreeRec(node->left);
            std::cout << node->value << " ";
            printTreeRec(node->right);
        }
    }
};

// Main function to test the implementation
int main() {
    LinkedBinaryTree<int> tree;

    // Insert values into the tree
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(3);
    tree.insert(8);
    tree.insert(5);

    // Print the binary tree (In-order traversal)
    std::cout << "Binary Tree (In-order Traversal): ";
    tree.printTree();

    // Print the linked lists of nodes with the same value
    std::cout << "Linked Lists of Nodes with Same Value:" << std::endl;
    tree.printLinkedLists();

    // Application Examples (explanations in comments)
    /*
    1. **Efficiently Handling Duplicate Values in a BST**:
       The linked binary tree is useful when we need to store and handle duplicate values efficiently in a binary search tree (BST). This helps in applications like databases and search engines where multiple entries may have the same value.
   
    2. **Multiset (Multi-Value Set) or Multimap**:
       The linked binary tree can be used to implement a **multiset** or **multimap**, where duplicates are allowed. The nodes with the same value are grouped together in linked lists, allowing efficient retrieval and management of duplicate elements.

    3. **Huffman Encoding**:
       In **Huffman encoding**, a binary tree is used to represent the encoding of characters. A linked binary tree can efficiently group nodes with the same frequency (value) to construct the tree for optimal data compression.

    4. **Handling Large Datasets with Duplicates**:
       This data structure is useful when dealing with large datasets (such as sensor data, logs, or any dataset where duplicates are common). By grouping nodes with the same value together, it helps in reducing redundancy while maintaining sorted order for fast access.

    5. **Symbol Table in Compiler Design**:
       In **compiler design**, a linked binary tree can be used to maintain a symbol table, which stores information about variables, functions, and other symbols. Grouping symbols with the same name but different scopes or attributes in the same linked list helps in managing them efficiently.
    */
    
    return 0;
}
