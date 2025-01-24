/*----------------------------------------------------------------------------
👨🏻‍💻 DATA STRUCTURES & ALGORITHMS ASSIGNMENT

Team Information:
    - Coder 1: Tevel Sho, S10258591B, Group 4
    - Coder 2: Brayden Saga, S10258659C, Group 4
----------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include "Dictionary.h"
#include "List.h"
#include "Actor.h"
#include "Movie.h"
#include "AVLTree.h"
#include "DynamicArray.h"

using namespace std;

// Maximum number of admin accounts
const int MAX_ADMINS = 1;

// Admin credentials (hardcoded, stored in array)
char adminUsername[MAX_ADMINS][20] = {"admin"};
char adminPassword[MAX_ADMINS][20] = {"password"};

// Function prototypes
bool authenticateAdmin();
Actor* findActorByName(Dictionary<string, int>& actorNameToIdMap, string actorName, Dictionary<int, Actor*>& actorIdToActorMap);
Movie* findMovieByName(Dictionary<string, int>& movieNameToIdMap, string movieName, Dictionary<int, Movie*>& movieIdToMovieMap);
void adminMenu(Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie);
void userMenu(Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie);
void readCSV(string fileName, Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Actor*>& yearToActor, AVLTree<Movie*>& yearToMovie);
bool addNewActor(int id, int birth, string name, Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor);
bool addNewMovie(int id, int year, string name, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie);
bool addActorToMovie(Actor* actor, Movie* movie);
void updateActorDetails(Actor* actorToUpdate, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor);
void updateMovieDetails(Movie* movieToUpdate, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie);
void displayActorsByAgeRange(int x, int y, AVLTree<Actor*>& yearToActor);
void displayRecentMovies(AVLTree<Movie*>& yearToMovie);
void displayMoviesByActor(); 
void displayActorsByMovie(); 
void displayActorsKnownBy(Actor* actor);
void displayActorsKnownByHelper(Actor* actor, DynamicArray& actors_known);
void setActorRating();
void setMovieRating();
void recommendMoviesByRating();
void recommendActorsByRating();

/*----------------------------------------------------------------------------
Main function of the program.

@return int: Returns 0 upon successful execution.

Description:
    - Initializes the program and determines if the user is an admin or a 
      normal user based on input.
    - Redirects user to either adminMenu() or userMenu() accordingly.
----------------------------------------------------------------------------*/
int main() {
    // List<Actor> actorList;
    // List<Movie> movieList;

    // Dictionary<int, List<Actor>> movieToActor;

    Dictionary<int, Actor*> actorIdToActorMap;
    Dictionary<string, int> actorNameToIdMap;

    Dictionary<int, Movie*> movieIdToMovieMap;
    Dictionary<string, int> movieNameToIdMap;

    //AVL TREE FOR YEAR TO ACTOR 
    AVLTree<Actor*> yearToActor;
    //AVL TREE FOR YEAR TO MOVIE
    AVLTree<Movie*> yearToMovie;



    char isAdmin;
    cout << "Are you an administrator? (y/n): ";
    cin >> isAdmin;
    
    if (isAdmin == 'y' || isAdmin == 'Y') {
        bool isAdminAuthenticated = false;

        for (int attempts = 0; attempts < 3; attempts++) {
            if (authenticateAdmin()) {
                isAdminAuthenticated = true;
                break;
            } else {
                cout << "Invalid credentials! Try again (" << (2 - attempts) << " attempts remaining).\n";
            }
        }

        if (isAdminAuthenticated) {
            cout << "Welcome, Admin!\n";
            adminMenu(actorIdToActorMap, actorNameToIdMap, yearToActor, movieIdToMovieMap, movieNameToIdMap, yearToMovie);
        } else {
            cout << "Failed all attempts! You will be logged in as a normal user.\n";
            userMenu(actorIdToActorMap, actorNameToIdMap, yearToActor, movieIdToMovieMap, movieNameToIdMap, yearToMovie);  
        }
    } else {
        cout << "Welcome, User!\n";
        userMenu(actorIdToActorMap, actorNameToIdMap, yearToActor, movieIdToMovieMap, movieNameToIdMap, yearToMovie);  
    }

    return 0;
}

