// ok so fundamentally we want a struct which is the node
// and a class which is the "holder" of the nodes
// the class helps us define a head and a next
// and it has 2 functions, print and push_front

#include <iostream>

struct Node {
    int value;
    Node* next;
}; // ; because its a statement? idk

class LinkedList {
    private:
        Node* head;
    public:
        // Node* next; I did not need this
        void print();
        void push_front(int value);
        LinkedList();
        ~LinkedList();
};

LinkedList::LinkedList() {
    head = nullptr;
    // next = nullptr; I did not need this
}

void LinkedList::push_front(int value) {
    Node* n1 = new Node; // new node, point to old head, move head to new node
    n1->next = head;
    n1->value = value;
    head = n1; // this is correct
}

void LinkedList::print() {
    Node* curr = head; // need curr so I don't destroy the list
    while (curr != nullptr) {
        std::cout << curr->value << "\n";
        curr = curr->next;
    }
}

LinkedList::~LinkedList() {
    while (head != nullptr) {
        Node* to = head->next;
        delete head;
        head = to; // this was correct
    }
}



