#include <iostream>

using namespace std;

template <class T> class List;

template <class T>
class ListNode {
    friend class List <T>;
private:
    T data;
    ListNode <T>* link;
public:
    ListNode(T k) : data(k), link(nullptr) {}
};

template <class T>
class List {
public:
    List() { first = last = nullptr; }
    void Attach(T k);
    bool appearM(T k, int m);         // Returns true if k appears m or more times
    int replaceALL(T a1, T a2);       // Replaces every occurrence of a1 with a2
    void rotate(char direction, int k); // Rotates the list by k positions (R = right, L = left)
    List<T> subList(int i, int j);    // Returns a sublist from index i to j (inclusive)
    void print() const;               // Prints the list for testing purposes

private:
    ListNode<T>* first;
    ListNode<T>* last;
};

template <class Type>
void List<Type>::Attach(Type k) {
    ListNode<Type>* newnode = new ListNode<Type>(k);
    if (first == nullptr)
        first = last = newnode;
    else {
        last->link = newnode;
        last = newnode;
    }
}
// Return TRUE if the first argument k appears in this list mor more times, 
//FALSE otherwise.
template <class T>
bool List<T>::appearM(T k, int m) {
    int count = 0;
    ListNode<T>* temp = first;
    while (temp != nullptr) {
        if (temp->data == k) {
            count++;
        }
        temp = temp->link;
    }
    return count >= m;
}

template <class T>
int List<T>::replaceALL(T a1, T a2) {
    int replacements = 0;
    ListNode<T>* temp = first;
    while (temp != nullptr) {
        if (temp->data == a1) {
            temp->data = a2;
            replacements++;
        }
        temp = temp->link;
    }
    return replacements;
}

template <class T>
void List<T>::rotate(char direction, int k) {
    if (first == nullptr || k == 0)
        return;

    // Find the length of the list
    ListNode<T>* temp = first;
    int length = 0;
    while (temp != nullptr) {
        length++;
        temp = temp->link;
    }

    k = k % length;  // In case k is larger than the length
    if (k == 0)
        return;

    // If rotating to the right, adjust k for a left rotation
    if (direction == 'R') {
        k = length - k;
    }

    // Find the (k-1)th node
    ListNode<T>* prev = nullptr;
    ListNode<T>* current = first;
    for (int i = 0; i < k; ++i) {
        prev = current;
        current = current->link;
    }

    // Disconnect the list into two parts
    ListNode<T>* newHead = current;
    if (prev) {
        prev->link = nullptr;
    }

    // Find the last node
    ListNode<T>* lastNode = newHead;
    while (lastNode->link != nullptr) {
        lastNode = lastNode->link;
    }

    // Connect the last node to the old head
    lastNode->link = first;

    // Set the new head
    first = newHead;
}

template <class T>
List<T> List<T>::subList(int i, int j) {
    List<T> sublist;
    ListNode<T>* temp = first;
    int index = 0;
    
    while (temp != nullptr) {
        if (index >= i && index <= j) {
            sublist.Attach(temp->data);
        }
        temp = temp->link;
        index++;
    }
    return sublist;
}

template <class T>
void List<T>::print() const {
    ListNode<T>* temp = first;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->link;
    }
    cout << endl;
}

int main() {
    List<int> list;

    // Attach elements to the list
    list.Attach(1);
    list.Attach(2);
    list.Attach(3);
    list.Attach(2);
    list.Attach(4);
    list.Attach(2);

    // Test appearM
    cout << "Appear M (2, 3): " << (list.appearM(2, 3) ? "TRUE" : "FALSE") << endl; // TRUE
    cout << "Appear M (3, 3): " << (list.appearM(3, 3) ? "TRUE" : "FALSE") << endl; // FALSE

    // Test replaceALL
    cout << "Replaced: " << list.replaceALL(2, 5) << " times" << endl; // Replaces all 2s with 5s
    list.print();  // Output: 1 5 3 5 4 5

    // Test rotate
    list.rotate('R', 2);  // Rotate right by 2 positions
    list.print();  // Output after right rotation: 4 5 1 5 3 5

    // Test subList
    List<int> sub = list.subList(1, 3);
    sub.print();  // Output: 5 1 5

    return 0;
}
