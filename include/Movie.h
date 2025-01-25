/*----------------------------------------------------------------------------
💻 Class: Movie (Movie.h)
Description: Represents a movie with its details and associated cast.

Team Information:
    - Member 1: [Name], [Student ID], [Group Name]
    - Member 2: [Name], [Student ID], [Group Name]

Key Features:
    - Default and parameterized constructors for creating movie objects.
    - Setters and getters for `id`, `title`, and `year of release`.
    - Add actors to the cast.
    - Display the list of associated actors (cast).
----------------------------------------------------------------------------*/
#pragma once

#include <string>
#include <iostream>
#include "List.h"
class Actor;
using namespace std;

class Actor;
class Movie {
    private:
        int id;
        string name;
        int year;

    public:
        List<Actor*> cast;


        Movie();
        Movie(int, string, int);

        // Setters and Getters
        void setID(int);
        int getID() const;

        void setName(string);
        string getName() const;

        void setYear(int);
        int getYear() const;

        List<Actor*> getCast() const;

        // Other functions
        void addActor(Actor* actor);
        void displayCast() const;
};

#include "templates/Movie.cpp"
