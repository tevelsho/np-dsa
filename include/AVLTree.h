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