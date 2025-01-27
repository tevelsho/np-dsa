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
        double rating;    // Current rating
        int numRatings;   // Number of ratings received

    public:
        // Constructor
        RatingSystem();

        // Add a new rating
        void addRating(double newRating);

        // Get the current rating
        double getRating() const;

        // Get the number of ratings
        int getNumRatings() const;
};

#include "templates/RatingSystem.cpp"