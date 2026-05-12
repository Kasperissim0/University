#include "HashTable.h"
#include "LinkedList.h"

HashTable::HashTable() {
    tableSize = 5;
    numKeys = 0;
    table = new LinkedList[tableSize];
}

HashTable::~HashTable() {
    delete[] table;
}

int HashTable::hash(int key) {
    return key % tableSize;
}

void HashTable::insert(int key) {
    table[hash(key)].insert(key);
    if (++numKeys > (2 * tableSize))
        increase_hash_table_size();
}

void HashTable::remove(int key) {
    int index = hash(key);
    bool removed = table[index].remove_value(key);
    if (removed) numKeys--;
}

std::vector<int> HashTable::get_all_keys() {
    std::vector<int> keys;
    keys.reserve(numKeys);

    for (int i = 0; i < tableSize; i++) {
        int len = table[i].get_length();
        for (int pos = 0; pos < len; pos++) {
            int v = table[i].get_at(pos);
            if (v != -1)
                keys.push_back(v);
        }
    }
    return keys;
}

void HashTable::increase_hash_table_size() {
    const auto oldKeys = get_all_keys();
    delete[] table; numKeys = 0; table = new LinkedList[tableSize *= 2];
    for (const auto &key : oldKeys) insert(key);
}
