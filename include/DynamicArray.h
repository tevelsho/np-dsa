/*----------------------------------------------------------------------------
 * Class: DynamicArray (DynamicArray.h)
 *
 * Description:
 *   A dynamic array implementation for managing a collection of objects with 
 *   support for resizing, sorting, and duplicate removal. This class provides 
 *   methods to add elements (while avoiding duplicates), access elements by index,
 *   sort the array (e.g., by ratings), and manage the underlying storage.
 *
 * Team Information:
 *   Coder 1: Tevel Sho     | S10258591B | Group 4
 *   Coder 2: Brayden Saga  | S10258659C | Group 4
 *
 * Key Features:
 *   Dynamic resizing to accommodate additional elements.
 *   Prevents duplicate entries during element addition.
 *   Sorting functionality based on ratings.
 *   Efficient mechanism to remove duplicates.
 *   Provides access to individual elements and array metadata.
 *----------------------------------------------------------------------------*/
#pragma once

template <typename T>
class DynamicArray {
    private:
        T* data;       // Pointer to the underlying array of type T.
        int capacity;  // Maximum capacity of the dynamic array.
        int size;      // Current number of elements in the array.

        // Helper functions for merge sort.
        void mergeSort(int left, int right);
        void merge(int left, int mid, int right);

    public:
        // Constructor: Initializes an empty dynamic array.
        DynamicArray();

        // Destructor: Releases allocated memory.
        ~DynamicArray();

        // Adds an item to the array, avoiding duplicates.
        void add(const T& item);

        // Retrieves the item at the specified index.
        T get(int index) const;

        // Returns the current number of elements in the array.
        int getSize() const;

        // Resizes the array when it reaches its capacity.
        void resize();

        // Removes duplicate items from the array.
        void removeDuplicates();

        // Sorts the array by rating.
        void sortByRating();
};

#include "templates/DynamicArray.tpp"