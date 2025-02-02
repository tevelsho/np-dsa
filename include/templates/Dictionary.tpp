#include <type_traits> 

// Initializes the dictionary with an empty hash table.
template <typename K, typename V>
Dictionary<K, V>::Dictionary() : size(0) {
    for (int i = 0; i < MAX_SIZE; ++i) {
        items[i] = nullptr;
    }
}

// Destructor to deallocate all nodes and prevent memory leaks.
template <typename K, typename V>
Dictionary<K, V>::~Dictionary() {
    for (int i = 0; i < MAX_SIZE; ++i) {
        Node<K, V>* current = items[i];
        while (current != nullptr) {
            Node<K, V>* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
}

// Adds a key-value pair to the dictionary using separate chaining for collision resolution.
template <typename K, typename V>
bool Dictionary<K, V>::add(const K& key, const V& value) {
    int hashIndex = Hash<K>::compute(key);
    Node<K, V>* newNode = new Node<K, V>(key, value);

    // Insert at empty index
    if (items[hashIndex] == nullptr) {
        items[hashIndex] = newNode;
    } else {
        Node<K, V>* current = items[hashIndex];
        
        // Traverse the chain to check for duplicates or find insertion point
        while (current->next != nullptr) {
            if (current->key == key) {
                delete newNode; // Avoid memory leak if key already exists
                return false;
            }
            current = current->next;
        }
        current->next = newNode;
    }
    ++size;
    return true;
}

// Removes a key-value pair from the dictionary if it exists.
template <typename K, typename V>
void Dictionary<K, V>::remove(const K& key) {
    int hashIndex = Hash<K>::compute(key);
    Node<K, V>* current = items[hashIndex];
    Node<K, V>* prev = nullptr;

    // Search for the key in the linked list
    while (current != nullptr && current->key != key) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) return; // Key not found

    // If the node to be deleted is the first node in the chain
    if (prev == nullptr) {
        items[hashIndex] = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
    --size;
}

// Retrieves the value associated with a given key.
template <typename K, typename V>
V Dictionary<K, V>::get(const K& key) const {
    int hashIndex = Hash<K>::compute(key);
    Node<K, V>* current = items[hashIndex];

    // Traverse the linked list at the hashed index to find the key
    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return 0; // Default return value if key is not found
}

// Checks if a key exists in the dictionary.
template <typename K, typename V>
bool Dictionary<K, V>::contains(const K& key) const {
    int hashIndex = Hash<K>::compute(key);
    Node<K, V>* current = items[hashIndex];

    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Checks if the dictionary is empty.
template <typename K, typename V>
bool Dictionary<K, V>::isEmpty() const {
    return size == 0;
}

// Returns the total number of key-value pairs stored in the dictionary.
template <typename K, typename V>
int Dictionary<K, V>::getLength() const {
    return size;
}

// Prints all key-value pairs in the dictionary.
template <typename K, typename V>
void Dictionary<K, V>::print() const {
    for (int i = 0; i < MAX_SIZE; ++i) {
        Node<K, V>* current = items[i];
        while (current != nullptr) {
            std::cout << "[" << current->key << ": " << current->value << "] -> ";
            current = current->next;
        }
        if (items[i] != nullptr) {
            std::cout << "null\n";
        }
    }
}