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
#include <iostream>
#include "List.h"
#include "RatingSystem.h"
class Actor;
using namespace std;

class Actor;

class Movie {
  private:
      int id;
      string name;
      string plot;
      int year;
      RatingSystem ratingSystem;

  public:
      List<Actor*> cast;

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

      List<Actor*> getCast() const;
      double castAverageRating() const;

      // Other functions
      void addActor(Actor* actor);
      void displayCast() const;

      void addRating(double newRating);

      // Get the actor's overall rating
      double getRating() const;

      // Get the number of ratings for the actor
      int getNumRatings() const;

};

#include "templates/Movie.cpp"