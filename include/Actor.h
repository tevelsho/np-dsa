/*
----------------------------------------------------------------------------
Class: Actor (Actor.h)
Description: Represents a movie with its details and the actors involved.
 
Team Information:
    - Member 1: [Name], [Student ID], [Group Name]
    - Member 2: [Name], [Student ID], [Group Name]

Key Features:
    - Stores details about the movie (title, plot, release year).
    - Maintains a list of actors who starred in the movie.
    - Provides methods to update movie details and retrieve actor information.
----------------------------------------------------------------------------
*/

#pragma once
#include <string>
#include <iostream>
#include "List.h"
#include "Movie.h"
using namespace std;

class Actor {
    private:
        string name;
        int yearOfBirth;
        List<Movie*> movies; 

    public:
        Actor();
        Actor(string, int);
        void setName(string);
        string getName();
        void setYearOfBirth(int);
        int getYearOfBirth();
};