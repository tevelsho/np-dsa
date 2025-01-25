
// Constructor
RatingSystem::RatingSystem() : rating(0.0), numRatings(0) {
}

// Add a new rating
void RatingSystem::addRating(double newRating) {
    rating = (rating * numRatings + newRating) / (numRatings + 1);
    numRatings++;
}

// Get the current rating
double RatingSystem::getRating() const {
    return rating;
}

// Get the number of ratings
int RatingSystem::getNumRatings() const {
    return numRatings;
}