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
#include <string>
#include <iostream>
#include "List.h"
using namespace std;

template<class T> //T will either be Actor* or Movie*
struct AVLNode 
{
    int key; //year of actor birth or movie release
    List<T> list;
    AVLNode* left;
    AVLNode* right;
    int height;

    //
    AVLNode(int key, T item) 
        : key(key), list(),
          left(nullptr), right(nullptr), height(1) {
        list.add(item);
    }
    
    // Destructor
    ~AVLNode() {
        //automatically destroys the list
    }
};

template <typename T> //specify Actor* or Movie*
class AVLTree {
    private:
        AVLNode<T>* root;
        int currentYear = 2025;
        
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
        AVLTree();
        ~AVLTree();
        bool removeItem(int key, T item);
        void insertItem(int key, T item);
        void DisplayActors(int x, int y) const;
        void DisplayMovies() const;
};

#include "templates/AVLTree.tpp"