/*----------------------------------------------------------------------------
💻 Class: Dictionary (Dictionary.h)
Description: A generic hash-based dictionary implementation using separate 
             chaining for collision handling.

Team Information:
    - Member 1: [Name], [Student ID], [Group Name]
    - Member 2: [Name], [Student ID], [Group Name]

Key Features:
    - Template-based implementation for storing key-value pairs.
    - Supports hashing for both `int` and `std::string` keys with customizable 
      hash functions.
    - Collision handling using linked lists (separate chaining).
    - Provides essential methods such as add, remove, search, and check existence.
----------------------------------------------------------------------------*/
#pragma once
#pragma once
#include <string>
using namespace std;

// Define a prime number for hash table size
const int MAX_SIZE = 3221; // Prime number for hashing

// Hash Function Helper Struct
// Template node structure for Dictionary
template <typename K, typename V>
struct Node {
    K key;       // Search key
    V value;     // Associated value
    Node* next;  // Pointer to the next node

    Node() : next(nullptr) {}
    Node(K newKey, V newValue) : key(newKey), value(newValue), next(nullptr) {}
};

// Hash Function Helper
template <typename K>
struct Hash {
    static int compute(const K& key);
};

// Specialization of Hash for int
template <>
struct Hash<int> {
    static int compute(int key) {
        return key % MAX_SIZE;
    }
};

int charvalue(char c)
{
	if (isalpha(c))
	{
		if (isupper(c))
			return (int)c - (int)'A';
		else
			return (int)c - (int)'a' + 26;
	}
	else
		return -1;
}

// Specialization of Hash for std::string
template <>
struct Hash<std::string> {
    static int compute(const std::string& key) {
        int hashValue = 0;
        for (char c : key) {
            hashValue += charvalue(c);
        }
        return hashValue % MAX_SIZE;
    }
};

// Template Dictionary Class
template <typename K, typename V>
class Dictionary {
    private:
        Node<K, V>* items[MAX_SIZE]; // Array of linked lists (chaining for collision handling)
        int size;                    // Number of items in the Dictionary

    public:
        // Constructor
        Dictionary();

        // Destructor
        ~Dictionary();

        // Add a key-value pair to the Dictionary
        bool add(const K& key, const V& value);

        // Remove a key-value pair by key
        void remove(const K& key);

        // Get the value associated with a key
        V get(const K& key) const;

        // Check if the Dictionary contains a specific key
        bool contains(const K& key) const;

        // Check if the Dictionary is empty
        bool isEmpty() const;

        // Get the number of items in the Dictionary
        int getLength() const;

        // Print all key-value pairs in the Dictionary
        void print() const;
};
#include "templates/Dictionary.tpp"