/*----------------------------------------------------------------------------
💻 Class: DynamicArray (DynamicArray.h)
Description: A dynamic array implementation for managing a collection of objects 
             with support for resizing, sorting, and removing duplicates.

Team Information:
    - Member 1: [Name], [Student ID], [Group Name]
    - Member 2: [Name], [Student ID], [Group Name]

Key Features:
    - Dynamic resizing to accommodate additional elements.
    - Supports adding elements while avoiding duplicates.
    - Sorting functionality based on ratings.
    - Efficient duplicate removal mechanism.
    - Provides access to individual elements and array metadata.
----------------------------------------------------------------------------*/

#pragma once

template <typename T>
class DynamicArray {
    private:
        T* data;       // Array of type T
        int capacity;  // Maximum capacity of the array
        int size;      // Current number of elements in the array

        // Helper methods for merge sort
        void mergeSort(int left, int right);
        void merge(int left, int mid, int right);

    public:
        // Constructor and Destructor
        DynamicArray();          // Default constructor
        ~DynamicArray();         // Destructor

        // Core methods
        void add(const T& item); // Adds an item to the array (avoiding duplicates)
        T get(int index) const;  // Retrieves an item at the specified index
        int getSize() const;     // Returns the current size of the array

        // Utility methods
        void resize();           // Resizes the array when it reaches capacity
        void removeDuplicates(); // Removes duplicate items from the array
        void sortByRating();     // Sorts the array by rating
};

#include "templates/DynamicArray.tpp"