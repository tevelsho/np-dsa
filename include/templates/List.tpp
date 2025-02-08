// Initializes an empty list with a null first node and a size of 0.
template <typename T>
List<T>::List() : firstNode(nullptr), size(0) {}

// Destroys the list by deallocating all dynamically allocated nodes.
template <typename T>
List<T>::~List() {
    Node* current = firstNode;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

// Checks if the list contains a specific item by traversing the nodes.
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

// Adds a new item to the list
template <typename T>
bool List<T>::add(const T newItem) {
    Node* newNode = new Node{newItem, firstNode}; // New node points to current first node
    firstNode = newNode; // Update firstNode to the new node
    ++size; // Increase size count
    return true;
}


// Inserts a new item at a specific index, shifting elements accordingly.
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

// Removes an item at a specific index, adjusting list pointers.
template <typename T>
void List<T>::remove(int index) {
    if (index < 0 || index >= size) {
        cout << "Index out of range" << endl;
        return;
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

// Removes a specific item from the list if found.
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
            --size;
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Retrieves the item at a specific index, ensuring index validity.
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

// Returns the number of elements in the list.
template <typename T>
int List<T>::getLength() const {
    return size;
}

// Checks if the list is empty.
template <typename T>
bool List<T>::isEmpty() const {
    return size == 0;
}

// Prints the contents of the list in order.
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

// Recursively sorts the linked list using merge sort.
template <typename T>
typename List<T>::Node* List<T>::mergeSortList(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    Node* mid = getMid(head);
    Node* left = head;
    Node* right = mid->next;
    mid->next = nullptr;

    left = mergeSortList(left);
    right = mergeSortList(right);

    return merge(left, right);
}

// Merges two sorted sub-lists into a single sorted list.
template <typename T>
typename List<T>::Node* List<T>::merge(Node* left, Node* right) {
    Node dummy;
    Node* tail = &dummy;
    dummy.next = nullptr;

    while (left != nullptr && right != nullptr) {
        if (left->item->getName() <= right->item->getName()) {
            tail->next = left;
            left = left->next;
        } else {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }

    tail->next = (left != nullptr) ? left : right;
    return dummy.next;
}

// Helper function to find the middle node of the list.
template <typename T>
typename List<T>::Node* List<T>::getMid(Node* head) {
    if (head == nullptr) {
        return head;
    }

    Node* slow = head;
    Node* fast = head;

    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// Sorts the list in ascending order using merge sort.
template <typename T>
void List<T>::sortByAlphabetical() {
    firstNode = mergeSortList(firstNode);
}