/*----------------------------------------------------------------------------
Authenticates an admin user.

@return bool: Returns true if the credentials match, otherwise false.

Description:
    - Prompts the user to enter a username and password.
    - Compares the entered credentials with the hardcoded admin credentials.
    - Grants admin access if the credentials are correct.
----------------------------------------------------------------------------*/
bool authenticateAdmin() {
    return true; //Temporary
    char username[20], password[20];

    // Prompt user to enter in credentials
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password";
    cin >> password;

    // Check against stored credentials
    for (int i = 0; i < MAX_ADMINS; i++) {
        bool usernameMatch = true;
        bool passwordMatch = false;

        // Compare username
        for (int j = 0; username[j] != '\0' || adminUsername[i][j] != '\0'; j++) {
            if (username[j] != adminUsername[i][j]) {
                usernameMatch = false;
                break;
            }
        }

        // Compare password
        for (int j = 0; password[j] != '\0' || adminPassword[i][j] != '\0'; j++) {
            if (password[j] != adminPassword[i][j]) {
                passwordMatch = false;
                break;
            }
        }

        // If username and password match, return true
        if (usernameMatch && passwordMatch) {
            return true;
        }
    }
    return false;
}

Actor* findActorByName(Dictionary<string, int>& actorNameToIdMap, string actorName, Dictionary<int, Actor*>& actorIdToActorMap) {
    int actorID = actorNameToIdMap.get(actorName);
    return actorIdToActorMap.get(actorID);
}

Movie* findMovieByName(Dictionary<string, int>& movieNameToIdMap, string movieName, Dictionary<int, Movie*>& movieIdToMovieMap) {
    int movieID = movieNameToIdMap.get(movieName);
    return movieIdToMovieMap.get(movieID);
}

/*----------------------------------------------------------------------------
Displays the admin menu and handles admin operations.

@return void

Description:
    - Allows the admin to perform various operations such as adding actors, 
      adding movies, updating details, and exiting the application.
    - Continues to prompt the admin until they choose to exit.
----------------------------------------------------------------------------*/
void adminMenu(Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie) {
    int option;

    do {
        cout << "\n=============================================\n";
        cout << "       🎬 Silver Village Admin Menu               \n";
        cout << "=============================================\n";
        cout << " [1]  ➤ Add a New Actor\n";
        cout << " [2]  ➤ Add a New Movie\n";
        cout << " [3]  ➤ Assign an Actor to a Movie\n";
        cout << " [4]  ➤ Update Actor Details\n";
        cout << " [5]  ➤ Update Movie Details\n";
        cout << " [0]  ➤ Exit Application\n";
        cout << "=============================================\n";
        cout << "Please select an option by entering the number: ";
        cin >> option;
        switch (option) {
            case 0: {
                cout << " Thank you for visiting Silver Village! Hope to see you next time!";
                break;
            }
            case 1: {
                cout << "Adding a new actor...\n";
                int actor_id, actor_birth;
                string actor_name;

                // Prompt user for id, name, and birth for new actor
                cout << "Enter new actor's ID: ";
                cin >> actor_id;

                cout << "Enter new actor's name: ";
                getline(cin, actor_name);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter new actor's year of birth: ";
                cin >> actor_birth;

                addNewActor(actor_id, actor_birth, actor_name, actorIdToActorMap, actorNameToIdMap, yearToActor);
                break;
            }
            case 2:{
                int movie_id, movie_year;
                string movie_name;

                // Prompt user for id, movie, and year for new movie
                cout << "Enter new movie's ID: ";
                cin >> movie_id;

                cout << "Enter new movie's name: ";
                getline(cin, movie_name);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter new movie's release year: ";
                cin >> movie_year;

                addNewMovie(movie_id, movie_year, movie_name, movieIdToMovieMap, movieNameToIdMap, yearToMovie);
                break;
            }
            case 3:{
                string actor_name, movie_name;
                cout << "Enter the actor's name: ";
                cin >> actor_name;

                cout << "Enter the movie's name: ";
                cin >> movie_name;

                Actor* actor = findActorByName(actorNameToIdMap, actor_name, actorIdToActorMap);
                Movie* movie = findMovieByName(movieNameToIdMap, movie_name, movieIdToMovieMap);
                if (actor != nullptr && movie != nullptr) {
                    addActorToMovie(actor, movie);
                } else {
                    cout << "Error: Actor or Movie not found. Please ensure the Name is correct.\n";
                }
                break;
            }
            case 4:{
                string actorName;
                // Prompt user for actor name to update actor's details
                cout << "Enter the actor's name to update: ";
                cin >> actorName;
                Actor* actorToUpdate = findActorByName(actorNameToIdMap, actorName, actorIdToActorMap);

                if (actorToUpdate != nullptr) {
                    updateActorDetails(actorToUpdate, actorNameToIdMap, yearToActor);
                }
                break;
            }
            case 5: {
                string movieName;

                cout << "Enter the movie's name to update: ";
                cin >> movieName;
                Movie* movieToUpdate = findMovieByName(movieNameToIdMap, movieName, movieIdToMovieMap);

                if (movieToUpdate != nullptr) {
                    updateMovieDetails(movieToUpdate, movieNameToIdMap, yearToMovie);
                }
                break;
            }
            default:
                cout << "Invalid choice! Try again.\n"; 

        }

    } while (option != 0);
}




