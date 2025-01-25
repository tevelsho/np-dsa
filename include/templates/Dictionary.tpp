// Dictionary.tpp - Template Implementation without Standard Library Hash
#include <type_traits> // For std::is_pointer

// Constructor
template <typename K, typename V>
Dictionary<K, V>::Dictionary() : size(0) {
    for (int i = 0; i < MAX_SIZE; ++i) {
        items[i] = nullptr;
    }
}

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

template <typename K, typename V>
bool Dictionary<K, V>::add(const K& key, const V& value) {
    int hashIndex = Hash<K>::compute(key);
    Node<K, V>* newNode = new Node<K, V>(key, value);

    if (items[hashIndex] == nullptr) {
        items[hashIndex] = newNode;
    } else {
        Node<K, V>* current = items[hashIndex];
        while (current->next != nullptr) {
            if (current->key == key) {
                delete newNode; // Avoid memory leak
                return false;   // Key already exists
            }
            current = current->next;
        }
        current->next = newNode;
    }
    ++size;
    return true;
}

template <typename K, typename V>
void Dictionary<K, V>::remove(const K& key) {
    int hashIndex = Hash<K>::compute(key);
    Node<K, V>* current = items[hashIndex];
    Node<K, V>* prev = nullptr;

    while (current != nullptr && current->key != key) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) return; // Key not found

    if (prev == nullptr) {
        items[hashIndex] = current->next;
    } else {
        prev->next = current->next;
    }
    delete current;
    --size;
}

template <typename K, typename V>
V Dictionary<K, V>::get(const K& key) const {
    int hashIndex = Hash<K>::compute(key);
    Node<K, V>* current = items[hashIndex];

    while (current != nullptr) {
        if (current->key == key) return current->value;
        current = current->next;
    }
    if constexpr (std::is_pointer<V>::value) {
        return nullptr; // Return NULL if V is a pointer type
    } else {
        return 0; // Return 0 if V is a non-pointer type (e.g., int)
    }
}

template <typename K, typename V>
bool Dictionary<K, V>::contains(const K& key) const {
    int hashIndex = Hash<K>::compute(key);
    Node<K, V>* current = items[hashIndex];

    while (current != nullptr) {
        if (current->key == key) return true;
        current = current->next;
    }
    return false;
}

template <typename K, typename V>
bool Dictionary<K, V>::isEmpty() const {
    return size == 0;
}

template <typename K, typename V>
int Dictionary<K, V>::getLength() const {
    return size;
}

template <typename K, typename V>
void Dictionary<K, V>::print() const {
    for (int i = 0; i < MAX_SIZE; ++i) {
        Node<K, V>* current = items[i];
        while (current != nullptr) {
            std::cout << "[" << current->key << ": " << current->value << "] -> ";
            current = current->next;
        }
        if (items[i] != nullptr) std::cout << "null\n";
    }
}