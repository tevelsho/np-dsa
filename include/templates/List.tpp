// Constructor
template <typename T>
List<T>::List() : firstNode(nullptr), size(0) {}

// Destructor
template <typename T>
List<T>::~List() {
    Node* current = firstNode;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

template <typename T>
bool List<T>::contains(const T item) const {
    Node* current = firstNode;
    while (current != nullptr) {
        if (current->item == item) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
bool List<T>::add(const T newItem) {
    Node* newNode = new Node{newItem, nullptr};

    // If the list is empty, insert the new node as the first node
    if (isEmpty()) {
        firstNode = newNode;
    }
    // If the new item should be inserted at the beginning of the list
    else if (newItem < firstNode->item) {
        newNode->next = firstNode;
        firstNode = newNode;
    }
    // Otherwise, find the correct position to insert the new node
    else {
        Node* current = firstNode;
        // Traverse the list to find the insertion point
        while (current->next != nullptr && current->next->item < newItem) {
            current = current->next;
        }
        // Insert the new node after the current node
        newNode->next = current->next;
        current->next = newNode;
    }

    ++size;
    return true;
}

// Add item at a specific index
template <typename T>
bool List<T>::add(int index, const T newItem) {
    if (index < 0 || index > size) {
        return false; // Invalid index
    }

    Node* newNode = new Node{newItem, nullptr};

    if (index == 0) {
        newNode->next = firstNode;
        firstNode = newNode;
    } else {
        Node* current = firstNode;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    ++size;
    return true;
}

// Remove item at a specific index
template <typename T>
void List<T>::remove(int index) {
    if (index < 0 || index >= size) {
        cout << "Index out of range" << endl;
    }

    Node* temp;

    if (index == 0) {
        temp = firstNode;
        firstNode = firstNode->next;
    } else {
        Node* current = firstNode;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        temp = current->next;
        current->next = current->next->next;
    }

    delete temp;
    --size;
}

template <typename T>
void List<T>::remove(const T item) {
    Node* current = firstNode;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->item == item) {
            if (previous == nullptr) {
                firstNode = current->next;
            } else {
                previous->next = current->next;
            }
            delete current;
            size--;
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Get item at a specific index
template <typename T>
T List<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }

    Node* current = firstNode;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->item;
}

// Get the length of the list
template <typename T>
int List<T>::getLength() const {
    return size;
}

// Check if the list is empty
template <typename T>
bool List<T>::isEmpty() const {
    return size == 0;
}

// Print the list
template <typename T>
void List<T>::print() const {
    Node* current = firstNode;

    if (isEmpty()) {
        cout << "The list is empty." << endl;
        return;
    }

    while (current != nullptr) {
        cout << current->item << " -> ";
        current = current->next;
    }
    cout << "nullptr" << endl;
}