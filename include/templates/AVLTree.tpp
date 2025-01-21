#include <iostream>
#include <string>
#include "../List.h"
#include "../AVLTree.h"
using namespace std;

template <class T>

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
void AVLTree<T>::insertItem(int key, T* item) {
    root = insertItem(root, key, item);
}

template<class T>
AVLNode<T>* AVLTree<T>::insertItem(AVLNode<T>* node, int key, T* item) {
    if (!node)
        return new AVLNode<T>(key, item);
    if (key < node->key)
        node->left = insertItem(node->left, key, item);
    else if (key > node->key)
        node->right = insertItem(node->right, key, item);
    else {
        // Key already exists, append actor to the list
        if (node->list)
            node->actors->append(item);
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

// AVLNode* deleteNode(AVLNode* root, int key) {
//     // 1. Perform standard BST delete
//     if (!root)
//         return root;
    
//     if (key < root->key)
//         root->left = deleteNode(root->left, key);
//     else if (key > root->key)
//         root->right = deleteNode(root->right, key);
//     else {
//         // Node with only one child or no child
//         if ((root->left == nullptr) || (root->right == nullptr)) {
//             AVLNode* temp = root->left ? root->left : root->right;
            
//             // No child case
//             if (temp == nullptr) {
//                 temp = root;
//                 root = nullptr;
//             }
//             else { // One child case
//                 *root = *temp; // Copy the contents
//             }
            
//             delete temp;
//         }
//         else {
//             // Node with two children
//             AVLNode* temp = minValueNode(root->right);
//             root->key = temp->key;
            
//             if (root->list && temp->list) {
//                 // Clear current actors list
//                 delete root->list;
//                 root->list = new LinkedList<T*>();
                
//             }
//             root->right = deleteNode(root->right, temp->key);
//         }
//     }
    
//     // If the tree had only one node
//     if (root == nullptr)
//         return root;
    
//     // 2. Update height
//     root->height = 1 + custom_max(height(root->left), height(root->right));
    
//     // 3. Get balance factor
//     int balance = getBalance(root);
    
//     // 4. Balance the tree
//     // Left Left Case
//     if (balance > 1 && getBalance(root->left) >= 0)
//         return rightRotate(root);
    
//     // Left Right Case
//     if (balance > 1 && getBalance(root->left) < 0) {
//         root->left = leftRotate(root->left);
//         return rightRotate(root);
//     }
    
//     // Right Right Case
//     if (balance < -1 && getBalance(root->right) <= 0)
//         return leftRotate(root);
    
//     // Right Left Case
//     if (balance < -1 && getBalance(root->right) > 0) {
//         root->right = rightRotate(root->right);
//         return leftRotate(root);
//     }
    
//     return root;
// }

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

    // If the current node is within range, display the items in the list
    if (node->key >= x && node->key <= y) {
        Node<T>* next = list.getHead();
        while (next != nullptr){
            cout << "Age: " << currentYear - Node<T>.item.year <<  " Name: " << Node<T>.item.name << endl;
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
        cout << "Year: " << node->key << ", Item: ";
        Node<T>* next = list.getHead();
        while (next != nullptr){
            cout << "Year: " << Node<T>.item.year <<  " Name: " << Node<T>.item.name << endl;
        }
        cout << endl;
    }

    // Then traverse the right subtree if needed
    if (node->key < y)
        inOrderTraversalRange(node->right, x, y);
}