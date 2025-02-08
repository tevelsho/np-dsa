// Returns the maximum of two integer values.
int custom_max(const int& a, const int& b) {
    return (a > b) ? a : b;
}

// Initializes an empty AVL tree.
template<class T>
AVLTree<T>::AVLTree() : root(nullptr) {}

// Recursively destroys all nodes in the AVL tree.
template<class T>
AVLTree<T>::~AVLTree() {
    destroyTree(root);
}

// Helper function to recursively delete all nodes in the tree.
template<class T>
void AVLTree<T>::destroyTree(AVLNode<T>* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Returns the height of a given node. If the node is null, returns 0.
template<class T>
int AVLTree<T>::height(AVLNode<T>* node) const {
    return node ? node->height : 0;
}

// Calculates and returns the balance factor of a node.
template<class T>
int AVLTree<T>::getBalance(AVLNode<T>* node) const {
    if (!node) return 0;
    return height(node->left) - height(node->right);
}

// Performs a right rotation on the given node and updates heights.
template<class T>
AVLNode<T>* AVLTree<T>::rightRotate(AVLNode<T>* y) {
    AVLNode<T>* x = y->left;
    AVLNode<T>* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = custom_max(height(y->left), height(y->right)) + 1;
    x->height = custom_max(height(x->left), height(x->right)) + 1;

    return x; // Return new root
}

// Performs a left rotation on the given node and updates heights.
template<class T>
AVLNode<T>* AVLTree<T>::leftRotate(AVLNode<T>* x) {
    AVLNode<T>* y = x->right;
    AVLNode<T>* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = custom_max(height(x->left), height(x->right)) + 1;
    y->height = custom_max(height(y->left), height(y->right)) + 1;

    return y; // Return new root
}

// Inserts a new item into the AVL tree and maintains balance.
template<class T>
void AVLTree<T>::insertItem(int key, T item) {
    root = insertItem(root, key, item);
}

// Recursively inserts an item and balances the tree if necessary.
template<class T>
AVLNode<T>* AVLTree<T>::insertItem(AVLNode<T>* node, int key, T item) {
    if (!node)
        return new AVLNode<T>(key, item);

    if (key < node->key)
        node->left = insertItem(node->left, key, item);
    else if (key > node->key)
        node->right = insertItem(node->right, key, item);
    else {
        // If key already exists, add the item to the list
        if (!node->list.isEmpty())
            node->list.add(item);
        return node;
    }

    // Update height of this ancestor node
    node->height = 1 + custom_max(height(node->left), height(node->right));

    // Get the balance factor to check for imbalances
    int balance = getBalance(node);

    // Perform rotations if the node is unbalanced
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Returns the node with the smallest key value in the subtree.
template<class T>
AVLNode<T>* AVLTree<T>::minValueNode(AVLNode<T>* node) const {
    AVLNode<T>* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Searches for a node with the given key and returns it.
template<class T>
AVLNode<T>* AVLTree<T>::find(int key) {
    AVLNode<T>* current = root;
    while (current != nullptr) {
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else
            return current; // Key found
    }
    return nullptr; // Key not found
}

// Removes a specific item from a node's list but does not delete the node itself.
template<class T>
bool AVLTree<T>::removeItem(int key, T item) {
    AVLNode<T>* node = find(key);
    node->list.remove(item);
    return false;
}

// Checks if the AVL Tree is empty.
template<class T>
bool AVLTree<T>::isEmpty() const {
    return root == nullptr;
}

// Displays actors within the specified age range.
template<class T>
void AVLTree<T>::DisplayActors(int x, int y) const {
    cout << "\n===============================\n";
    cout << "Actors aged between " << (currentYear - y) << " and " << (currentYear - x) << ":\n";
    cout << "-------------------------------\n";
    inOrderTraversalRangeAge(root, x, y);
    cout << "\n===============================\n";
}

// Displays movies released in the last three years.
template<class T>
void AVLTree<T>::DisplayMovies() const {
    cout << "\n==============================\n";
    cout << "Movies released between " << (currentYear - 3) << " and " << currentYear << ":\n";
    cout << "------------------------------\n";
    inOrderTraversalRange(root, currentYear - 3, currentYear);
    cout << "\n==============================\n";
}

// In-order traversal to display actors within a specified age range.
template<class T>
void AVLTree<T>::inOrderTraversalRangeAge(AVLNode<T>* node, int x, int y) const {
    if (node == nullptr)
        return;

    // Traverse right subtree if needed
    if (node->key < y)
        inOrderTraversalRangeAge(node->right, x, y);

    // Display actors in the range
    if (node->key >= x && node->key <= y) {
        for (int i = 0; i < node->list.getLength(); i++) {
            cout << "Age: " << currentYear - node->key <<  " Name: " << node->list.get(i)->getName() << endl;
        }
    }

    // Traverse left subtree if needed
    if (node->key > x)
        inOrderTraversalRangeAge(node->left, x, y);
}

// In-order traversal to display movies released within a specified time range.
template<class T>
void AVLTree<T>::inOrderTraversalRange(AVLNode<T>* node, int x, int y) const {
    if (node == nullptr)
        return;

    // Traverse left subtree if needed
    if (node->key > x)
        inOrderTraversalRange(node->left, x, y);

    // Display movies in the range
    if (node->key >= x && node->key <= y) {
        for (int i = 0; i < node->list.getLength(); i++) {
            cout << "Year: " << node->key << " Title: " << node->list.get(i)->getName() << endl;
        }
    }

    // Traverse right subtree if needed
    if (node->key < y)
        inOrderTraversalRange(node->right, x, y);
}