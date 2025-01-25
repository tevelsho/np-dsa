#pragma once
#include "Actor.h"
#include <iostream>
#include <string>

using namespace std;

// Default Constructor
Movie::Movie() : id(0), name(""), year(0), cast() {
}

// Parameterized Constructor
Movie::Movie(int id, string name, int year) 
    : id(id), name(name), year(year), cast() {
}

// Sets the ID of the movie
void Movie::setID(int id) {
    this->id = id;
}

// Gets the ID of the movie
int Movie::getID() const {
    return id;
}

// Sets the name of the movie
void Movie::setName(string name) {
    this->name = name;
}

// Gets the name of the movie
string Movie::getName() const {
    return name;
}

// Sets the release year of the movie
void Movie::setYear(int year) {
    this->year = year;
}

// Gets the release year of the movie
int Movie::getYear() const {
    return year;
}

// Adds an actor to the cast
void Movie::addActor(Actor* actor) {
    if (actor == nullptr) {
        cerr << "Error: Attempted to add a null Actor pointer to the cast of movie ID " 
             << id << "." << endl;
        return;
    }
    cast.add(actor);
}

List<Actor*> Movie::getCast() const {
    return cast;
}

// Displays the cast
void Movie::displayCast() const {
    cout << "Cast of \"" << name << "\" (" << year << "):" << endl;

    if (cast.isEmpty()) {
        cout << "No actors in the cast." << endl;
        return;
    }

    // Iterate through the cast and display each actor's details
    for (int i = 0; i < cast.getLength(); i++) {
        Actor* actor = cast.get(i);
        cout << "ID: " << actor->getID() << ", Name: " << actor->getName() << endl;
    }
}

void Movie::addRating(double newRating) {
    ratingSystem.addRating(newRating);
}

// Get the current rating
double Movie::getRating() const {
    return ratingSystem.getRating();
}

// Get the number of ratings
int Movie::getNumRatings() const {
    return ratingSystem.getNumRatings();
}