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
    int get_length();
    bool search(int value);
    LinkedListNode* get_head();
};

#endif
