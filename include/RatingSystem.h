/*----------------------------------------------------------------------------
 * Class: RatingSystem (RatingSystem.h)
 *
 * Description:
 *   A utility class for managing ratings for actors, movies, or other entities.
 *   Provides functionality to add new ratings, compute the average rating, and track
 *   the total number of ratings received.
 *
 * Team Information:
 *   Coder 1: Tevel Sho     | S10258591B | Group 4
 *   Coder 2: Brayden Saga  | S10258659C | Group 4
 *
 * Key Features:
 *   Allows adding new ratings and updates the average rating.
 *   Tracks the cumulative number of ratings.
 *   Provides methods to retrieve the current average rating and the rating count.
 *----------------------------------------------------------------------------*/
#pragma once

class RatingSystem {
    private:
        double rating;   // Current average rating.
        int numRatings;  // Total number of ratings received.

    public:
        // Constructor: Initializes the rating system.
        RatingSystem();

        // Adds a new rating and updates the average accordingly.
        void addRating(double newRating);

        // Retrieves the current average rating.
        double getRating() const;

        // Retrieves the total count of ratings received.
        int getNumRatings() const;
};

#include "templates/RatingSystem.cpp"