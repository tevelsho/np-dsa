#pragma once
#include "Actor.h"
#include <iostream>
#include <string>

using namespace std;

// Default Constructor
Movie::Movie() : id(0), name(""), year(0), cast() {
}

// Parameterized Constructor
Movie::Movie(int id, string name, string plot, int year) 
    : id(id), name(name), year(year), plot(plot), cast() {
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

// Sets the plot of the movie
void Movie::setPlot(string plot) {
    this->plot = plot;
}

// Gets the plot of the movie
string Movie::getPlot() const {
    return plot;
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

double Movie::castAverageRating() const {
    if (cast.isEmpty()) {
        return 0.0;
    }
    int count = 0;
    double totalRating = 0.0;
    for (int i = 0; i < cast.getLength(); i++) {
        if (cast.get(i)->getRating() == 0){
            //dont count non rated actors
            continue;
        }
        totalRating += cast.get(i)->getRating();
        count++;
    }
    if (count == 0){
        return 0.0;
    }
    return totalRating / count;
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