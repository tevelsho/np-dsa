#include <stdexcept> 

// Initializes an empty dynamic array with an initial capacity of 1.
template <typename T>
DynamicArray<T>::DynamicArray() : capacity(1), size(0) {
    data = new T[capacity];
}

// Destroys the dynamic array by deallocating the allocated memory.
template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

// Adds a new item to the array while avoiding duplicates.
template <typename T>
void DynamicArray<T>::add(const T& item) {
    // Check if the item already exists in the array
    for (int i = 0; i < size; ++i) {
        if (data[i] == item) {
            return; // Duplicate found, do not add the item
        }
    }

    // Resize if the array is at full capacity
    if (size == capacity) {
        resize();
    }

    // Insert the new item at the next available index
    data[size++] = item;
}

// Retrieves an item at a specific index with bounds checking.
template <typename T>
T DynamicArray<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Returns the current number of elements in the array.
template <typename T>
int DynamicArray<T>::getSize() const {
    return size;
}

// Resizes the array by doubling its capacity when full.
template <typename T>
void DynamicArray<T>::resize() {
    int newCapacity = capacity * 2;
    T* newArray = new T[newCapacity];

    // Copy existing elements to the new array
    for (int i = 0; i < size; ++i) {
        newArray[i] = data[i];
    }

    // Deallocate old array and update capacity
    delete[] data;
    data = newArray;
    capacity = newCapacity;
}

// Removes duplicate elements from the array while maintaining order.
template <typename T>
void DynamicArray<T>::removeDuplicates() {
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (data[i] == data[j]) {
                // Shift elements to the left to remove the duplicate
                for (int k = j; k < size - 1; ++k) {
                    data[k] = data[k + 1];
                }
                size--; // Reduce the array size
                j--;    // Recheck the current index
            }
        }
    }
}

// Merges two sorted halves of the array based on rating in descending order.
template <typename T>
void DynamicArray<T>::merge(int left, int mid, int right) {
    int n1 = mid - left + 1; // Size of the left subarray
    int n2 = right - mid;    // Size of the right subarray

    // Create temporary arrays for merging
    T* leftArray = new T[n1];
    T* rightArray = new T[n2];

    // Copy data into temporary arrays
    for (int i = 0; i < n1; i++) {
        leftArray[i] = data[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArray[i] = data[mid + 1 + i];
    }

    // Merge the two halves back into the original array
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i]->getRating() >= rightArray[j]->getRating()) { // Sort in descending order
            data[k] = leftArray[i];
            i++;
        } else {
            data[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements from leftArray
    while (i < n1) {
        data[k] = leftArray[i];
        i++;
        k++;
    }

    // Copy any remaining elements from rightArray
    while (j < n2) {
        data[k] = rightArray[j];
        j++;
        k++;
    }

    // Deallocate temporary arrays
    delete[] leftArray;
    delete[] rightArray;
}

// Recursively sorts the array using Merge Sort.
template <typename T>
void DynamicArray<T>::mergeSort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursively sort the two halves
        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        // Merge the sorted halves
        merge(left, mid, right);
    }
}

// Sorts the dynamic array based on rating using Merge Sort.
template <typename T>
void DynamicArray<T>::sortByRating() {
    mergeSort(0, size - 1);
}