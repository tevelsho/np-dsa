/*----------------------------------------------------------------------------
💻 Class: Actor (Actor.h)
Description: Represents a movie with its details and the actors involved.
 
Team Information:
    - Member 1: [Name], [Student ID], [Group Name]
    - Member 2: [Name], [Student ID], [Group Name]

Key Features:
    - Stores details about the movie (title, plot, release year).
    - Maintains a list of actors who starred in the movie.
    - Provides methods to update movie details and retrieve actor information.
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

// Specialization of Hash for `int`
template <>
struct Hash<int> {
    static int compute(int key) {
        return key % MAX_SIZE;
    }
};

// Specialization of Hash for `std::string`
template <>
struct Hash<std::string> {
    static int compute(const std::string& key) {
        int hash = 0;
        for (char c : key) {
            if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a'; // Convert to lowercase
            hash = (hash * 26 + (c - 'a')) % MAX_SIZE;
        }
        return hash;
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

#include "templates/Dictionary.tpp"