#include "Actor.h"

// Default Constructor: Initializes a Movie object with default values.
Movie::Movie() : id(0), name(""), year(0), plot(""), cast() {}

// Parameterized Constructor: Initializes a Movie object with specified values.
Movie::Movie(int id, string name, string plot, int year) 
    : id(id), name(name), year(year), plot(plot), cast() {}

// Sets the movie's unique identifier.
void Movie::setID(int id) {
    this->id = id;
}

// Retrieves the movie's unique identifier.
int Movie::getID() const {
    return id;
}

// Sets the title of the movie.
void Movie::setName(string name) {
    this->name = name;
}

// Retrieves the title of the movie.
string Movie::getName() const {
    return name;
}

// Sets the plot of the movie
void Movie::setPlot(string plot) {
    this->plot = plot;
}

// Gets the plot of the movie
string Movie::getPlot() const {
    return plot;
}

// Sets the release year of the movie.
void Movie::setYear(int year) {
    this->year = year;
}

// Retrieves the release year of the movie.
int Movie::getYear() const {
    return year;
}

bool Movie::hasActor(Actor* actor) const {
    return cast.contains(actor);
}

// Adds an actor to the movie's cast list, ensuring the actor pointer is valid.
void Movie::addActor(Actor* actor) {
    if (actor == nullptr) {
        cerr << "Error: Attempted to add a null Actor pointer to the cast of movie ID " 
             << id << "." << endl;
        return;
    }
    cast.add(actor);
}

// Removes an actor from the movie's cast list, ensuring the actor pointer is valid.
bool Movie::removeActor(Actor* actor) {
    if (actor == nullptr) {
        cerr << "Error: Attempted to remove a null Actor pointer from the cast of movie ID " 
             << id << "." << endl;
        return false;
    } else if (!cast.contains(actor)){
        return false;
    }
    cast.remove(actor);
    return true;
}

// Retrieves the list of actors in the movie's cast.
List<Actor*> Movie::getCast() const {
    return cast;
}

// Computes and returns the average rating of all actors in the movie's cast.
// Actors with a rating of 0 are excluded from the calculation.
double Movie::castAverageRating() const {
    if (cast.isEmpty()) {
        return 0.0;
    }

    int count = 0;
    double totalRating = 0.0;

    for (int i = 0; i < cast.getLength(); i++) {
        if (cast.get(i)->getRating() == 0) {
            continue; // Ignore unrated actors.
        }
        totalRating += cast.get(i)->getRating();
        count++;
    }

    return (count == 0) ? 0.0 : totalRating / count;
}

// Displays all actors in the movie's cast, including their ID and name.
void Movie::displayCast() const {
    cout << "Cast of \"" << name << "\" (" << year << "):" << endl;

    if (cast.isEmpty()) {
        cout << "No actors in the cast." << endl;
        return;
    }

    for (int i = 0; i < cast.getLength(); i++) {
        Actor* actor = cast.get(i);
        cout << "ID: " << actor->getID() << ", Name: " << actor->getName() << endl;
    }
}

// Adds a new rating to the movie, updating its average rating accordingly.
void Movie::addRating(double newRating) {
    ratingSystem.addRating(newRating);
}

// Retrieves the movie's current rating.
double Movie::getRating() const {
    return ratingSystem.getRating();
}

// Retrieves the total number of ratings submitted for the movie.
int Movie::getNumRatings() const {
    return ratingSystem.getNumRatings();
}