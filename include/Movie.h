/*----------------------------------------------------------------------------
 * Class: Movie (Movie.h)
 *
 * Description:
 *   Represents a movie with its details and associated cast.
 *
 * Team Information:
 *   Coder 1: Tevel Sho     | S10258591B | Group 4
 *   Coder 2: Brayden Saga  | S10258659C | Group 4
 *
 * Key Features:
 *   Provides both default and parameterized constructors for creating movie objects.
 *   Offers comprehensive setters and getters for managing movie ID, title, and release year.
 *   Maintains a list of associated actors (cast) with functionalities to add and display them.
 *   Integrates a rating system for movies with methods to add, retrieve, and manage ratings.
 *   Calculates the average rating of the cast associated with the movie.
 *----------------------------------------------------------------------------*/
#pragma once

#include <string>
#include <iostream>
#include "List.h"
#include "RatingSystem.h"

// Forward declaration of Actor class.
class Actor;
using namespace std;

class Movie {
  private:
      int id;                    // Unique identifier for the movie.
      string name;               // Title of the movie.
      string plot;
      int year;                  // Release year of the movie.
      RatingSystem ratingSystem; // Manages the movie's ratings.

  public:
      List<Actor*> cast;         // List of actors (cast) associated with the movie.

      Movie();
      Movie(int, string, string, int);

      // Setters and Getters
      void setID(int);
      int getID() const;

      void setName(string);
      string getName() const;

      void setPlot(string);
      string getPlot() const;

      void setYear(int);
      int getYear() const;

      // Retrieves the cast list.
      List<Actor*> getCast() const;

      // Calculates and returns the average rating of the cast.
      double castAverageRating() const;

      // Other Member Functions
      // Adds an actor to the movie's cast.
      void addActor(Actor* actor);

      // Displays the cast of the movie.
      void displayCast() const;

      // Adds a new rating to the movie.
      void addRating(double newRating);

      // Retrieves the movie's overall rating.
      double getRating() const;

      // Retrieves the number of ratings the movie has received.
      int getNumRatings() const;
};

#include "templates/Movie.cpp"