#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Custom Stack class definition
template <typename KeyType>
class Stack {
private:
    vector<KeyType> s;

public:
    // Push an element onto the stack
    void push(const KeyType& x) {
        s.push_back(x);
    }

    // Pop the top element from the stack
    void pop() {
        if (!s.empty()) {
            s.pop_back();
        }
    }

    // Return the top element of the stack
    KeyType top() const {
        return s.back();
    }

    // Check if the stack is empty
    bool empty() const {
        return s.empty();
    }

    // Move an element to the top of the stack
    void moveToTop(const KeyType& x) {
        auto it = find(s.begin(), s.end(), x);
        if (it != s.end()) {
            // Remove the element
            s.erase(it);
            // Push it back to the top of the stack
            s.push_back(x);
        }
    }

    // Display the elements of the stack
    void display() const {
        for (const auto& elem : s) {
            cout << elem << " ";
        }
        cout << endl;
    }
};

// Custom Queue class definition
template <typename KeyType>
class Queue {
private:
    vector<KeyType> q;

public:
    // Enqueue an element to the queue
    void enqueue(const KeyType& x) {
        q.push_back(x);
    }

    // Dequeue an element from the queue
    void dequeue() {
        if (!q.empty()) {
            q.erase(q.begin());
        }
    }

    // Return the front element of the queue
    KeyType front() const {
        return q.front();
    }

    // Check if the queue is empty
    bool empty() const {
        return q.empty();
    }

    // Move an element to the front of the queue
    void moveToFront(const KeyType& x) {
        auto it = find(q.begin(), q.end(), x);
        if (it != q.end()) {
            // Remove the element
            q.erase(it);
            // Insert it at the front
            q.insert(q.begin(), x);
        }
    }

    // Move an element to the rear of the queue
    void moveToRear(const KeyType& x) {
        auto it = find(q.begin(), q.end(), x);
        if (it != q.end()) {
            // Remove the element
            q.erase(it);
            // Insert it at the rear
            q.push_back(x);
        }
    }

    // Display the elements of the queue
    void display() const {
        for (const auto& elem : q) {
            cout << elem << " ";
        }
        cout << endl;
    }
};

