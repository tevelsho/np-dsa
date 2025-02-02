// Constructor: Initializes the rating system with a default rating of 0.0 and sets the number of ratings to zero.
RatingSystem::RatingSystem() : rating(0.0), numRatings(0) {
}

// Adds a new rating to the system and updates the overall rating average.
void RatingSystem::addRating(double newRating) {
    rating = (rating * numRatings + newRating) / (numRatings + 1);
    numRatings++;
}

// Retrieves the current average rating of the entity.
double RatingSystem::getRating() const {
    return rating;
}

// Retrieves the total number of ratings that have been recorded.
int RatingSystem::getNumRatings() const {
    return numRatings;
}
