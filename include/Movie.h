// Movie.h
#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include "Actor.h" // Ensure Actor.h is correctly included
#include "List.h" 
// Forward declaration of Actor class
// If Actor.h is already included above, this is optional
// class Actor;

class Movie {
public:
    // Constructor
    Movie(int id, const std::string& title, int year);

    // Destructor
    ~Movie();

    // Getters
    int getId() const;
    std::string getTitle() const;
    int getYear() const;

    // Adds an Actor to the cast
    void addActor(Actor* actor);

    // Displays the cast
    void displayCast() const;

private:
    // Node structure for the linked list of actors
    int id;
    std::string title;
    int year;
    List<Actor*> cast; // Head of the linked list

    // Disable copy constructor and assignment operator to prevent shallow copies
    Movie(const Movie& other);
    Movie& operator=(const Movie& other);
};

#endif // MOVIE_H