/*----------------------------------------------------------------------------
Reads and processes a CSV file based on its type.

@param fileName (string): The name of the CSV file to read. Supported file names:
    - "actors.csv": Contains actor information with columns (id, name, birth).
    - "cast.csv": Contains cast information with columns (person_id, movie_id).
    - "movies.csv": Contains movie information with columns (id, title, year).

@return void

Description:
    - Opens the specified CSV file and checks for successful access.
    - Skips the header line and processes data line by line.
    - Dynamically handles file-specific data structures:
        - For "actors.csv", reads ID, Name, and Birth Year.
        - For "cast.csv", reads Person ID and Movie ID.
        - For "movies.csv", reads ID, Title, and Year.
    - Converts numeric data (e.g., IDs, years) from string to integer using `stoi`.
    - Outputs the parsed data directly to the console.
    - Handles unsupported file names with an error message.

Error Handling:
    - If the file cannot be opened, an error message is displayed, and the function exits.
    - If an unsupported file name is provided, an appropriate error message is shown.
-----------------------------------------------------------------------------*/
void readCSV(string fileName, Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Actor*>& yearToActor, AVLTree<Movie*>& yearToMovie) {
    // File pointer
    fstream fin;

    // Open actors.csv
    fin.open(fileName, ios::in);

    // Check if the file is opened
    if (!fin.is_open()) {
        cout << "Error: Could not open file!" << endl;
        return;
    }

    string line, word;

    // Skip the header line
    getline(fin, line);

    if (fileName == "actors.csv") {
        // Read data line by line
        while (getline(fin, line)) {
            stringstream s(line);

            // Read and parse each column as string and convert to int
            string name, temp;
            int id, birth;

            getline(s, temp, ',');
            id = stoi(temp);

            getline(s, name, ',');

            getline(s, temp, ','); 
            birth = stoi(temp);  

            // Create an actor object
            Actor* actor = new Actor(id, name, birth);

            // Map the ID to the Actor pointer
            actorIdToActorMap.add(id, actor);

            // Map the Name to the ID
            actorNameToIdMap.add(name, id);

            // Add actor to the AVL tree
            yearToActor.insertItem(birth, actor);
        }

        fin.close();

    } else if (fileName == "cast.csv") {
        // Read data line by line
        while (getline(fin, line)) {
            stringstream s(line);

            // Read and parse each column as string and convert to int
            string temp;
            int personID, movieID;

            getline(s, temp, ',');
            personID = stoi(temp);

            getline(s, temp, ','); 
            movieID = stoi(temp);  

            // Output the parsed data
            Actor* actor = actorIdToActorMap.get(personID);
            Movie* movie = movieIdToMovieMap.get(movieID);
            actor->addMovie(movie);
            movie->addActor(actor);
        }

        fin.close();

    } else if (fileName == "movies.csv") {
                // Read data line by line
        while (getline(fin, line)) {
            stringstream s(line);

            // Read and parse each column as string and convert to int
            string title, temp;
            int id, year;

            getline(s, temp, ',');
            id = stoi(temp);

            getline(s, title, ',');

            getline(s, temp, ','); 
            year = stoi(temp);  

            // Create an actor object
            Movie* movie = new Movie(id, title, year);

            // Map the ID to the Movie pointer
            movieIdToMovieMap.add(id, movie);

            // Map the Title to the ID
            movieNameToIdMap.add(title, id);

            // Add Movie to the AVL tree
            yearToMovie.insertItem(year, movie);
        }

        fin.close();
    } else {
        cout << "Error: Unsupported file name \"" << fileName << "\". Please provide a valid file name." << endl;
        fin.close();
    }
}

