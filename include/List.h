/*----------------------------------------------------------------------------
 * Class: List (List.h)
 *
 * Description:
 *   A generic singly linked list implementation for managing a collection of elements.
 *   This class provides dynamic insertion, removal, and retrieval capabilities.
 *
 * Team Information:
 *   Coder 1: Tevel Sho     | S10258591B | Group 4
 *   Coder 2: Brayden Saga  | S10258659C | Group 4
 *
 * Key Features:
 *   Supports dynamic addition and removal of elements.
 *   Allows adding elements at the end or at specific indices.
 *   Provides methods to retrieve elements by index and to check if an element exists.
 *   Includes functions to get the size of the list and determine if it is empty.
 *   Ensures proper memory management with a destructor.
 *   Offers print functionality to display the list contents.
 *----------------------------------------------------------------------------*/
#pragma once
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class List {
    private:
        // Node structure representing each element in the list.
        struct Node {
            T item;       // The data stored in the node.
            Node* next;   // Pointer to the next node in the list.
        };

        Node* firstNode; // Pointer to the first node in the list.
        int size;        // Number of elements in the list.

    public:
        // Constructor: Initializes an empty list.
        List();

        // Destructor: Releases all allocated memory.
        ~List();

        // Adds a new item to the end of the list.
        bool add(const T newItem);

        // Adds a new item at a specified index in the list.
        bool add(int index, const T newItem);

        // Removes an item from the list at a specified index.
        void remove(int index);

        // Removes the first occurrence of an item from the list.
        void remove(const T item);

        // Checks whether the list contains the specified item.
        bool contains(const T item) const;

        // Retrieves the item at the specified index.
        T get(int index) const;

        // Returns the number of elements in the list.
        int getLength() const;

        // Checks if the list is empty.
        bool isEmpty() const;

        // Prints the contents of the list.
        void print() const;
};

#include "templates/List.tpp"