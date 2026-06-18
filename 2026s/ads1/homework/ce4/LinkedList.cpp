#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr), length(0) {}

LinkedList::~LinkedList() {
    LinkedListNode* curr = head;
    while (curr != nullptr) {
        LinkedListNode* next = curr->next;
        delete curr;
        curr = next;
    }
}

void LinkedList::insert(int value) {
    LinkedListNode* node = new LinkedListNode();
    node->data = value;
    node->next = head;
    head = node;
    length++;
}

int LinkedList::get_length() {
    return length;
}

bool LinkedList::search(int value) {
    LinkedListNode* curr = head;
    while (curr != nullptr) {
        if (curr->data == value) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

LinkedListNode* LinkedList::get_head() {
    return head;
}
