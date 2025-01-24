/*----------------------------------------------------------------------------
💻 Class: Actor (Actor.h)
Description: Represents a movie with its details and the actors involved.
 
Team Information:
    - Member 1: [Name], [Student ID], [Group Name]
    - Member 2: [Name], [Student ID], [Group Name]

Key Features:
    - Stores details about the movie (title, plot, release year).
    - Maintains a list of actors who starred in the movie.
    - Provides methods to update movie details and retrieve actor information.
----------------------------------------------------------------------------*/
#pragma once
#include <string>
#include <iostream>
#include "List.h"
using namespace std;

template<class T>
struct Node {
        T item; 
        Node* next; 
};

template<class T> //T will either be Actor* or Movie*
struct AVLNode 
{
    int key; //year of actor birth or movie release
    List<T>* list;
    AVLNode* left;
    AVLNode* right;
    int height;

    //
    AVLNode(int key, T* item) 
        : key(key), list(new List<T*>()),
          left(nullptr), right(nullptr), height(1) {
        list->append(item);
    }
    
    // Destructor
    ~AVLNode() {
        if (list) delete list;
    }
};

template <typename T> //specify Actor* or Movie*

class AVLTree {
private:
    AVLNode<T>* root;
    int currentYear = 2025;
    
    int height(AVLNode<T>* node) const;

public:
    AVLTree();
    ~AVLTree();
    void insertItem(int key, T* item);
    void destroyTree(AVLNode<T>* node);
    int height(AVLNode<T>* node) const;
    int getBalance(AVLNode<T>* node) const;
    AVLNode<T>* rightRotate(AVLNode<T>* y);
    AVLNode<T>* leftRotate(AVLNode<T>* y);
    void insertItem(int key, T* item);
    AVLNode<T>* insertItem(AVLNode<T>* node, int key, T* item);
    AVLNode<T>* minValueNode(AVLNode<T>* node) const;
    void DisplayActors(int x, int y) const;
    void DisplayMovies() const;
    void inOrderTraversalRangeAge(AVLNode<T>* node, int x, int y) const;
    void inOrderTraversalRange(AVLNode<T>* node, int x, int y) const;

};

#include "templates/AVLTree.tpp"