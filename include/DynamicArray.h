#pragma once

template <typename T>
class DynamicArray {
private:
    T* data;       // Array of type T
    int capacity;  // Maximum capacity of the array
    int size;      // Current number of elements in the array
    void mergeSort(int left, int right);
    void merge(int left, int mid, int right);

public:
    DynamicArray();          // Constructor
    ~DynamicArray();         // Destructor

    void add(const T& item); // Method to add an item without duplicates
    T get(int index) const;  // Method to get an item at a specific index
    int getSize() const;     // Getter for the size of the array
    void resize();           // Resize the array when full
    void removeDuplicates(); // Remove duplicate items from the array
    void sortByRating();     // Sort the array by rating
};

#include "templates/DynamicArray.tpp"