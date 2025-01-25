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