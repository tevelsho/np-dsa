/*
----------------------------------------------------------------------------
Adds an actor to the movie's actor list.

@param actorID (int): The unique ID of the actor to be added.

@return void

Description:
    - Appends the actor's ID to the linked list `actorIDs`.
    - Ensures dynamic storage for multiple actors.
    
Example Usage:
    - Movie.addActor(101);  // Adds actor with ID 101 to the movie.
----------------------------------------------------------------------------
*/

#include <string>
#include <iostream>
#include "Actor.h"

Actor::Actor() {

}

Actor::Actor(string n, int y) : name(n), yearOfBirth(y) {

}

void Actor::setName(string n) {
    name = n;
}

string Actor::getName() {
    return name;
}

void Actor::setYearOfBirth(int y) {
    yearOfBirth = y;
}

int Actor::getYearOfBirth() {
    return yearOfBirth;
}