/*----------------------------------------------------------------------------
Adds a new actor to the linked list.

@param actorList (List<Actor>&): Reference to the linked list of Actor objects.

@return bool: Returns true if the actor is successfully added to the list, otherwise false.

Description:
    - Prompts the user to input details for a new actor, including:
        - `id` (integer): A unique identifier for the actor.
        - `name` (string): The actor's full name.
        - `birth` (integer): The year of birth for the actor.
    - Creates a new `Actor` object with the provided details.
    - Adds the newly created actor to the provided linked list (`actorList`).
    - Ensures the list dynamically grows as new actors are added.

Error Handling:
    - Input validation ensures the correct data types are entered for each field.
    - If invalid input is detected, the program may exhibit undefined behavior (additional validation can be added).
-----------------------------------------------------------------------------*/
bool addNewActor(int id, int birth, string name, Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor) {
    // Create a new actor object
    Actor* actor = new Actor(id, name, birth);

    // Map the ID to the Actor pointer
    actorIdToActorMap.add(id, actor);

    // Map the Name to the ID
    actorNameToIdMap.add(name, id);

    // Add actor to the AVL tree
    yearToActor.insertItem(birth, actor);

    return true;
}

/*----------------------------------------------------------------------------
Adds a new movie to the linked list.

@param movieList (List<Movie>&): Reference to the linked list of Movie objects.

@return bool: Returns true if the movie is successfully added to the list, otherwise false.

Description:
    - Prompts the user to input details for a new movie, including:
        - `id` (integer): A unique identifier for the movie.
        - `movie` (string): The movie's name/title.
        - `year` (integer): The year of release for the movie.
    - Creates a new `Movie` object with the provided details.
    - Adds the newly created movie to the provided linked list (`movieList`).

Error Handling:
    - If invalid input is detected (e.g., non-integer for `id` or `year`), the program may exhibit undefined behavior.
-----------------------------------------------------------------------------*/
bool addNewMovie(int id, int year, string name, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie) {
    // Create a new movie object
    Movie* movie = new Movie(id, name, year);

    // Map the ID to the Movie pointer
    movieIdToMovieMap.add(id, movie);

    // Map the Title to the ID
    movieNameToIdMap.add(name, id);

    // Add Movie to the AVL tree
    yearToMovie.insertItem(year, movie);

    return true;
}

