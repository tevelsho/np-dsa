#pragma once
#include <string>
#include <iostream>
#include "Movie.h"

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

// Gets the list of movies the actor is associated with
List<Movie*> Actor::getMovies() const {
    return movies;
}

void Actor::addMovie(Movie* movie) {
    movies.add(movie);
}

void Actor::displayMovies() const {
    cout << "Movies associated with " << name << ":\n";
    for (int i = 0; i < movies.getLength(); i++) {
        cout << movies.get(i)->getName() << " (" << movies.get(i)->getYear() << ")\n";
    }
}

// void Actor::actorsKnownBy(List<Actor*>& actors_known){
//     try{
//         cout << "RUNNING?";
//         for (int i = 0; i < movies.getLength(); i++) {
//             Movie* movie = movies.get(i);
//             List<Actor*> cast = movie->getCast();
//             for (int j = 0; j < cast.getLength(); j++) {
//                 Actor* actor = cast.get(j);
//                 if (actor != this && !actors_known.contains(actor)) {
//                     actors_known.add(actor);
//                 }
//             }
//         }
//         List<Actor*> actors_known_indirect;
//         for (int i = 0; i < actors_known.getLength(); i++) {
//             Actor* directActor = actors_known.get(i);
//             for (int j = 0; j < directActor->getMovies().getLength(); j++) {
//                 Movie* movie = directActor->getMovies().get(j);
//                 List<Actor*> cast = movie->getCast();
//                 for (int k = 0; k < cast.getLength(); k++) {
//                     Actor* actor = cast.get(k);
//                     if (actor != this && !actors_known.contains(actor) && !actors_known_indirect.contains(actor)) {
//                         actors_known_indirect.add(actor);
//                     }
//                 }
//             }
//         }

//         for (int i = 0; i < actors_known_indirect.getLength(); i++) {
//             actors_known.add(actors_known_indirect.get(i));
//         }
//     } catch (const std::exception& e) {
//         std::cerr << "An error occurred: " << e.what() << std::endl;
//     } catch (...) {
//         std::cerr << "An unknown error occurred while processing actorsKnownBy." << std::endl;
//     }
    
// };
