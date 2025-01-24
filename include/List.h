/*----------------------------------------------------------------------------
💻 Class: List (List.h)
Description: A generic singly linked list implementation.

Team Information:
    - Member 1: [Name], [Student ID], [Group Name]
    - Member 2: [Name], [Student ID], [Group Name]

Key Features:
    - Constructor and destructor for initializing and cleaning up the list.
    - Add elements to the list at the end or a specific index.
    - Remove elements from the list by index.
    - Retrieve elements by index.
    - Get the size of the list or check if it is empty.
    - Print the contents of the list.
    - Retrieve the head of the list for iteration.
----------------------------------------------------------------------------*/
#pragma once
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class List {
private:
    struct Node {
        T item;
        Node* next;
    };

    Node* firstNode;
    int size;

public:
    // Constructor and Destructor
    List();
    ~List();

    // Member Functions
    bool add(const T& newItem);
    bool add(int index, const T& newItem);
    void remove(int index);
    T& get(int index) const;
    int getLength() const;
    bool isEmpty() const;
    void print() const;
    Node* getHead() const;
};

#include "templates/List.tpp"