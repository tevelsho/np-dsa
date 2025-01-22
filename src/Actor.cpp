#include <string>
#include <iostream>
#include "Actor.h"

// Default Constructor
Actor::Actor() : id(0), name(""), year(0), movies() {
}

// Parameterized Constructor
Actor::Actor(int id, string name, int year) 
    : id(id), name(name), year(year), movies() {
}

// Sets the ID of the actor
void Actor::setID(int id) {
    this->id = id;
}

// Gets the ID of the actor
int Actor::getID() {
    return id;
}

// Sets the name of the actor
void Actor::setName(string name) {
    this->name = name;
}

// Gets the name of the actor
string Actor::getName() {
    return name;
}

// Sets the year of birth of the actor
void Actor::setYearOfBirth(int year) {
    this->year = year;
}

// Gets the year of birth of the actor
int Actor::getYearOfBirth() {
    return year;
}