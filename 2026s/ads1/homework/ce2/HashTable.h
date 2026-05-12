#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinkedList.h"
#include <vector>

class HashTable {
private:
    LinkedList* table;
    int tableSize;
    int numKeys;

public:
    HashTable(); 
    ~HashTable();

    int hash(int key);
    void insert(int key);

    void remove(int key);

    std::vector<int> get_all_keys();

    void increase_hash_table_size();
};


#endif
