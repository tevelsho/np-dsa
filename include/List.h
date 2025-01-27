/*----------------------------------------------------------------------------
💻 Class: List (List.h)
Description: A generic singly linked list implementation for managing a 
             collection of elements with dynamic insertion, removal, and 
             retrieval capabilities.

Team Information:
    - Member 1: [Name], [Student ID], [Group Name]
    - Member 2: [Name], [Student ID], [Group Name]

Key Features:
    - Supports dynamic addition and removal of elements.
    - Provides methods to add elements at the end or at specific indices.
    - Retrieve elements by index or check if an element exists in the list.
    - Methods to get the size of the list or check if it is empty.
    - Destructor to ensure proper memory management.
    - Print functionality to display the list contents.
----------------------------------------------------------------------------*/

#pragma once
#include <stdexcept>

template <typename T>
class List {
    private:
        struct Node {
            T item;      // Data stored in the node
            Node* next;  // Pointer to the next node in the list
        };

        Node* firstNode; // Pointer to the first node in the list
        int size;        // Current number of elements in the list

    public:
        // Constructor and Destructor
        List();         // Default constructor
        ~List();        // Destructor to clean up the list

        // Core methods
        bool add(const T newItem);        // Adds an item to the end of the list
        bool add(int index, const T newItem); // Adds an item at a specific index
        void remove(int index);           // Removes an item by index
        void remove(const T item);        // Removes the first occurrence of a specific item
        bool contains(const T item) const; // Checks if an item exists in the list

        // Access methods
        T get(int index) const;           // Retrieves an item by index
        int getLength() const;            // Returns the number of elements in the list
        bool isEmpty() const;             // Checks if the list is empty

        // Utility method
        void print() const;               // Prints the contents of the list
};

#include "templates/List.tpp"