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
        List();
        ~List();
        bool add(const T newItem);
        bool add(int index, const T newItem);
        void remove(int index);
        void remove(const T item);
        bool contains(const T item) const;
        T get(int index) const; 
        int getLength() const;
        bool isEmpty() const; 
        void print() const;
};

#include "templates/List.tpp"