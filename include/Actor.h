/*----------------------------------------------------------------------------
💻 Class: Actor (Actor.h)
Description: Represents an actor with personal details, associated movies, 
             and a rating system.

Team Information:
    - Member 1: [Name], [Student ID], [Group Name]
    - Member 2: [Name], [Student ID], [Group Name]

Key Features:
    - Default and parameterized constructors for initializing actor objects.
    - Comprehensive getters and setters for managing `id`, `name`, and `year of birth`.
    - Maintains a list of associated movies with functionalities to add and display them.
    - Includes a rating system for actors with the ability to add, retrieve, 
      and manage ratings.
----------------------------------------------------------------------------*/
#pragma once
#include <string>
#include <iostream>
#include "List.h"
#include "RatingSystem.h"

class Movie;
using namespace std;

class Movie;
class Actor {
    private:
        int id;
        string name;
        int year;

        //Rating System
        RatingSystem ratingSystem;

    public:
        // List of movies the actor is associated with
        List<Movie*> movies; 


        // Constructors
        Actor();
        Actor(int, string, int);

        // Setters and Getters
        void setID(int);
        int getID();

        void setName(string);
        string getName();

        void setYearOfBirth(int);
        int getYearOfBirth();

        List<Movie*> getMovies() const;
        
        // Other functions
        void addMovie(Movie* movie);
        void displayMovies() const;

        void addRating(double newRating);

        // Get the actor's overall rating
        double getRating() const;

        // Get the number of ratings for the actor
        int getNumRatings() const;

};

#include "templates/Actor.cpp"