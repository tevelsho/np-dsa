#include <string>
#include <iostream>
#include "Actor.h"

Actor::Actor() {

}

Actor::Actor(string n, int y) : name(n), year(y), movies() {
    
}

void Actor::setName(string n) {
    name = n;
}

string Actor::getName() {
    return name;
}

void Actor::setYearOfBirth(int y) {
    year = y;
}

int Actor::getYearOfBirth() {
    return year;
}