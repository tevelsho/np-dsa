#pragma once
#include "Actor.h"

class DynamicArray {
private:
    Actor** actors;  // Array of pointers to Actor
    int capacity;
    int size;

    // Private method to resize the array when capacity is reached
    void resize();

public:
    DynamicArray();          // Constructor
    ~DynamicArray();         // Destructor

    void add(Actor* actor);  // Method to add an actor without duplicates
    Actor* get(int index);     // Method to get an actor at a specific index
    int getSize() const;     // Getter for the size of the array
};

#include "templates/DynamicArray.tpp"