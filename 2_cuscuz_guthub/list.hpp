#include <cstddef>
#include <cassert>
#include <string>

using namespace std;

class LinkedList {
    // INTERNAL STRUCTURE
    struct Node {
        string value;
        Node *prev;
        Node *next;
        Node(string v, Node* p = nullptr, Node* n = nullptr)
            : value(v), prev(p), next(n) {}
    };

    Node *head;
    Node *tail;
    size_t m_size;

    // Private helper to retrieve node at a given index
    Node* getNode(size_t pos) {
        if (pos >= m_size) {
            return nullptr;
        }
        Node* current = head;
        for (size_t i = 0; i < pos; ++i) {
            current = current->next;
        }
        return current;
    }

public:
    LinkedList();
    ~LinkedList();

    size_t size();
    string at(size_t pos);
    void insert(size_t pos, string value);
    void push_back(string value);
    void remove(size_t pos);
};


inline LinkedList::LinkedList() : head(nullptr), tail(nullptr), m_size(0) {}

inline LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

inline size_t LinkedList::size() {
    return m_size;
}

inline string LinkedList::at(size_t pos) {
    assert(pos < m_size);
    return getNode(pos)->value;
}

inline void LinkedList::insert(size_t pos, string value) {
    assert(pos <= m_size);

    if (pos == m_size) {
        push_back(value);
    } else if (pos == 0) {
        Node* newNode = new Node(value, nullptr, head);
        if (head != nullptr) {
            head->prev = newNode;
        }
        head = newNode;
        if (tail == nullptr) { 
            tail = head;
        }
        m_size++;
    } else {
        // Insert in the middle
        Node* current = getNode(pos);
        Node* prevNode = current->prev;
        Node* newNode = new Node(value, prevNode, current);

        if (prevNode != nullptr) {
            prevNode->next = newNode;
        }
        current->prev = newNode;
        m_size++;
    }
}

inline void LinkedList::push_back(string value) {
    Node* newNode = new Node(value, tail, nullptr);
    if (tail != nullptr) {
        tail->next = newNode;
    }
    tail = newNode;
    if (head == nullptr) { // Empty list
        head = tail;
    }
    m_size++;
}

inline void LinkedList::remove(size_t pos) {
    assert(pos < m_size);
    Node* toDelete = getNode(pos);

    Node* prevNode = toDelete->prev;
    Node* nextNode = toDelete->next;

    if (prevNode != nullptr) {
        prevNode->next = nextNode;
    } else { // Removing head
        head = nextNode;
    }

    if (nextNode != nullptr) {
        nextNode->prev = prevNode;
    } else { // Removing tail
        tail = prevNode;
    }

    delete toDelete;
    m_size--;
}


// STACK CLASS
class Stack {
    // INTERNAL STORAGE
    LinkedList list;
public:
    size_t size();
    void push(string value);
    void pop();
    string top();
};


// STACK IMPLEMENTATION
inline size_t Stack::size() {
    return list.size();
}

inline void Stack::push(string value) {
    list.insert(0, value); // Add to the top
}

inline void Stack::pop() {
    assert(list.size() > 0);
    list.remove(0); // Remove from the top
}

inline string Stack::top() {
    assert(list.size() > 0);
    return list.at(0); // Peek at the top
}


// QUEUE CLASS
class Queue {
    // INTERNAL STORAGE
    LinkedList list;
public:
    size_t size();
    void push(string value);
    void pop();
    string front();
};


// QUEUE IMPLEMENTATION
inline size_t Queue::size() {
    return list.size();
}

inline void Queue::push(string value) {
    list.push_back(value); // Add to the tail
}

inline void Queue::pop() {
    assert(list.size() > 0);
    list.remove(0); // Remove from the front
}

inline string Queue::front() {
    assert(list.size() > 0);
    return list.at(0); // Peek at the front
}