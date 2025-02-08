#include "Movie.h"

// Default Constructor: Initializes an Actor object with default values.
Actor::Actor() : id(0), name(""), year(0), movies() {}

// Parameterized Constructor: Initializes an Actor object with specified values.
Actor::Actor(int id, string name, int year) 
    : id(id), name(name), year(year), movies() {}

// Sets the actor's unique identifier.
void Actor::setID(int id) {
    this->id = id;
}

// Retrieves the actor's unique identifier.
int Actor::getID() {
    return id;
}

// Sets the name of the actor.
void Actor::setName(string name) {
    this->name = name;
}

// Retrieves the name of the actor.
string Actor::getName() {
    return name;
}

// Sets the year of birth of the actor.
void Actor::setYearOfBirth(int year) {
    this->year = year;
}

// Retrieves the year of birth of the actor.
int Actor::getYearOfBirth() {
    return year;
}

// Returns the list of movies associated with the actor.
List<Movie*> Actor::getMovies() const {
    return movies;
}

// Adds a movie to the actor's list of associated movies.
void Actor::addMovie(Movie* movie) {
    movies.add(movie);
}

// Removes a movie from the actor's list of associated movies.
bool Actor::removeMovie(Movie* movie) {
    if (movie == nullptr) {
        cerr << "Error: Attempted to remove a null Actor pointer from the cast of movie ID " 
             << id << "." << endl;
        return false;
    } else if (!movies.contains(movie)){
        return false;
    }
    movies.remove(movie);
    return true;
}

// Displays all movies associated with the actor.
void Actor::displayMovies() const {
    cout << "Movies associated with " << name << ":\n";

    if (movies.isEmpty()) {
        cout << "No movies found.\n";
        return;
    }

    for (int i = 0; i < movies.getLength(); i++) {
        cout << movies.get(i)->getName() << " (" << movies.get(i)->getYear() << ")\n";
    }
}

// Adds a new rating to the actor's rating system.
void Actor::addRating(double newRating) {
    ratingSystem.addRating(newRating);
}

// Retrieves the current average rating of the actor.
double Actor::getRating() const {
    return ratingSystem.getRating();
}

// Retrieves the total number of ratings received by the actor.
int Actor::getNumRatings() const {
    return ratingSystem.getNumRatings();
}
