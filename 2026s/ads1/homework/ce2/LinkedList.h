#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class LinkedListNode {
public:
    int data;
    LinkedListNode *next;
};

class LinkedList {
private:
    LinkedListNode *head;
    int length;

public:
    LinkedList();
    ~LinkedList();

    void insert(int value);
    bool remove_value(int value);
    int get_length();
    int extract_all(int* out);
    int get_at(int pos);
};

#endif
