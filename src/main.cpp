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
#include <iomanip>
#include <sstream>
#include "List.h"
#include "Dictionary.h"
#include "Actor.h"
#include "Movie.h"
#include "AVLTree.h"
#include "DynamicArray.h"
#include <cmath> // Include cmath for the floor function

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
void adminMenu(Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie, DynamicArray<Actor*>& allActors, DynamicArray<Movie*>& allMovies);
void userMenu(Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie, DynamicArray<Actor*>& allActors, DynamicArray<Movie*>& allMovies);
void readCSV(string fileName, Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Actor*>& yearToActor, AVLTree<Movie*>& yearToMovie, DynamicArray<Actor*>& allActors, DynamicArray<Movie*>& allMovies);
void castAddLine(int personId, int movieId);
void addLine(const string& filename, int id, const string& name, int year);
bool addNewActor(int id, int birth, string name, Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, DynamicArray<Actor*>& allActors);
bool addNewMovie(int id, int year, string name, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie, DynamicArray<Movie*>& allMovies);
bool addActorToMovie(Actor* actor, Movie* movie);
void updateActorDetails(Actor* actorToUpdate, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor);
void updateMovieDetails(Movie* movieToUpdate, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie);
void displayActorsByAgeRange(int x, int y, AVLTree<Actor*>& yearToActor);
void displayRecentMovies(AVLTree<Movie*>& yearToMovie);
void displayMoviesByActor(Actor* actor); 
void displayActorsByMovie(Movie* movie); 
void displayActorsKnownBy(Actor* actor);
void displayActorsKnownByHelper(Actor* actor, DynamicArray<Actor*>& actors_known);
string roundToOneDecimal(double value);
void setActorRating(Actor* actor, double rating);
void setMovieRating(Movie* movie, double rating);  
void recommendMoviesByRating(DynamicArray<Movie*>& allMovies);
void recommendActorsByRating(DynamicArray<Actor*>& allActors);


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

    DynamicArray<Actor*> allActors; //Dynamic array with actors sorted by rating
    DynamicArray<Movie*> allMovies; //Dynamic array with movies sorted by rating

    Dictionary<int, Actor*> actorIdToActorMap;
    Dictionary<string, int> actorNameToIdMap;

    Dictionary<int, Movie*> movieIdToMovieMap;
    Dictionary<string, int> movieNameToIdMap;

    //AVL TREE FOR YEAR TO ACTOR 
    AVLTree<Actor*> yearToActor;
    //AVL TREE FOR YEAR TO MOVIE
    AVLTree<Movie*> yearToMovie;

    readCSV("actors.csv", actorIdToActorMap, actorNameToIdMap, movieIdToMovieMap, movieNameToIdMap, yearToActor, yearToMovie, allActors, allMovies);
    readCSV("movies.csv", actorIdToActorMap, actorNameToIdMap, movieIdToMovieMap, movieNameToIdMap, yearToActor, yearToMovie, allActors, allMovies);
    readCSV("cast.csv", actorIdToActorMap, actorNameToIdMap, movieIdToMovieMap, movieNameToIdMap, yearToActor, yearToMovie, allActors, allMovies);

    char isAdmin;
    while (true) {
        cout << "Are you an administrator? (y/n, q to quit): ";
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
                adminMenu(actorIdToActorMap, actorNameToIdMap, yearToActor, movieIdToMovieMap, movieNameToIdMap, yearToMovie, allActors, allMovies);
            } else {
                cout << "Failed all attempts! You will be logged in as a normal user.\n";
                userMenu(actorIdToActorMap, actorNameToIdMap, yearToActor, movieIdToMovieMap, movieNameToIdMap, yearToMovie, allActors, allMovies);  
            }
        } else if (isAdmin == 'n' || isAdmin == 'N') {
            cout << "Welcome, User!\n";
            userMenu(actorIdToActorMap, actorNameToIdMap, yearToActor, movieIdToMovieMap, movieNameToIdMap, yearToMovie, allActors, allMovies);  
        } else if (isAdmin == 'q' || isAdmin == 'Q') {
            cout << "Thank you for visiting Silver Village! Hope to see you next time!\n";
            break;
        } else {
            cout << "Invalid input! Please enter 'y' for yes, 'n' for no, or 'q' to quit: ";

        }
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
    char username[20], password[20];

    // Prompt user to enter in credentials
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;

    // Check against stored credentials
    for (int i = 0; i < MAX_ADMINS; i++) {
        bool usernameMatch = true;
        bool passwordMatch = true;

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
void adminMenu(Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie, DynamicArray<Actor*>& allActors, DynamicArray<Movie*>& allMovies) {
    int option;

    do {
        cout << "\n=============================================\n";
        cout << "          Silver Village Admin Menu               \n";
        cout << "=============================================\n";
        cout << " [1] Add a New Actor\n";
        cout << " [2] Add a New Movie\n";
        cout << " [3] Assign an Actor to a Movie\n";
        cout << " [4] Update Actor Details\n";
        cout << " [5] Update Movie Details\n";
        cout << " [0] Log Out of Admin\n";
        cout << "=============================================\n";
        
        // Prompt user for input
        cout << "Please select an option by entering the number: ";
        cin >> option;

        // Check for invalid input (non-integer or out-of-range)
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "\nInvalid choice! Please enter a number between 0 and 5.\n";
            continue; 
        }

        if (option < 0 || option > 5) {
            cout << "\nInvalid choice! Please enter a number between 0 and 5.\n";
            continue; 
        }

        switch (option) {
            case 0: {
                cout << "Logged out from Admin\n";
                break;
            }
            case 1: {
                cout << "Adding a new actor...\n";
                int actor_id, actor_birth;
                string actor_name;

                // Prompt user for id, name, and birth for new actor
                cout << "Enter new actor's ID: ";
                cin >> actor_id;

                if (actorIdToActorMap.contains(actor_id)) {
                    cout << "Error: Actor ID already exists. Please choose a different ID.\n";
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the newline left by cin >>

                cout << "Enter new actor's name: ";
                getline(cin, actor_name);

                if (actorNameToIdMap.contains(actor_name)) {
                    cout << "Error: Actor name already exists. Please choose a different name.\n";
                    break;
                }

                cout << "Enter new actor's year of birth: ";
                cin >> actor_birth;
                
                addNewActor(actor_id, actor_birth, actor_name, actorIdToActorMap, actorNameToIdMap, yearToActor, allActors);
                addLine("actors.csv", actor_id, actor_name, actor_birth);
                cout << "Actor successfully added!\n";
                break;
            }
            case 2:{
                int movie_id, movie_year;
                string movie_name;

                // Prompt user for id, movie, and year for new movie
                cout << "Enter new movie's ID: ";
                cin >> movie_id;

                if (movieIdToMovieMap.contains(movie_id)) {
                    cout << "Error: Movie ID already exists. Please choose a different ID.\n";
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter new movie's name: ";
                getline(cin, movie_name);

                if (movieNameToIdMap.contains(movie_name)) {
                    cout << "Error: Movie name already exists. Please choose a different name.\n";
                    break;
                }

                cout << "Enter new movie's release year: ";
                cin >> movie_year;

                addNewMovie(movie_id, movie_year, movie_name, movieIdToMovieMap, movieNameToIdMap, yearToMovie, allMovies);
                addLine("movies.csv", movie_id, movie_name, movie_year);
                break;
            }
            case 3:{

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                string actor_name, movie_name;
                cout << "Enter the actor's name: ";
                getline(cin, actor_name);

                cout << "Enter the movie's name: ";
                getline(cin, movie_name);

                Actor* actor = findActorByName(actorNameToIdMap, actor_name, actorIdToActorMap);
                Movie* movie = findMovieByName(movieNameToIdMap, movie_name, movieIdToMovieMap);
                if (actor != nullptr && movie != nullptr) {
                    addActorToMovie(actor, movie);
                    castAddLine(actor->getID(), movie->getID());
                } else {
                    cout << "Error: Actor or Movie not found. Please ensure the Name is correct.\n";
                }
                break;
            }
            case 4:{
                string actor_name;
                // Prompt user for actor name to update actor's details
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter the actor's name to update: ";
                getline(cin, actor_name);
                Actor* actorToUpdate = findActorByName(actorNameToIdMap, actor_name, actorIdToActorMap);

                if (actorToUpdate != nullptr) {
                    updateActorDetails(actorToUpdate, actorNameToIdMap, yearToActor);
                } else {
                    cout << "Error: Actor not found. Please ensure the Name is correct.\n";
                }
                break;
            }
            case 5: {
                string movie_name;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter the movie's name to update: ";
                getline(cin, movie_name);
                Movie* movieToUpdate = findMovieByName(movieNameToIdMap, movie_name, movieIdToMovieMap);

                if (movieToUpdate != nullptr) {
                    updateMovieDetails(movieToUpdate, movieNameToIdMap, yearToMovie);
                } else {
                    cout << "Error: Movie not found. Please ensure the Name is correct.\n";
                }
                break;
            }
            default:
                cout << "Error: Unexpected error occurred.\n";
                break;
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
void readCSV(string fileName, Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Actor*>& yearToActor, AVLTree<Movie*>& yearToMovie, DynamicArray<Actor*>& allActors, DynamicArray<Movie*>& allMovies) {
    // File pointer
    fstream fin;
    string filePath = "./data/" + fileName;

    // Open csv
    fin.open(filePath, ios::in);

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

            getline(s, temp, '"');
            getline(s, name, '"');
            s.ignore(1);

            getline(s, temp, ','); 
            birth = stoi(temp);  

            addNewActor(id, birth, name, actorIdToActorMap, actorNameToIdMap, yearToActor, allActors);
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
            addActorToMovie(actor, movie);
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

            getline(s, temp, '"');
            getline(s, title, '"');
            s.ignore(1);

            getline(s, temp, ','); 
            year = stoi(temp);  

            addNewMovie(id, year, title, movieIdToMovieMap, movieNameToIdMap, yearToMovie, allMovies);
        }

        fin.close();
    } else {
        cout << "Error: Unsupported file name \"" << fileName << "\". Please provide a valid file name." << endl;
        fin.close();
    }
}

void addLine(const string& filename, int id, const string& name, int year) {
    // Open the file in append mode
    string filePath = "./data/" + filename;

    ofstream file(filePath, ios::app);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filePath << " for writing." << endl;
        return;
    }

    // Write the new line in the format: id,"name",year
    file << id << ",\"" << name << "\"," << year << "\n";

    // Close the file
    file.close();

}

void castAddLine(int personId, int movieId) {
    // Open the file in append mode
    ofstream file("./data/cast.csv", ios::app);

    if (!file.is_open()) {
        cerr << "Error: Could not open file cast.csv for writing." << endl;
        return;
    }

    // Write the new line in the format: id,"name",year
    file << personId << ",\"" << movieId << "\n";

    // Close the file
    file.close();
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
bool addNewActor(int id, int birth, string name, Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, DynamicArray<Actor*>& allActors) {
    // Create a new actor object
    Actor* actor = new Actor(id, name, birth);

    // Map the ID to the Actor pointer
    actorIdToActorMap.add(id, actor);

    // Map the Name to the ID
    actorNameToIdMap.add(name, id);

    // Add actor to the dynamic array
    allActors.add(actor);

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
bool addNewMovie(int id, int year, string name, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie, DynamicArray<Movie*>& allMovies) {
    // Create a new movie object
    Movie* movie = new Movie(id, name, year);

    // Map the ID to the Movie pointer
    movieIdToMovieMap.add(id, movie);

    // Map the Title to the ID
    movieNameToIdMap.add(name, id);

    // Add Movie to the dynamic array
    allMovies.add(movie);

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
void userMenu(Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie, DynamicArray<Actor*>& allActors, DynamicArray<Movie*>& allMovies) {
    int option;

    do {
        cout << "\n=============================================\n";
        cout << "         Silver Village User Menu               \n";
        cout << "=============================================\n";
        cout << " [1] Display Actors by Age Range\n";
        cout << " [2] Show Movies from the Last 3 Years\n";
        cout << " [3] List Movies an Actor Starred In\n";
        cout << " [4] List Actors in a Specific Movie\n";
        cout << " [5] Find All Actors an Actor Knows\n";
        cout << " [6] Rate an Actor\n";
        cout << " [7] Rate a Movie\n";
        cout << " [8] Recommend Movies by Rating\n";
        cout << " [9] Recommend Actors by Rating\n";
        cout << " [0] Log Out of User\n";
        cout << "=============================================\n";
        cout << "Please select an option by entering the number: ";
        cin >> option;
        switch (option) {
            case 0: {
                cout << "Logged out from User\n";
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
                string actor_name;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter the actor's name: ";
                getline(cin, actor_name);
                Actor* actor = findActorByName(actorNameToIdMap, actor_name, actorIdToActorMap);
                if (actor != nullptr){
                    displayMoviesByActor(actor);
                } else {
                    cout << "Actor not found.\n";
                }
                break;
            }

            case 4:{
                //Display all the actors in a particular movie (in alphabetical order)
                string movie_name;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter the movie's name: ";
                getline(cin, movie_name);
                Movie* movie = findMovieByName(movieNameToIdMap, movie_name, movieIdToMovieMap);
                if (movie != nullptr){
                    displayActorsByMovie(movie);
                } else {
                    cout << "Movie not found.\n";
                }
                break;

            }
            case 5:
                {
                    //Display all the actors an actor knows
                    string actor_name;

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter the actor's name: ";
                    getline(cin, actor_name);
                    Actor* actor = findActorByName(actorNameToIdMap, actor_name, actorIdToActorMap);
                    if (actor != nullptr){
                        displayActorsKnownBy(actor);
                    } else{
                        cout << "Actor not found.\n";
                    }
                    break;  
                }
            case 6: {
                //Rate an actor
                string actor_name;
                double rating;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter the actor's name: ";
                getline(cin, actor_name);
                Actor* actor = findActorByName(actorNameToIdMap, actor_name, actorIdToActorMap);
                if (actor == nullptr) {
                    cout << "Actor not found.\n";
                    break;
                }
                while (true) {
                    cout << "Actor's current rating: " << roundToOneDecimal(actor->getRating()) << endl;
                    cout << "Enter a rating (e.g., 1.5, 4.9): ";
                    cin >> rating;

                    if (cin.fail() || rating < 0 || rating > 5) {
                        cin.clear(); // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        cout << "Invalid input. Please enter a number between 1 and 5." << endl;
                    } else {
                        break; // Exit the loop if input is valid
                    }
                }
                setActorRating(actor, rating);
                break;
            }
            case 7: {
                //Rate a movie
                string movie_name;
                double rating;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter the movie's name: ";
                getline(cin, movie_name);
                Movie* movie = findMovieByName(movieNameToIdMap, movie_name, movieIdToMovieMap);
                if (movie == nullptr) {
                    cout << "Movie not found.\n";
                    break;
                }
                while (true) {
                    cout << "Movie's current rating: " << roundToOneDecimal(movie->getRating()) << endl;
                    cout << "Enter a rating (e.g., 1.5, 4.9): ";
                    cin >> rating;

                    if (cin.fail() || rating < 0 || rating > 5) {
                        cin.clear(); // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        cout << "Invalid input. Please enter a number between 1 and 5." << endl;
                    } else {
                        break; // Exit the loop if input is valid
                    }
                }
                setMovieRating(movie, rating);
                break;
            }
            case 8: {
                recommendMoviesByRating(allMovies);
                break;
            }
            case 9: {
                recommendActorsByRating(allActors);
                break;
            }
            default:
                cout << "Invalid choice! Try again.\n"; 

        }

    } while (option != 0);
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

void displayMoviesByActor(Actor* actor){
    //Display all movies an actor starred in (in alphabetical order)
    cout << "Movies " << actor->getName() << " starred in:\n";
    List<Movie*> *movies = &actor->movies;
    for (int i = 0; i < movies->getLength(); i++){
        cout << movies->get(i)->getName() << " (" << movies->get(i)->getYear() << ")\n";
    }
}; 
void displayActorsByMovie(Movie* movie){
    //Display all the actors in a particular movie (in alphabetical order)
    cout << "Actors in " << movie->getName() << ":\n";
    for (int i = 0; i < movie->cast.getLength(); i++){
        cout << movie->cast.get(i)->getName() << "\n";
    }
}; 

void displayActorsKnownByHelper(Actor* targetActor, DynamicArray<Actor*>& actors_known, Actor* originalActor){
    if (targetActor == nullptr){
        cout << "Actor not found.\n";
        return;
    }
    List<Movie*> *movies = &targetActor->movies;
    //go through each movie of the actor
    for (int i = 0; i < movies->getLength(); i++){
        //go through each actor in the movie 
        Movie* movie = movies->get(i);
        for (int j = 0; j < movie->cast.getLength(); j++){
            if (movie->cast.get(j) != targetActor && movie->cast.get(j) != originalActor){
                actors_known.add(movie->cast.get(j));
            }
        }
    }
};

void displayActorsKnownBy(Actor* targetActor){
    DynamicArray<Actor*> actors_known;
    // Step 1: Add direct connections
    displayActorsKnownByHelper(targetActor, actors_known, targetActor);

    // Step 2: Add indirect connections (one more level)
    DynamicArray<Actor*> actors_known_indirect;
    for (int i = 0; i < actors_known.getSize(); i++){
        displayActorsKnownByHelper(actors_known.get(i), actors_known_indirect, targetActor);
    }
    
    // Combine direct and indirect connections (code is working)
    for (int i = 0; i < actors_known_indirect.getSize(); i++){
        actors_known.add(actors_known_indirect.get(i));
    }

    cout << "Actors known by " << targetActor->getName() << ":\n";
    for (int i = 0; i < actors_known.getSize(); i++){
        cout << actors_known.get(i)->getName() << "\n";
    }
    cout << "Total: " << actors_known.getSize() << "\n";

};

string roundToOneDecimal(double value) {
    if (value == 0) {
        return "nul";
    }
    ostringstream oss;
    oss << fixed << setprecision(1) << floor(value * 10 + 0.5) / 10;
    return oss.str();
}

void setActorRating(Actor* actor, double rating){
    actor->addRating(rating);
};
void setMovieRating(Movie* movie, double rating){
    movie->addRating(rating);
};
void recommendMoviesByRating(DynamicArray<Movie*>& allMovies){
    allMovies.sortByRating();
    cout << "Top highest rated movies:\n";
    cout << "Rating - Cast Rating - Movie Name\n";
    for (int i = 0; i < 5; i++){
        Movie* movie = allMovies.get(i);
        cout << roundToOneDecimal(movie->getRating()) << "⭐  - " << roundToOneDecimal(movie->castAverageRating()) << "⭐       - " << movie->getName() << " (" << movie->getYear() << ")\n";
    };
};
void recommendActorsByRating(DynamicArray<Actor*>& allActors){
    allActors.sortByRating();
    cout << "Top 5 Actors recommended by rating:\n";
    cout << "Rating - Actor Name\n";
    for (int i = 0; i < 5; i++){
        cout << roundToOneDecimal(allActors.get(i)->getRating()) << "⭐  - "<< allActors.get(i)->getName() <<  "\n";
    };
};