/*----------------------------------------------------------------------------
Assigns an actor to a specific movie.

@param actorList (List<Actor>): Reference to the linked list of Actor objects.
@param movieList (List<Movie>): Reference to the linked list of Movie objects.
@param movieToActors (Dictionary<int, List<Actor>>&): Dictionary mapping movie IDs to their associated list of actors.

@return bool: Returns true if the actor is successfully added to the movie, otherwise false.

Description:
    - Prompts the user to select an actor by ID and a movie by ID.
    - Searches for the actor and movie in their respective lists.
    - Associates the selected actor with the selected movie by updating the `movieToActors` dictionary.
    - If the movie has no existing list of actors, a new list is created and added to the dictionary.

Error Handling:
    - If the actor or movie ID does not exist, an error message is displayed, and the function returns false.
    - Ensures that actor and movie lists are dynamically managed.
-----------------------------------------------------------------------------*/
bool addActorToMovie(Actor* actor, Movie* movie) {
    actor->addMovie(movie);
    movie->addActor(actor);
    cout << "Actor successfully added to the movie!\n";
    return true;
}

/*----------------------------------------------------------------------------
Updates the details of an existing actor.

@param actorList (List<Actor>&): Reference to the linked list of Actor objects.

@return void

Description:
    - Prompts the user to enter the ID of the actor to update.
    - Searches for the actor in the provided list using the ID.
    - Displays the current details of the actor.
    - Allows the user to update the actor's name and year of birth:
        - If the user provides empty input for the name, the current name is retained.
        - If the user enters `-1` for the year of birth, the current year is retained.
    - Updates the actor's details based on user input.

Error Handling:
    - If the actor ID does not exist, an error message is displayed, and the function exits.
    - Input validation ensures the current details are retained for invalid or empty input.
-----------------------------------------------------------------------------*/
void updateActorDetails(Actor* actorToUpdate, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor) {
    
    // Display current details of the actor
    cout << "Current Details:\n";
    cout << "ID: " << actorToUpdate->getID() << "\n";
    cout << "Name: " << actorToUpdate->getName() << "\n";
    cout << "Year of Birth: " << actorToUpdate->getYearOfBirth() << "\n";

    // Prompt user for new details 
    string newName;
    int newYear;

    cout << "Enter the new name (leave blank to keep current): ";
    getline(cin, newName);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter the new year of birth (enter -1 to keep current): ";
    cin >> newYear;

    // Update the details
    if (!newName.empty()) {
        actorNameToIdMap.remove(actorToUpdate->getName());
        actorToUpdate->setName(newName);
        actorNameToIdMap.add(newName, actorToUpdate->getID());
    }
    if (newYear != -1) {
        yearToActor.removeItem(actorToUpdate->getYearOfBirth(), actorToUpdate);
        actorToUpdate->setYearOfBirth(newYear);
        yearToActor.insertItem(newYear, actorToUpdate);
    }

    cout << "Actor details updated successfully!\n";
}

/*----------------------------------------------------------------------------
Updates the details of an existing movie.

@param movieList (List<Movie>&): Reference to the linked list of Movie objects.

@return void

Description:
    - Prompts the user to enter the ID of the movie to update.
    - Searches for the movie in the provided list using the ID.
    - Displays the current details of the movie.
    - Allows the user to update the movie's title and year of release:
        - If the user provides empty input for the title, the current title is retained.
        - If the user enters `-1` for the year of release, the current year is retained.
    - Updates the movie's details based on user input.

Error Handling:
    - If the movie ID does not exist, an error message is displayed, and the function exits.
    - Input validation ensures the current details are retained for invalid or empty input.
-----------------------------------------------------------------------------*/
void updateMovieDetails(Movie* movieToUpdate, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie) {
    

    // Display current details of the movie
    cout << "Current Details:\n";
    cout << "ID: " << movieToUpdate->getID() << "\n";
    cout << "Title: " << movieToUpdate->getName() << "\n";
    cout << "Year of Release: " << movieToUpdate->getYear() << "\n";

    // Prompt user for new details 
    string newTitle;
    int newYear;

    cout << "Enter the new title (leave blank to keep current): ";
    getline(cin, newTitle);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter the new year of release (enter -1 to keep current): ";
    cin >> newYear;

    // Update the details
    if (!newTitle.empty()) {
        movieNameToIdMap.remove(movieToUpdate->getName());
        movieToUpdate->setName(newTitle);
        movieNameToIdMap.add(newTitle, movieToUpdate->getID());
    }
    if (newYear != -1) {
        yearToMovie.removeItem(movieToUpdate->getYear(), movieToUpdate);
        movieToUpdate->setYear(newYear);
        yearToMovie.insertItem(newYear, movieToUpdate);
    }

    cout << "Movie details updated successfully!\n";
}

