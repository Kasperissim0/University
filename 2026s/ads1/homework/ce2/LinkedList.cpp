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

bool LinkedList::remove_value(int value) {
    if (!head) return false;

    if (head->data == value) {
        LinkedListNode* temp = head;
        head = head->next;
        delete temp;
        length--;
        return true;
    }

    LinkedListNode* curr = head->next;
    LinkedListNode* prev = head;

    while (curr) {
        if (curr->data == value) {
            prev->next = curr->next;
            delete curr;
            length--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }

    return false;
}

int LinkedList::get_length() {
    return length;
}

int LinkedList::extract_all(int* out) {
    LinkedListNode* curr = head;
    int i = 0;
    while (curr) {
        out[i++] = curr->data;
        curr = curr->next;
    }
    return i;
}

int LinkedList::get_at(int pos) {
    LinkedListNode* curr = head;
    int index = 0;
    while (curr) {
        if (index == pos) return curr->data;
        curr = curr->next;
        index++;
    }
    return -1;
}
