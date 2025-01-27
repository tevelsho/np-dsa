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
#include "List.h"
#include "RatingSystem.h"

class Movie;

class Actor {
    private:
        int id;                   // Actor's unique ID
        string name;              // Actor's full name
        int year;                 // Actor's year of birth
        RatingSystem ratingSystem; // Rating system for the actor

    public:
        List<Movie*> movies;      // List of movies the actor is associated with

        // Constructors
        Actor();
        Actor(int id, string name, int year);

        // Setters and Getters
        void setID(int id);
        int getID() const;

        void setName(const string& name);
        string getName() const;

        void setYearOfBirth(int year);
        int getYearOfBirth() const;

        // Retrieve the list of associated movies
        List<Movie*> getMovies() const;

        // Movie-related functions
        void addMovie(Movie* movie);
        void displayMovies() const;

        // Rating-related functions
        void addRating(double newRating);
        double getRating() const;      // Retrieve the actor's overall rating
        int getNumRatings() const;     // Retrieve the number of ratings
};

#include "templates/Actor.cpp"