/*----------------------------------------------------------------------------
Displays the user menu and handles user operations.

@return void

Description:
    - Allows the user to perform various actions such as 
      viewing actors and movies based on specific criteria.
    - Continues to prompt the user until they choose to exit.
-----------------------------------------------------------------------------*/
void userMenu(Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie) {
    int option;

    do {
        cout << "\n=============================================\n";
        cout << "       🎬 Silver Village User Menu               \n";
        cout << "=============================================\n";
        cout << " [1]  ➤ Display Actors by Age Range\n";
        cout << " [2]  ➤ Show Movies from the Last 3 Years\n";
        cout << " [3]  ➤ List Movies an Actor Starred In\n";
        cout << " [4]  ➤ List Actors in a Specific Movie\n";
        cout << " [5]  ➤ Find All Actors an Actor Knows\n";
        cout << " [0]  ➤ Exit Application\n";
        cout << "=============================================\n";
        cout << "Please select an option by entering the number: ";

        switch (option) {
            case 0: {
                cout << " Thank you for visiting Silver Village! Hope to see you next time!";
                break;
            }
            case 1: {
                int x, y;
                cout << "Enter the age range (x, y): ";
                cin >> x >> y;
                displayActorsByAgeRange(x, y, yearToActor);
                break;
            }
            case 2:{
                displayRecentMovies(yearToMovie);
                break;
            }
            case 3:{
                //Display all movies an actor starred in (in alphabetical order)
                break;
            }

            case 4:{
                //Display all the actors in a particular movie (in alphabetical order)
                break;

            }
            case 5:
                {
                    //Display all the actors an actor knows
                    string actorName;
                    cout << "Enter the actor's name: ";
                    cin >> actorName;

                    Actor* actor = findActorByName(actorNameToIdMap, actorName, actorIdToActorMap);
                    displayActorsKnownBy(actor);
                    break;  
                }
                
            default:
                cout << "Invalid choice! Try again.\n"; 

        }

    } while (option != 5);
}

void displayActorsByAgeRange(int x, int y, AVLTree<Actor*>& yearToActor) {
    cout << "Actors between " << x << " and " << y << " years old:\n";
    int currentYear = 2025;
    x = currentYear - x; //last year to include
    y = currentYear - y; //first year to include
    yearToActor.DisplayActors(y, x);
}; 

void displayRecentMovies(AVLTree<Movie*>& yearToMovie) {
    cout << "Movies from the last 3 years:\n";
    yearToMovie.DisplayMovies();
};

void displayMoviesByActor(); 
void displayActorsByMovie(); 

void displayActorsKnownByHelper(Actor* actor, DynamicArray& actors_known){
    for (int i = 0; i < actor->movies.getLength(); i++){
        //get cast of all movies actor was in
        List<Actor*> cast = actor->movies.get(i)->cast;

        for (int j = 0; j < cast.getLength(); j++){
            if (cast.get(j) != actor){
                actors_known.add(cast.get(j));
            }
        }
    }
};

void displayActorsKnownBy(Actor* actor){
    DynamicArray actors_known;
    displayActorsKnownByHelper(actor, actors_known);
    for (int i = 0; i < actors_known.getSize(); i++){
        displayActorsKnownByHelper(actors_known.get(i), actors_known);
    }
    cout << "Actors known by " << actor->getName() << ":\n";
    for (int i = 0; i < actors_known.getSize(); i++){
        cout << actors_known.get(i)->getName() << "\n";
    }
};

void setActorRating();
void setMovieRating();
void recommendMoviesByRating();
void recommendActorsByRating();