#include "Movie.h"
#include <iostream>
#include <string>

using namespace std;

// Default Constructor
Movie::Movie() : id(0), title(""), year(0), cast() {
}

// Parameterized Constructor
Movie::Movie(int id, string title, int year) 
    : id(id), title(title), year(year), cast() {
}

// Sets the ID of the movie
void Movie::setID(int id) {
    this->id = id;
}

// Gets the ID of the movie
int Movie::getID() const {
    return id;
}

// Sets the title of the movie
void Movie::setTitle(string title) {
    this->title = title;
}

// Gets the title of the movie
string Movie::getTitle() const {
    return title;
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

// Displays the cast
void Movie::displayCast() const {
    cout << "Cast of \"" << title << "\" (" << year << "):" << endl;

    if (cast.isEmpty()) {
        cout << "No actors in the cast." << endl;
        return;
    }

    // Iterate through the cast and display each actor's details
    auto currentNode = cast.getHead();
    while (currentNode != nullptr) {
        Actor* actor = currentNode->item;
        if (actor != nullptr) {
            cout << " - " << actor->getName() << " (ID: " << actor->getID() 
                 << ", Year of Birth: " << actor->getYearOfBirth() << ")" << endl;
        }
        currentNode = currentNode->next;
    }
}