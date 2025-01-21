// Dictionary.tpp - Template Implementation without Standard Library Hash

#ifndef DICTIONARY_TPP
#define DICTIONARY_TPP

#include "../Dictionary.h"

// Constructor
template <typename K, typename V>
Dictionary<K, V>::Dictionary()
{
    size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        items[i] = nullptr;
    }
}

// Destructor
template <typename K, typename V>
Dictionary<K, V>::~Dictionary() {
    for (int i = 0; i < MAX_SIZE; i++) {
        Node<K, V>* current = items[i];
        while (current != nullptr) {
            Node<K, V>* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
}

// Hash function using custom Hash struct
template <typename K, typename V>
int Dictionary<K, V>::hashFunction(K key) {
    return Hash<K>::compute(key);
}

// Add a new item with the specified key to the Dictionary
template <typename K, typename V>
bool Dictionary<K, V>::add(K newKey, V newValue) {
    int index = hashFunction(newKey);
    Node<K, V>* current = items[index];

    // Check for duplicate keys
    while (current != nullptr) {
        if (current->key == newKey) {
            return false; // Duplicate key found
        }
        current = current->next;
    }

    // Insert new node at the beginning
    Node<K, V>* newNode = new Node<K, V>(newKey, newValue);
    newNode->next = items[index];
    items[index] = newNode;
    size++;
    return true;
}

// Remove an item with the specified key from the Dictionary
template <typename K, typename V>
void Dictionary<K, V>::remove(K key) {
    int index = hashFunction(key);

    Node<K, V>* previous = nullptr;
    Node<K, V>* current = items[index];

    while (current != nullptr) {
        if (current->key == key) {
            if (previous == nullptr) {
                items[index] = current->next; // First node
            }
            else {
                previous->next = current->next;
            }
            delete current;
            size--;
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Get an item with the specified key from the Dictionary
template <typename K, typename V>
V Dictionary<K, V>::get(K key) {
    int index = hashFunction(key);
    Node<K, V>* current = items[index];
    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return nullptr; // Return nullptr if key not found (Assuming V can be nullptr)
}

// Check if a specified key is in the Dictionary
template <typename K, typename V>
bool Dictionary<K, V>::contains(K key) {
    int index = hashFunction(key);
    Node<K, V>* current = items[index];
    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Check if the Dictionary is empty
template <typename K, typename V>
bool Dictionary<K, V>::isEmpty() {
    return size == 0;
}

// Get the number of items in the Dictionary
template <typename K, typename V>
int Dictionary<K, V>::getLength() {
    return size;
}

// Display the items in the Dictionary
template <typename K, typename V>
void Dictionary<K, V>::print() {
    for (int i = 0; i < MAX_SIZE; i++) {
        Node<K, V>* current = items[i];
        if (current != nullptr) {
            std::cout << "Index " << i << ": ";
            while (current != nullptr) {
                std::cout << "[" << current->key << ": " << current->value << "] -> ";
                current = current->next;
            }
            std::cout << "nullptr" << std::endl;
        }
    }
}

#endif // DICTIONARY_TPP
