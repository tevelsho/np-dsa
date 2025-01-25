#include <stdexcept> // For std::out_of_range

// Constructor
template <typename T>
DynamicArray<T>::DynamicArray() : capacity(1), size(0) {
    data = new T[capacity];
}

// Destructor
template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

// Add an item to the array (without duplicates)
template <typename T>
void DynamicArray<T>::add(const T& item) {
    // Check for duplicates
    for (int i = 0; i < size; ++i) {
        if (data[i] == item) {
            return; // Item already present, do not add
        }
    }

    // Resize if necessary
    if (size == capacity) {
        resize();
    }

    // Add the item
    data[size++] = item;
}

// Get an item at a specific index
template <typename T>
T DynamicArray<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Get the size of the array
template <typename T>
int DynamicArray<T>::getSize() const {
    return size;
}

// Resize the array (double the capacity)
template <typename T>
void DynamicArray<T>::resize() {
    int newCapacity = capacity * 2;
    T* newArray = new T[newCapacity];
    for (int i = 0; i < size; ++i) {
        newArray[i] = data[i];
    }
    delete[] data;
    data = newArray;
    capacity = newCapacity;
}

// Remove duplicate items from the array
template <typename T>
void DynamicArray<T>::removeDuplicates() {
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (data[i] == data[j]) {
                // Shift elements to the left
                for (int k = j; k < size - 1; ++k) {
                    data[k] = data[k + 1];
                }
                size--; // Reduce the size
                j--;    // Recheck the current index
            }
        }
    }
}

// Merge two sorted halves of the array
template <typename T>
void DynamicArray<T>::merge(int left, int mid, int right) {
    int n1 = mid - left + 1; // Size of the left half
    int n2 = right - mid;    // Size of the right half

    // Create temporary arrays
    T* leftArray = new T[n1];
    T* rightArray = new T[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        leftArray[i] = data[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArray[i] = data[mid + 1 + i];
    }

    // Merge the temporary arrays back into data[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i]->getRating() >= rightArray[j]->getRating()) { // Sort by rating (descending)
            data[k] = leftArray[i];
            i++;
        } else {
            data[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of leftArray (if any)
    while (i < n1) {
        data[k] = leftArray[i];
        i++;
        k++;
    }

    // Copy remaining elements of rightArray (if any)
    while (j < n2) {
        data[k] = rightArray[j];
        j++;
        k++;
    }

    // Clean up temporary arrays
    delete[] leftArray;
    delete[] rightArray;
}

// Recursive Merge Sort function
template <typename T>
void DynamicArray<T>::mergeSort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        // Merge the sorted halves
        merge(left, mid, right);
    }
}

// Public method to sort the array using Merge Sort
template <typename T>
void DynamicArray<T>::sortByRating() {
    mergeSort(0, size - 1);
}