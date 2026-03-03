#include <iostream>

struct Node {
    int data;
    Node* next;
};

class LinkedList {
    private:
        Node* head;
    public:
        LinkedList();
        void push_front(int value);
        void print();
        ~LinkedList();
};

LinkedList::LinkedList() {
    head = nullptr;
}

void LinkedList::push_front(int value) {
    Node* n1 = new Node;
    n1->data = value;
    n1->next = head;
    head = n1;
}

void LinkedList::print() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << "\n";
        current = current->next;
    }
}

LinkedList::~LinkedList() {
    while (head != nullptr) {
        Node* nextNode = head->next;
        delete head;
        head = nextNode;
    }
}