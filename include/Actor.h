/*----------------------------------------------------------------------------
 * Class: Actor (Actor.h)
 *
 * Description:
 *   Represents an actor with personal details, associated movies, and a rating system.
 *
 * Team Information:
 *   Coder 1: Tevel Sho     | S10258591B | Group 4
 *   Coder 2: Brayden Saga  | S10258659C | Group 4
 *
 * Key Features:
 *   Provides default and parameterized constructors for initializing actor objects.
 *   Offers comprehensive getters and setters for managing the actor's ID, name, and year of birth.
 *   Maintains a list of associated movies with functionalities to add and display them.
 *   Integrates a rating system for actors, enabling addition and retrieval of ratings.
 *----------------------------------------------------------------------------*/
#pragma once

#include <string>
#include <iostream>
#include "List.h"
#include "RatingSystem.h"

// Forward declaration of Movie class.
class Movie;
using namespace std;

class Actor {
    private:
        int id;            // Unique identifier for the actor.
        string name;       // Name of the actor.
        int year;          // Year of birth.
        
        RatingSystem ratingSystem; // Manages the actor's ratings.
        
    public:
        // List of movies the actor is associated with.
        List<Movie*> movies; 

        // Constructor: Initialize an empty Actor object
        Actor();

        // Constructor: Creates an Actor object with the specified id, name, and year of birth.
        Actor(int, string, int);

        // Setters and Getters for actor attributes.
        void setID(int);
        int getID();

        void setName(string);
        string getName();

        void setYearOfBirth(int);
        int getYearOfBirth();

        // Retrieves the list of movies associated with the actor.
        List<Movie*> getMovies() const;
        
        // Other Member Functions
        // Adds a movie to the actor's list.
        void addMovie(Movie* movie);
        
        // Displays the movies the actor has starred in.
        void displayMovies() const;

        // Adds a new rating to the actor.
        void addRating(double newRating);

        // Retrieves the actor's overall rating.
        double getRating() const;

        // Retrieves the number of ratings the actor has received.
        int getNumRatings() const;
};

#include "templates/Actor.cpp"