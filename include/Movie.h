/*----------------------------------------------------------------------------
💻 Class: Movie (Movie.h)
Description: Represents a movie with its details and the associated cast.

Team Information:
    - Member 1: [Name], [Student ID], [Group Name]
    - Member 2: [Name], [Student ID], [Group Name]

Key Features:
    - Default and parameterized constructors for creating movie objects.
    - Comprehensive setters and getters for managing `id`, `title`, and `year of release`.
    - Maintains a list of associated actors (cast) with functionalities to add 
      and display them.
    - Includes a rating system for movies with the ability to add, retrieve, 
      and manage ratings.
    - Calculates the average rating of the cast associated with the movie.
----------------------------------------------------------------------------*/

#pragma once
#include <string>
#include "List.h"
#include "RatingSystem.h"

class Actor;

class Movie {
    private:
        int id;                   // Unique identifier for the movie
        std::string name;         // Movie title
        int year;                 // Year of release
        RatingSystem ratingSystem; // Rating system for the movie

    public:
        List<Actor*> cast;        // List of actors associated with the movie

        // Constructors
        Movie();                  // Default constructor
        Movie(int id, std::string name, int year); // Parameterized constructor

        // Setters and Getters
        void setID(int id);       // Sets the movie ID
        int getID() const;        // Retrieves the movie ID

        void setName(const std::string& name); // Sets the movie title
        std::string getName() const;           // Retrieves the movie title

        void setYear(int year);   // Sets the release year
        int getYear() const;      // Retrieves the release year

        // Cast-related functions
        List<Actor*> getCast() const;         // Retrieves the list of associated actors
        double castAverageRating() const;     // Calculates the average rating of the cast
        void addActor(Actor* actor);          // Adds an actor to the cast
        void displayCast() const;             // Displays the list of associated actors

        // Rating-related functions
        void addRating(double newRating);     // Adds a rating to the movie
        double getRating() const;             // Retrieves the movie's overall rating
        int getNumRatings() const;            // Retrieves the number of ratings for the movie
};

#include "templates/Movie.cpp"