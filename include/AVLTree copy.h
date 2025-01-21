// AVLTree.h
#pragma once
#include <string>
#include <iostream>
#include "List.h"
using namespace std;

template <typename T> //specify Actor* or Movie*

class AVLTree {
private:
    AVLNode* root;
    int currentYear = 2025;
    
    int height(AVLNode* node) const;

public:
    AVLTree();
    ~AVLTree();
    void insertItem(int key, T* item);
    void destroyTree(AVLNode* node);

    void DisplayActors(int x, int y);
    void DisplayMovies();
};