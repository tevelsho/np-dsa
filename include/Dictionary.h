/*----------------------------------------------------------------------------
 * Class: Dictionary (Dictionary.h)
 *
 * Description:
 *   A generic hash-based dictionary implementation using separate chaining 
 *   for collision handling.
 *
 * Team Information:
 *   Coder 1: Tevel Sho     | S10258591B | Group 4
 *   Coder 2: Brayden Saga  | S10258659C | Group 4
 *
 * Key Features:
 *   Template-based implementation for storing key-value pairs.
 *   Supports hashing for both int and std::string keys with customizable hash functions.
 *   Uses linked lists (separate chaining) to handle hash collisions.
 *   Provides essential methods such as add, remove, search, and existence check.
 *----------------------------------------------------------------------------*/
#pragma once
#include <string>
using namespace std;

// Define a prime number for hash table size.
const int MAX_SIZE = 3221; // Prime number for hashing.

// -----------------------------------------------------------------------------
// Hash Function Helper Struct and Node Definition
// -----------------------------------------------------------------------------

// Node structure for Dictionary, representing a key-value pair.
template <typename K, typename V>
struct Node {
    K key;       // Search key.
    V value;     // Associated value.
    Node* next;  // Pointer to the next node in the chain.

    Node() : next(nullptr) {}
    Node(K newKey, V newValue) : key(newKey), value(newValue), next(nullptr) {}
};

// Generic Hash Function Helper.
template <typename K>
struct Hash {
    static int compute(const K& key);
};

// Specialization of Hash for int keys.
template <>
struct Hash<int> {
    static int compute(int key) {
        return key % MAX_SIZE;
    }
};

int charvalue(char c)
{
    if (isdigit(c)) // Check if character is a digit
        return c - '0'; // Return numeric value of digit
    if (isalpha(c)) {
        if (isupper(c))
            return (int)c - (int)'A' + 1;
        else
            return (int)c - (int)'a' + 27;
    }
    return 0; // For non-alphanumeric characters, contribute 0 to hash
}

// Specialization of Hash for std::string keys.
template <>
struct Hash<std::string> {
    static int compute(const std::string& key) {
        long long hashValue = 0;  // Use long long to avoid overflow during calculation
        int position = 1;         // Start position weight from 1
        for (char c : key) {
            hashValue = (hashValue * 37 + charvalue(c)) % MAX_SIZE; // Use 37 as a base to reflect each character's position and value
        }
        return hashValue % MAX_SIZE;
    }
};

// -----------------------------------------------------------------------------
// Template Dictionary Class Definition
// -----------------------------------------------------------------------------
template <typename K, typename V>
class Dictionary {
    private:
        Node<K, V>* items[MAX_SIZE]; // Array of pointers for linked list chains.
        int size;                    // Current number of items in the Dictionary.

    public:
        // Constructor: Initializes the Dictionary.
        Dictionary();

        // Destructor: Releases all allocated memory.
        ~Dictionary();

        // Adds a key-value pair to the Dictionary.
        bool add(const K& key, const V& value);

        // Removes a key-value pair by key.
        void remove(const K& key);

        // Retrieves the value associated with a key.
        V get(const K& key) const;

        // Checks if the Dictionary contains the specified key.
        bool contains(const K& key) const;

        // Checks if the Dictionary is empty.
        bool isEmpty() const;

        // Returns the number of items in the Dictionary.
        int getLength() const;

        // Prints all key-value pairs in the Dictionary.
        void print() const;
};

#include "templates/Dictionary.tpp"
