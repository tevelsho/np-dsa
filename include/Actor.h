/*----------------------------------------------------------------------------
💻 Class: Actor (Actor.h)
Description: Represents an actor with personal details and associated movies.

Team Information:
    - Member 1: [Name], [Student ID], [Group Name]
    - Member 2: [Name], [Student ID], [Group Name]

Key Features:
    - Default and parameterized constructors for creating actor objects.
    - Setters and getters for `id`, `name`, and `year of birth`.
    - Retrieve the list of associated movies.
----------------------------------------------------------------------------*/
#pragma once
#include <string>
#include <iostream>
#include "List.h"

class Movie;
using namespace std;

class Actor {
    private:
        int id;
        string name;
        int year;

    public:
        List<Movie*> movies; 


        Actor();
        Actor(int, string, int);

        void setID(int);
        int getID();

        void setName(string);
        string getName();

        void setYearOfBirth(int);
        int getYearOfBirth();

        // Other functions
        void addMovie(Movie* movie);
        void displayMovies() const;
};

#include "templates/Actor.cpp"