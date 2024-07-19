/*  database.hpp
 * 
 *  Author: Rodrigo Arce Diaz
 *   
 * 
 * Last Update: July 18, 2024
 * 
 */

#ifndef _DATABASE_HPP_
#define _DATABASE_HPP_

#include <unordered_map>
#include <ostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include "playerCard.hpp"

template<typename K, typename V>
class Hashnode{
    public:

    K key;
    V value;
    Hashnode* next;


    Hashnode(const K& key, const V& value) : key(key), value(value), next(nullptr) {};

};

template<typename K, typename V>
class Database {

    private:
        std::vector<Hashnode<K, V>*> hashmap;
        int capacity;
        int size;

    int hashFunction(const K& key) const;

    public:
        Database(int capacity = 10);

        ~Database();

        void insert(const K& key, const V& value);

        void remove(const K& key);

        V search(const K& key) const;

        bool contains(const K& key) const;

        int getSize() const;

        bool isEmpty() const;

        void printUsers(std::ostream& os) const;

};


template <typename K, typename V>
Database<K, V>::Database(int capacity) : capacity(capacity), size(0) {
    hashmap.resize(capacity, nullptr);
}

template <typename K, typename V>
Database<K, V>::~Database() {
    for (int i = 0; i < capacity; ++i) {
        Hashnode<K, V>* entry = hashmap[i];
        while (entry != nullptr) {
            Hashnode<K, V>* prev = entry;
            entry = entry->next;
            delete prev;
        }
        hashmap[i] = nullptr;
    }
}

template <typename K, typename V>
int Database<K, V>::hashFunction(const K& key) const {
    return std::hash<K>{}(key) % capacity;
}

template <typename K, typename V>
void Database<K, V>::insert(const K& key, const V& value) {
    int hashIndex = hashFunction(key);
    Hashnode<K, V>* prev = nullptr;
    Hashnode<K, V>* entry = hashmap[hashIndex];

    while (entry != nullptr && entry->key != key) {
        prev = entry;
        entry = entry->next;
    }

    if (entry == nullptr) {
        entry = new Hashnode<K, V>(key, value);
        if (prev == nullptr) {
            hashmap[hashIndex] = entry;
        } else {
            prev->next = entry;
        }
        ++size;
    } else {
        entry->value = value;
    }
}

template <typename K, typename V>
void Database<K, V>::remove(const K& key) {
    int hashIndex = hashFunction(key);
    Hashnode<K, V>* prev = nullptr;
    Hashnode<K, V>* entry = hashmap[hashIndex];

    while (entry != nullptr && entry->key != key) {
        prev = entry;
        entry = entry->next;
    }

    if (entry == nullptr) {
        return; // Key not found
    } else {
        if (prev == nullptr) {
            hashmap[hashIndex] = entry->next;
        } else {
            prev->next = entry->next;
        }
        delete entry;
        --size;
    }
}

template <typename K, typename V>
V Database<K, V>::search(const K& key) const {
    int hashIndex = hashFunction(key);
    Hashnode<K, V>* entry = hashmap[hashIndex];

    while (entry != nullptr) {
        if (entry->key == key) {
            return entry->value;
        }
        entry = entry->next;
    }

    throw std::runtime_error("Key not found");
}

template <typename K, typename V>
bool Database<K, V>::contains(const K& key) const {
    int hashIndex = hashFunction(key);
    Hashnode<K, V>* entry = hashmap[hashIndex];

    while (entry != nullptr) {
        if (entry->key == key) {
            return true;
        }
        entry = entry->next;
    }

    return false;
}

template <typename K, typename V>
int Database<K, V>::getSize() const {
    return size;
}

template <typename K, typename V>
bool Database<K, V>::isEmpty() const {
    return size == 0;
}

template <typename K, typename V>
void Database<K, V>::printUsers(std::ostream& os) const {
    for (int i = 0; i < capacity; ++i) {
        Hashnode<K, V>* entry = hashmap[i];
        while (entry != nullptr) {
            os << "Username: " << entry->key << "\nName: " 
               << entry->value.getFirstName() << " " << entry->value.getLastName() << "\n\n"; 
            entry = entry->next;
        }
    }
}



#endif
