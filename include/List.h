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
#include <string>
#include <iostream>
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
        bool add(const T& newItem);
        bool add(int index, const T& newItem);
        void remove(int index);
        T get(int index) const; 
        int getLength() const;
        bool isEmpty() const; 
        void print() const;
        Node* getHead() const;
};
