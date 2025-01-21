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
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <iostream>

// Define a prime number for hash table size
const int MAX_SIZE = 3221; // Prime number

// Forward declaration of Node
template <typename K, typename V>
struct Node;

// Hash Function Helper Struct
template <typename K>
struct Hash;

// Specialization of Hash for int
template <>
struct Hash<int> {
    static int compute(int key) {
        return key % MAX_SIZE;
    }
};

// Specialization of Hash for std::string
template <>
struct Hash<std::string> {
    static int compute(const std::string& key) {
        int hash = 0;
        for (char c : key) {
            // Convert to lowercase if uppercase
            if (c >= 'A' && c <= 'Z') {
                c = c - 'A' + 'a';
            }
            // Map 'a' to 0, 'b' to 1, ..., 'z' to 25
            int letter = c - 'a';
            hash = (hash * 26 + letter) % MAX_SIZE;
        }
        return hash;
    }
};

// Template Dictionary Class
template <typename K, typename V>
struct Node {
    K key;      // Search key
    V value;    // Data item
    Node* next; // Pointer to the next node

    Node() : next(nullptr) {}
    Node(K newKey, V newValue) : key(newKey), value(newValue), next(nullptr) {}
};

template <typename K, typename V>
class Dictionary
{
private:
    Node<K, V>* items[MAX_SIZE];
    int size; // Number of items in the Dictionary

public:
    // Constructor
    Dictionary();

    // Destructor
    ~Dictionary();

    // Hash function
    int hashFunction(K key);

    // Add a new item with the specified key to the Dictionary
    bool add(K newKey, V newValue);

    // Remove an item with the specified key from the Dictionary
    void remove(K key);

    // Get an item with the specified key from the Dictionary
    V get(K key);

    // Check if a specified key is in the Dictionary
    bool contains(K key);

    // Check if the Dictionary is empty
    bool isEmpty();

    // Get the number of items in the Dictionary
    int getLength();

    // Display the items in the Dictionary
    void print();
};
#endif // DICTIONARY_H
