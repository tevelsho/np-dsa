#pragma once
#include <iostream>
#include <string>
using namespace std;

int custom_max(const int& a, const int& b) {
    return (a > b) ? a : b;
}

template<class T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template<class T>
AVLTree<T>::~AVLTree() {
    destroyTree(root);
}

template<class T>
void AVLTree<T>::destroyTree(AVLNode<T>* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}
    
    //AVL FUNCTIONS

template<class T>
int AVLTree<T>::height(AVLNode<T>* node) const {
    return node ? node->height : 0;
}

template<class T>
int AVLTree<T>::getBalance(AVLNode<T>* node) const {
    if (!node) return 0;
    return height(node->left) - height(node->right);
}

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
    
    // Return new root
    return x;
}
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
    
    // Return new root
    return y;
}

//Inserting an Item
template<class T>
void AVLTree<T>::insertItem(int key, T item) {
    root = insertItem(root, key, item);
}

template<class T>
AVLNode<T>* AVLTree<T>::insertItem(AVLNode<T>* node, int key, T item) {
    if (!node)
        return new AVLNode<T>(key, item);
    if (key < node->key)
        node->left = insertItem(node->left, key, item);
    else if (key > node->key)
        node->right = insertItem(node->right, key, item);
    else {
        // Key already exists, append actor to the list
        if (!node->list.isEmpty())
            node->list.add(item);
        return node;
    }
    
    node->height = 1 + custom_max(height(node->left), height(node->right));
    
    int balance = getBalance(node);
    
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    
    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}
template<class T>
AVLNode<T>* AVLTree<T>::minValueNode(AVLNode<T>* node) const{
    AVLNode<T>* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

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

template<class T>
bool AVLTree<T>::removeItem(int key, T item) {
    AVLNode<T>* node = find(key);
    node->list.remove(item);
    return false;
}

// BETWEEN X AND Y
template<class T>
void AVLTree<T>::DisplayActors(int x, int y) const{
    inOrderTraversalRangeAge(root, x, y);
    cout << endl; // For a clean newline after displaying
}

// PAST THREE YEARS
template<class T>
void AVLTree<T>::DisplayMovies() const{
    inOrderTraversalRange(root, currentYear-3, currentYear);
    cout << endl; // For a clean newline after displaying
}

// For ACTORS
template<class T>
void AVLTree<T>::inOrderTraversalRangeAge(AVLNode<T>* node, int x, int y) const {
    if (node == nullptr)
        return;

    // Since it's in-order, first traverse the left subtree if needed
    if (node->key < y)
        inOrderTraversalRange(node->right, x, y);

    if (node->key >= x && node->key <= y) {
        for (int i = 0; i < node->list.getLength(); i++) {
            cout << "Age: " << currentYear - node->key <<  " Name: " << node->list.get(i)->getName() << endl;
        }
        cout << endl;
    }

    // Then traverse the right subtree if needed
    if (node->key > x)
        inOrderTraversalRange(node->left, x, y);
}

// For Actors
template<class T>
void AVLTree<T>::inOrderTraversalRange(AVLNode<T>* node, int x, int y) const {
    if (node == nullptr)
        return;

    // Since it's in-order, first traverse the left subtree if needed
    if (node->key > x)
        inOrderTraversalRange(node->left, x, y);

    // If the current node is within range, display the items in the list
    if (node->key >= x && node->key <= y) {
        for (int i = 0; i < node->list.getLength(); i++) {
            cout << "Year: " << node->key << " Name: " << node->list.get(i)->getName() << endl;
        }
        cout << endl;
    }

    // Then traverse the right subtree if needed
    if (node->key < y)
        inOrderTraversalRange(node->right, x, y);
}