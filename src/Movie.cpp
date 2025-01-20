// Movie.cpp      
#include "Movie.h"
#include <iostream>

// Constructor
Movie::Movie(int Id, const std::string& Title, int Year)
    : id(Id), title(Title), year(Year), cast() {}

// Destructor
Movie::~Movie() {
    
}

// Getters
int Movie::getId() const {
    return id;
}

std::string Movie::getTitle() const {
    return title;
}

int Movie::getYear() const {
    return year;
}

// Adds an Actor to the cast
void Movie::addActor(Actor* actor) {
    if (actor == nullptr) {
        std::cerr << "Error: Attempted to add a null Actor pointer to the cast of movie ID " 
                  << id << "." << std::endl;
        return;
    }
    cast.add(actor);
}

// Displays the cast
void Movie::displayCast() const {
    std::cout << "Cast of \"" << title << "\" (" << year << "):" << std::endl;
    cast.print();
}