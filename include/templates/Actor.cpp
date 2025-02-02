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

// ------------------- COMMENTED CODE -------------------
// This function (actorsKnownBy) was commented out in the provided code.
// It appears to find actors an actor has worked with directly and indirectly.
/*
void Actor::actorsKnownBy(List<Actor*>& actors_known) {
    try {
        cout << "RUNNING?";
        // Iterate through the movies the actor has been in.
        for (int i = 0; i < movies.getLength(); i++) {
            Movie* movie = movies.get(i);
            List<Actor*> cast = movie->getCast();

            // Add all actors in the same movie to the known actors list.
            for (int j = 0; j < cast.getLength(); j++) {
                Actor* actor = cast.get(j);
                if (actor != this && !actors_known.contains(actor)) {
                    actors_known.add(actor);
                }
            }
        }

        // Find indirect connections through actors already known.
        List<Actor*> actors_known_indirect;
        for (int i = 0; i < actors_known.getLength(); i++) {
            Actor* directActor = actors_known.get(i);
            for (int j = 0; j < directActor->getMovies().getLength(); j++) {
                Movie* movie = directActor->getMovies().get(j);
                List<Actor*> cast = movie->getCast();

                // Add all indirect connections to the list.
                for (int k = 0; k < cast.getLength(); k++) {
                    Actor* actor = cast.get(k);
                    if (actor != this && !actors_known.contains(actor) && !actors_known_indirect.contains(actor)) {
                        actors_known_indirect.add(actor);
                    }
                }
            }
        }

        // Merge indirect connections into the main known actors list.
        for (int i = 0; i < actors_known_indirect.getLength(); i++) {
            actors_known.add(actors_known_indirect.get(i));
        }

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while processing actorsKnownBy." << std::endl;
    }
}
*/