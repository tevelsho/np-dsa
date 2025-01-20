#include <iostream>
#include <limits>
#include "ActorManager.h"

using namespace std;

void ActorManager::createNewActor() {
    List<Actor*> actorList;

    string name;
    int yearOfBirth;

    // Prompt user for name and year of birth of new actor
    cout << "Enter the Actor's Name (e.g., John Tan):";
    getline(cin, name);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter the Actor's Year Of Birth (e.g., 1998):";
    cin >> yearOfBirth;

    Actor* actor = new Actor(name, yearOfBirth);
    actorList.add(actor);

    cout << "Actor '" << name << "' has been added!\n";
}
