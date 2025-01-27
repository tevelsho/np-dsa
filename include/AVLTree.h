/*----------------------------------------------------------------------------
💻 Class: AVLTree (AVLTree.h)
Description: A generic AVL Tree implementation for managing `Actor` or `Movie` 
             objects, organized by a key (e.g., year of birth or release year).

Team Information:
    - Member 1: [Name], [Student ID], [Group Name]
    - Member 2: [Name], [Student ID], [Group Name]

Key Features:
    - Default constructor for creating an empty AVL tree.
    - Self-balancing binary search tree for efficient insertion, deletion, 
      and search operations.
    - Supports storage of objects like `Actor*` or `Movie*` with a key-based structure.
    - Allows in-order traversal to display actors or movies within a specified range.
    - Ensures data consistency through AVL tree rotations for balance.
----------------------------------------------------------------------------*/

#pragma once
#include "List.h"

template <class T> // T can be `Actor*` or `Movie*`
struct AVLNode {
    int key;                 // Key (e.g., year of actor birth or movie release)
    List<T> list;            // List of items (actors or movies) associated with the key
    AVLNode* left;           // Pointer to the left child
    AVLNode* right;          // Pointer to the right child
    int height;              // Height of the node

    // Constructor
    AVLNode(int key, T item)
        : key(key), list(), left(nullptr), right(nullptr), height(1) {
        list.add(item);
    }

    // Destructor
    ~AVLNode() {
        // Automatically destroys the list
    }
};

template <typename T> // T can be `Actor*` or `Movie*`
class AVLTree {
    private:
        AVLNode<T>* root;                   // Root of the AVL tree
        int currentYear = 2025;             // Reference year for age-based calculations

        // Helper methods
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
        // Constructors and Destructor
        AVLTree();                          // Default constructor
        ~AVLTree();                         // Destructor

        // Core methods
        bool removeItem(int key, T item);   // Removes an item based on its key
        void insertItem(int key, T item);  // Inserts a new item with a given key
        void DisplayActors(int x, int y) const; // Displays actors within an age range
        void DisplayMovies() const;        // Displays movies within a specified range
};

#include "templates/AVLTree.tpp"