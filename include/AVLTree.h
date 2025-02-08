/*----------------------------------------------------------------------------
 * Class: AVLTree (AVLTree.h)
 *
 * Description:
 *   A generic AVL Tree implementation for managing Actor* or Movie* objects,
 *   organized by a key (e.g., year of actor birth or movie release year).
 *
 * Team Information:
 *   Coder 1: Brayden Saga  | S10258659C | Group 4
 *
 * Key Features:
 *   Default constructor for creating an empty AVL tree.
 *   Self-balancing binary search tree for efficient insertion, deletion, and search operations.
 *   Supports storage of objects like Actor* or Movie* using a key-based structure.
 *   Provides in-order traversal to display actors or movies within a specified range.
 *   Maintains data consistency through AVL tree rotations for balance.
 *----------------------------------------------------------------------------*/
#pragma once

#include <string>
#include <iostream>
#include "List.h"
using namespace std;

template <class T> // T will either be Actor* or Movie*
struct AVLNode {
    int key;             // Key representing year (birth or release)
    List<T> list;        // List of items sharing the same key
    AVLNode* left;       // Pointer to the left child
    AVLNode* right;      // Pointer to the right child
    int height;          // Height of the node for balancing

    // Constructor: Initializes the node with a key and an item.
    AVLNode(int key, T item)
        : key(key), list(), left(nullptr), right(nullptr), height(1) {
        list.add(item);
    }
    
    // Destructor: Automatically destroys the associated list.
    ~AVLNode() {
        // The list destructor is automatically invoked.
    }
};

template <typename T> // T can be Actor* or Movie*
class AVLTree {
    private:
        AVLNode<T>* root;         // Root node of the AVL tree.
        int currentYear = 2025;   // Current year used for range queries.
        
        // Helper functions for AVL tree operations.
        AVLNode<T>* minValueNode(AVLNode<T>* node) const;
        int height(AVLNode<T>* node) const;
        int getBalance(AVLNode<T>* node) const;
        void destroyTree(AVLNode<T>* node);
        AVLNode<T>* find(int key);
        AVLNode<T>* rightRotate(AVLNode<T>* y);
        AVLNode<T>* leftRotate(AVLNode<T>* y);
        AVLNode<T>* insertItem(AVLNode<T>* node, int key, T item);
        void inOrderTraversalRangeAge(AVLNode<T>* node, int x, int y) const;
        void inOrderTraversalRange(AVLNode<T>* node, int x, int y) const;
        
    public:
        // Constructor: Creates an empty AVL tree.
        AVLTree();
        
        // Destructor: Cleans up the AVL tree and releases memory.
        ~AVLTree();
        
        // Removes an item with the specified key from the AVL tree.
        bool removeItem(int key, T item);
        
        // Inserts an item with the specified key into the AVL tree.
        void insertItem(int key, T item);

        // Checks if the AVL tree is empty
        bool isEmpty() const;
        
        // Displays actors whose birth years are within the specified range.
        void DisplayActors(int x, int y) const;
        
        // Displays movies released within a specified range.
        void DisplayMovies() const;
};

#include "templates/AVLTree.tpp"