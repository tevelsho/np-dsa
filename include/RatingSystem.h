/*----------------------------------------------------------------------------
💻 Class: RatingSystem (RatingSystem.h)
Description: A utility class to manage ratings for actors, movies, or other entities.

Team Information:
    - Member 1: [Name], [Student ID], [Group Name]
    - Member 2: [Name], [Student ID], [Group Name]

Key Features:
    - Allows adding new ratings and calculates the average rating.
    - Tracks the total number of ratings received.
    - Provides methods to retrieve the current rating and the total count of ratings.
----------------------------------------------------------------------------*/

#pragma once

class RatingSystem {
private:
    double rating;    // Current average rating
    int numRatings;   // Total number of ratings received

public:
    // Constructor
    RatingSystem();                // Initializes the rating and count to 0

    // Rating-related functions
    void addRating(double newRating); // Adds a new rating and updates the average
    double getRating() const;         // Retrieves the current average rating
    int getNumRatings() const;        // Retrieves the total number of ratings
};

#include "templates/RatingSystem.cpp"