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
#include <cmath> 
#include "List.h"
#include "Dictionary.h"
#include "Actor.h"
#include "Movie.h"
#include "AVLTree.h"
#include "DynamicArray.h"

using namespace std;

// Function prototypes (Supporting)
bool authenticateAdmin();
Actor* findActorByName(Dictionary<string, int>& actorNameToIdMap, string actorName, Dictionary<int, Actor*>& actorIdToActorMap);
Movie* findMovieByName(Dictionary<string, int>& movieNameToIdMap, string movieName, Dictionary<int, Movie*>& movieIdToMovieMap);
void adminMenu(Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie, DynamicArray<Actor*>& allActors, DynamicArray<Movie*>& allMovies);
void userMenu(Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie, DynamicArray<Actor*>& allActors, DynamicArray<Movie*>& allMovies);
void readCSV(string fileName, Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Actor*>& yearToActor, AVLTree<Movie*>& yearToMovie, DynamicArray<Actor*>& allActors, DynamicArray<Movie*>& allMovies);
string roundToOneDecimal(double value);

// Function prototypes (Basic)
bool addNewActor(int id, int birth, string name, Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, DynamicArray<Actor*>& allActors);
bool addNewMovie(int id, int year, string name, string plot, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie, DynamicArray<Movie*>& allMovies);
bool addActorToMovie(Actor* actor, Movie* movie);
void updateActorDetails(Actor* actorToUpdate, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor);
void updateMovieDetails(Movie* movieToUpdate, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie);
void displayActorsByAgeRange(int x, int y, AVLTree<Actor*>& yearToActor);
void displayRecentMovies(AVLTree<Movie*>& yearToMovie);
void displayMoviesByActor(Actor* actor); 
void displayActorsByMovie(Movie* movie); 
void displayActorsKnownBy(Actor* actor);
void displayActorsKnownByHelper(Actor* actor, DynamicArray<Actor*>& actors_known);

// Function prototypes (Advanced)
void setActorRating(Actor* actor, double rating);
void setMovieRating(Movie* movie, double rating);  
void recommendMoviesByRating(DynamicArray<Movie*>& allMovies);
void recommendActorsByRating(DynamicArray<Actor*>& allActors);

// Maximum number of admin accounts
const int MAX_ADMINS = 1;

// Admin credentials (hardcoded, stored in array)
char adminUsername[MAX_ADMINS][20] = {"admin"};
char adminPassword[MAX_ADMINS][20] = {"password"};

/*----------------------------------------------------------------------------
Main function of the program.

@return int: Returns 0 upon successful execution.

Description:
    - Initializes key data structures to store and map actors and movies 
      using dynamic arrays, dictionaries, and AVL trees.
    - Reads data from "actors.csv", "movies.csv", and "cast.csv" to populate 
      these data structures.
    - Prompts the user to determine if they are an administrator or a normal 
      user.
        - If the user is an administrator, it provides up to three attempts 
          for authentication and redirects to `adminMenu()` if successful. 
          If authentication fails, the user is redirected to `userMenu()`.
        - If the user is not an administrator, it redirects directly to 
          `userMenu()`.
        - If the user opts to quit, the program displays a farewell message 
          and exits.
    - Ensures robust input handling and appropriate redirection based on user 
      responses.
----------------------------------------------------------------------------*/
int main() {
    DynamicArray<Actor*> allActors; 
    DynamicArray<Movie*> allMovies; 

    Dictionary<int, Actor*> actorIdToActorMap;
    Dictionary<string, int> actorNameToIdMap;

    Dictionary<int, Movie*> movieIdToMovieMap;
    Dictionary<string, int> movieNameToIdMap;

    AVLTree<Actor*> yearToActor;
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
[Coder - Tevel]

Authenticates an admin user.

@return bool: Returns true if the entered credentials match the stored admin 
              credentials; otherwise, returns false.

Description:
    - Prompts the user to enter an admin username and password.
    - Compares the entered username and password with hardcoded admin credentials
      stored in `adminUsername` and `adminPassword` arrays.
    - Performs character-by-character comparison for both the username and password
      to ensure exact matches.
    - If a match is found for both the username and password, grants admin access 
      by returning `true`.
    - If no match is found after checking all stored admin credentials, denies access 
      and returns `false`.
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

/*----------------------------------------------------------------------------
[Coder - Brayden]

Finds an actor by their name.

@param actorNameToIdMap: Dictionary mapping actor names to their corresponding IDs.
@param actorName: The name of the actor to search for.
@param actorIdToActorMap: Dictionary mapping actor IDs to their corresponding Actor objects.
@return Actor*: Returns a pointer to the Actor object if found, otherwise nullptr.

Description:
    - Looks up the actor's ID in `actorNameToIdMap` using the provided `actorName`.
    - Uses the retrieved actor ID to fetch the corresponding Actor object from 
      `actorIdToActorMap`.
----------------------------------------------------------------------------*/
Actor* findActorByName(Dictionary<string, int>& actorNameToIdMap, string actorName, Dictionary<int, Actor*>& actorIdToActorMap) {
    int actorID = actorNameToIdMap.get(actorName);
    return actorIdToActorMap.get(actorID);
}

/*----------------------------------------------------------------------------
[Coder - Brayden]

Finds a movie by its name.

@param movieNameToIdMap: Dictionary mapping movie names to their corresponding IDs.
@param movieName: The name of the movie to search for.
@param movieIdToMovieMap: Dictionary mapping movie IDs to their corresponding Movie objects.
@return Movie*: Returns a pointer to the Movie object if found, otherwise nullptr.

Description:
    - Looks up the movie's ID in `movieNameToIdMap` using the provided `movieName`.
    - Uses the retrieved movie ID to fetch the corresponding Movie object from 
      `movieIdToMovieMap`.
----------------------------------------------------------------------------*/
Movie* findMovieByName(Dictionary<string, int>& movieNameToIdMap, string movieName, Dictionary<int, Movie*>& movieIdToMovieMap) {
    int movieID = movieNameToIdMap.get(movieName);
    return movieIdToMovieMap.get(movieID);
}

/*----------------------------------------------------------------------------
[Coder - Tevel]

Displays the admin menu and handles admin operations.

@param actorIdToActorMap: Dictionary mapping actor IDs to their corresponding Actor objects.
@param actorNameToIdMap: Dictionary mapping actor names to their corresponding IDs.
@param yearToActor: AVLTree mapping actor birth years to Actor objects.
@param movieIdToMovieMap: Dictionary mapping movie IDs to their corresponding Movie objects.
@param movieNameToIdMap: Dictionary mapping movie names to their corresponding IDs.
@param yearToMovie: AVLTree mapping movie release years to Movie objects.
@param allActors: Dynamic array containing all Actor objects.
@param allMovies: Dynamic array containing all Movie objects.
@return void

Description:
    - Provides an interface for administrators to manage actors and movies.
    - Allows the following operations:
        1. Add a new actor.
        2. Add a new movie.
        3. Assign an actor to a movie.
        4. Update actor details.
        5. Update movie details.
        0. Log out of the admin menu.
    - Continuously prompts the admin to select an option until they choose to log out.
    - Validates input to ensure the selection is within the allowed range (0–5).
    - Displays appropriate error messages for invalid input or operations (e.g., 
      duplicate IDs, missing actors or movies).
    - Calls helper functions such as `addNewActor`, `addNewMovie`, `addActorToMovie`, 
      `updateActorDetails`, and `updateMovieDetails` to perform specific tasks.
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
                cout << "Actor successfully added!\n";
                break;
            }
            case 2:{
                int movie_id, movie_year;
                string movie_name, movie_plot;

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

                cout << "Enter new movie's plot: ";
                getline(cin, movie_plot);

                cout << "Enter new movie's release year: ";
                cin >> movie_year;

                addNewMovie(movie_id, movie_year, movie_name, movie_plot, movieIdToMovieMap, movieNameToIdMap, yearToMovie, allMovies);
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
[Coder - Tevel]

Reads and processes a CSV file based on its type and populates appropriate data structures.

@param fileName: The name of the CSV file to read. Supported file names:
    - "actors.csv": Contains actor information with columns (id, name, birth).
    - "cast.csv": Contains cast information with columns (person_id, movie_id).
    - "movies.csv": Contains movie information with columns (id, title, year).
@param actorIdToActorMap: Dictionary mapping actor IDs to their corresponding Actor objects.
@param actorNameToIdMap: Dictionary mapping actor names to their corresponding IDs.
@param movieIdToMovieMap: Dictionary mapping movie IDs to their corresponding Movie objects.
@param movieNameToIdMap: Dictionary mapping movie names to their corresponding IDs.
@param yearToActor: AVLTree mapping actor birth years to Actor objects.
@param yearToMovie: AVLTree mapping movie release years to Movie objects.
@param allActors: Dynamic array containing all Actor objects.
@param allMovies: Dynamic array containing all Movie objects.

@return void

Description:
    - Opens the specified CSV file from the "./data/" directory.
    - Validates if the file is successfully opened; otherwise, displays an error message and exits.
    - Skips the header line and processes data line by line for the specified file type:
        - **"actors.csv"**: Parses ID, Name, and Birth Year and calls `addNewActor` to populate data structures.
        - **"cast.csv"**: Parses Person ID and Movie ID and calls `addActorToMovie` to assign actors to movies.
        - **"movies.csv"**: Parses ID, Title, and Release Year and calls `addNewMovie` to populate data structures.
    - Converts numeric data (IDs, years) from string to integer using `stoi`.
    - Handles unsupported file names with an error message and exits gracefully.

Error Handling:
    - Displays an error message if the file cannot be opened.
    - Handles unsupported file names by showing an error message and closing the file.
----------------------------------------------------------------------------*/
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

            getline(s, name, ',');

            getline(s, temp, ','); 
            if (temp == "") {
                birth = 0;
            } else {
                birth = stoi(temp);
            }

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
            string title, plot, temp;
            int id, year;

            getline(s, temp, ',');
            id = stoi(temp);

            // Handle title which may be enclosed in quotes
            if (s.peek() == '"') {
                s.get(); // Remove the opening quote
                getline(s, title, '"'); // Read until the closing quote
                s.get(); // Remove the comma after the closing quote
            } else {
                getline(s, title, ',');
            }

            // Handle plot which may be enclosed in quotes
            if (s.peek() == '"') {
                s.get(); // Remove the opening quote
                getline(s, plot, '"'); // Read until the closing quote
                s.get(); // Remove the comma after the closing quote
            } else {
                getline(s, plot, ',');
            }

            getline(s, temp, ','); 
            year = stoi(temp);  

            addNewMovie(id, year, title, plot, movieIdToMovieMap, movieNameToIdMap, yearToMovie, allMovies);
        }

        fin.close();
    } else {
        cout << "Error: Unsupported file name \"" << fileName << "\". Please provide a valid file name." << endl;
        fin.close();
    }
}

/*----------------------------------------------------------------------------
[Coder - Brayden]

Adds a new actor to the system and updates relevant data structures.

@param id: A unique integer identifier for the actor.
@param birth: The year of birth of the actor.
@param name: The full name of the actor.
@param actorIdToActorMap: Dictionary mapping actor IDs to their corresponding Actor objects.
@param actorNameToIdMap: Dictionary mapping actor names to their corresponding IDs.
@param yearToActor: AVLTree mapping actor birth years to Actor objects.
@param allActors: Dynamic array containing all Actor objects.
@return bool: Returns true if the actor is successfully added to all data structures.

Description:
    - Creates a new `Actor` object using the provided `id`, `name`, and `birth`.
    - Adds the newly created `Actor` object to the following data structures:
        - **`actorIdToActorMap`**: Maps the actor's unique ID to their `Actor` object.
        - **`actorNameToIdMap`**: Maps the actor's name to their unique ID.
        - **`allActors`**: A dynamic array containing all `Actor` objects for fast iteration.
        - **`yearToActor`**: An AVL tree for efficiently grouping and searching actors by their birth year.
    - Ensures the actor is fully integrated into all relevant data structures.

Error Handling:
    - Assumes that the provided `id` and `name` are unique. If duplicates exist, behavior is undefined.
    - Does not validate the input parameters (e.g., negative birth year or empty name). Additional validation should be implemented as needed.
----------------------------------------------------------------------------*/
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
[Coder - Tevel]

Adds a new movie to the system and updates relevant data structures.

@param id: A unique integer identifier for the movie.
@param year: The release year of the movie.
@param name: The name or title of the movie.
@param movieIdToMovieMap: Dictionary mapping movie IDs to their corresponding Movie objects.
@param movieNameToIdMap: Dictionary mapping movie names to their corresponding IDs.
@param yearToMovie: AVLTree mapping movie release years to Movie objects.
@param allMovies: Dynamic array containing all Movie objects.
@return bool: Returns true if the movie is successfully added to all data structures.

Description:
    - Creates a new `Movie` object using the provided `id`, `name`, and `year`.
    - Adds the newly created `Movie` object to the following data structures:
        - **`movieIdToMovieMap`**: Maps the movie's unique ID to its `Movie` object.
        - **`movieNameToIdMap`**: Maps the movie's title to its unique ID.
        - **`allMovies`**: A dynamic array containing all `Movie` objects for fast iteration.
        - **`yearToMovie`**: An AVL tree for efficiently grouping and searching movies by their release year.
    - Ensures the movie is fully integrated into all relevant data structures.

Error Handling:
    - Assumes that the provided `id` and `name` are unique. If duplicates exist, behavior is undefined.
    - Does not validate the input parameters (e.g., invalid release year or empty name). Additional validation should be implemented as needed.
----------------------------------------------------------------------------*/
bool addNewMovie(int id, int year, string name, string plot, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie, DynamicArray<Movie*>& allMovies) {
    // Create a new movie object
    Movie* movie = new Movie(id, name, plot, year);

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
[Coder - Brayden]
Assigns an actor to a specific movie and establishes a bidirectional relationship.

@param actor: Pointer to the `Actor` object to be assigned to the movie.
@param movie: Pointer to the `Movie` object to which the actor will be assigned.
@return bool: Returns true if the actor is successfully added to the movie and vice versa.

Description:
    - Updates the `Actor` object by adding the `Movie` object to the actor's list of associated movies.
    - Updates the `Movie` object by adding the `Actor` object to the movie's list of associated actors.
    - Establishes a bidirectional relationship between the actor and the movie, ensuring data consistency.
    - Assumes that both the `Actor` and `Movie` pointers are valid and properly initialized.

Error Handling:
    - Does not validate the input pointers (`actor` and `movie`) for null or invalid values. Additional validation should be implemented if needed.
    - Assumes that the `addMovie` and `addActor` methods handle duplicate entries internally.
----------------------------------------------------------------------------*/
bool addActorToMovie(Actor* actor, Movie* movie) {
    actor->addMovie(movie);
    movie->addActor(actor);
    return true;
}

/*----------------------------------------------------------------------------
[Coder - Tevel]

Updates the details of an existing actor in the system.

@param actorToUpdate: Pointer to the `Actor` object whose details need to be updated.
@param actorNameToIdMap: Dictionary mapping actor names to their corresponding IDs.
@param yearToActor: AVLTree mapping actor birth years to Actor objects.
@return void

Description:
    - Displays the current details of the specified actor, including their ID, name, and year of birth.
    - Prompts the user to enter updated details:
        - **Name**: If the input is empty, the actor's current name is retained.
        - **Year of Birth**: If the input is `-1`, the actor's current year of birth is retained.
    - Updates the `Actor` object with the new details based on user input.
    - Ensures data consistency by updating relevant data structures:
        - **`actorNameToIdMap`**: Updates the mapping of the actor's name to their ID.
        - **`yearToActor`**: Updates the AVL tree mapping the actor's birth year to the actor object.

Error Handling:
    - Assumes that the input `actorToUpdate` is valid and properly initialized.
    - If the user provides invalid or empty input for the name or year, the current details are retained.
    - Handles changes to the actor's name and year of birth by updating or maintaining consistency in the relevant data structures.
----------------------------------------------------------------------------*/
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
[Coder - Tevel]

Updates the details of an existing movie in the system.

@param movieToUpdate: Pointer to the `Movie` object whose details need to be updated.
@param movieNameToIdMap: Dictionary mapping movie titles to their corresponding IDs.
@param yearToMovie: AVLTree mapping movie release years to Movie objects.
@return void

Description:
    - Displays the current details of the specified movie, including its ID, title, and year of release.
    - Prompts the user to enter updated details:
        - **Title**: If the input is empty, the movie's current title is retained.
        - **Year of Release**: If the input is `-1`, the movie's current year of release is retained.
    - Updates the `Movie` object with the new details based on user input.
    - Ensures data consistency by updating relevant data structures:
        - **`movieNameToIdMap`**: Updates the mapping of the movie's title to its ID.
        - **`yearToMovie`**: Updates the AVL tree mapping the movie's release year to the movie object.

Error Handling:
    - Assumes that the input `movieToUpdate` is valid and properly initialized.
    - If the user provides invalid or empty input for the title or year, the current details are retained.
    - Handles changes to the movie's title and year of release by updating or maintaining consistency in the relevant data structures.
----------------------------------------------------------------------------*/
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
[Coder - Tevel]

Displays the user menu and handles user operations.

@param actorIdToActorMap: Dictionary mapping actor IDs to their corresponding Actor objects.
@param actorNameToIdMap: Dictionary mapping actor names to their corresponding IDs.
@param yearToActor: AVLTree mapping actor birth years to Actor objects.
@param movieIdToMovieMap: Dictionary mapping movie IDs to their corresponding Movie objects.
@param movieNameToIdMap: Dictionary mapping movie names to their corresponding IDs.
@param yearToMovie: AVLTree mapping movie release years to Movie objects.
@param allActors: Dynamic array containing all Actor objects.
@param allMovies: Dynamic array containing all Movie objects.
@return void

Description:
    - Provides an interface for users to interact with the system and perform various operations, including:
        1. Displaying actors by age range.
        2. Viewing movies released in the last three years.
        3. Listing movies an actor starred in (sorted alphabetically).
        4. Listing actors in a specific movie (sorted alphabetically).
        5. Finding all actors that an actor "knows."
        6. Rating an actor (allows input validation for ratings between 0 and 5).
        7. Rating a movie (allows input validation for ratings between 0 and 5).
        8. Recommending movies based on their ratings.
        9. Recommending actors based on their ratings.
    - Continues to prompt the user to select an option until they choose to log out by entering `0`.

Error Handling:
    - Validates user input for menu selection to ensure it is within the allowed range (0–9).
    - Handles invalid or empty input gracefully for operations requiring user input (e.g., names, ratings).
    - Displays appropriate error messages if an actor or movie is not found in the system.
----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------
[Coder - Brayden]

Displays actors within a specified age range.

@param x: The minimum age of actors to display (inclusive).
@param y: The maximum age of actors to display (inclusive).
@param yearToActor: AVLTree mapping actor birth years to Actor objects.
@return void

Description:
    - Calculates the range of birth years corresponding to the specified age range.
        - Converts the given ages (`x` and `y`) into birth years based on the current year (assumed to be 2025).
        - The range of birth years is calculated as:
            - `x`: The latest birth year to include (`2025 - x`).
            - `y`: The earliest birth year to include (`2025 - y`).
    - Uses the `DisplayActors` method of the AVLTree to display actors born within the calculated range.
    - Outputs a list of actors between the specified ages.

Error Handling:
    - Assumes the input ages (`x` and `y`) are valid integers where `y` is less than or equal to `x`.
    - If no actors exist in the specified range, the output depends on the behavior of the `DisplayActors` method.
----------------------------------------------------------------------------*/
void displayActorsByAgeRange(int x, int y, AVLTree<Actor*>& yearToActor) {
    cout << "Actors between " << x << " and " << y << " years old:\n";
    int currentYear = 2025;
    x = currentYear - x; //last year to include
    y = currentYear - y; //first year to include
    yearToActor.DisplayActors(y, x);
}; 

/*----------------------------------------------------------------------------
[Coder - Tevel]

Displays movies released within the last three years.

@param yearToMovie: AVLTree mapping movie release years to Movie objects.
@return void

Description:
    - Outputs a list of movies that were released within the last three years.
    - Uses the `DisplayMovies` method of the AVLTree to fetch and display movies.
    - Assumes the AVLTree contains movies categorized by their release year.

Error Handling:
    - Assumes the `DisplayMovies` method of the AVLTree correctly filters and displays movies from the last three years.
    - If no movies exist within the specified range, the behavior of the output depends on the `DisplayMovies` method implementation.
----------------------------------------------------------------------------*/
void displayRecentMovies(AVLTree<Movie*>& yearToMovie) {
    cout << "Movies from the last 3 years:\n";
    yearToMovie.DisplayMovies();
};

/*----------------------------------------------------------------------------
[Coder - Brayden]

Displays all movies that a specific actor has starred in, sorted alphabetically.

@param actor: Pointer to the `Actor` object whose movies are to be displayed.
@return void

Description:
    - Outputs a list of movies that the specified actor has starred in, displaying:
        - The movie's name (title).
        - The year the movie was released.
    - Iterates through the actor's `movies` list to retrieve and display each movie.
    - Assumes that the `movies` list associated with the actor is sorted alphabetically.

Error Handling:
    - Assumes the input `actor` is a valid and properly initialized pointer.
    - If the actor has no associated movies in their `movies` list, the function will not output any movie titles.
----------------------------------------------------------------------------*/
void displayMoviesByActor(Actor* actor){
    //Display all movies an actor starred in (in alphabetical order)
    cout << "Movies " << actor->getName() << " starred in:\n";
    List<Movie*> *movies = &actor->movies;
    for (int i = 0; i < movies->getLength(); i++){
        cout << movies->get(i)->getName() << " (" << movies->get(i)->getYear() << ")\n";
    }
}; 

/*----------------------------------------------------------------------------
[Coder - Tevel]

Displays all actors who starred in a specific movie, sorted alphabetically.

@param movie: Pointer to the `Movie` object whose cast (actors) are to be displayed.
@return void

Description:
    - Outputs a list of actors who starred in the specified movie.
    - Displays each actor's name retrieved from the movie's `cast` list.
    - Assumes that the `cast` list in the `Movie` object is sorted alphabetically.

Error Handling:
    - Assumes the input `movie` is a valid and properly initialized pointer.
    - If the movie has no associated actors in its `cast` list, the function will not output any actor names.
----------------------------------------------------------------------------*/
void displayActorsByMovie(Movie* movie){
    //Display all the actors in a particular movie (in alphabetical order)
    cout << "Actors in " << movie->getName() << ":\n";
    for (int i = 0; i < movie->cast.getLength(); i++){
        cout << movie->cast.get(i)->getName() << "\n";
    }
}; 

/*----------------------------------------------------------------------------
[Coder - Brayden]

Identifies and adds actors known by a specific target actor through shared movies.

@param targetActor: Pointer to the `Actor` object whose connections are being explored.
@param actors_known: Reference to a dynamic array that stores the list of actors known by the target actor.
@param originalActor: Pointer to the original `Actor` object initiating the search, used to avoid self-references.
@return void

Description:
    - Traverses the movies associated with the `targetActor` to find all actors they worked with.
    - Iterates through each movie in the `targetActor`'s `movies` list.
    - For each movie, iterates through the cast and adds all actors to the `actors_known` dynamic array except:
        - The `targetActor` themselves.
        - The `originalActor` to avoid self-references in the results.
    - Ensures all connections are stored in the `actors_known` dynamic array.

Error Handling:
    - If `targetActor` is `nullptr`, an error message is displayed, and the function exits without performing any operations.
    - Assumes all pointers and references provided are valid and properly initialized.
----------------------------------------------------------------------------*/
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


/*----------------------------------------------------------------------------
[Coder - Brayden]

Displays all actors directly and indirectly known by a specific target actor.

@param targetActor: Pointer to the `Actor` object whose network of known actors is to be displayed.
@return void

Description:
    - Identifies and displays actors known by the `targetActor` through shared movies.
    - **Direct Connections**: Calls `displayActorsKnownByHelper` to add all actors the `targetActor` worked with directly.
    - **Indirect Connections**: Iterates through the direct connections and adds actors known by them to expand the network.
    - Combines direct and indirect connections into a single list for display.
    - Outputs the names of all actors in the combined list, along with the total count.

Steps:
    1. Direct connections are added to the `actors_known` dynamic array by calling `displayActorsKnownByHelper`.
    2. Indirect connections are identified by iterating through `actors_known` and calling `displayActorsKnownByHelper` for each actor.
    3. Direct and indirect connections are combined into a single array.
    4. The combined list of actor names is displayed in the console.

Error Handling:
    - Assumes the `targetActor` pointer is valid and properly initialized.
    - If `targetActor` is `nullptr`, the behavior depends on the implementation of the helper function and other called methods.
    - No checks are performed for duplicate entries in the combined list; handling relies on the helper function.

----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------
[Coder - Brayden]

Rounds a double value to one decimal place and converts it to a string.

@param value: The double value to be rounded and converted to a string.
@return string: Returns the rounded value as a string. If the value is 0, returns "nul".

Description:
    - Rounds the input value to one decimal place using `floor` and a precision adjustment.
    - Converts the rounded value into a fixed-point string representation with one decimal place.
    - Special case: If the value is 0, returns the string "nul".
----------------------------------------------------------------------------*/
string roundToOneDecimal(double value) {
    if (value == 0) {
        return "nul";
    }
    ostringstream oss;
    oss << fixed << setprecision(1) << floor(value * 10 + 0.5) / 10;
    return oss.str();
}

/*----------------------------------------------------------------------------
[Coder - Brayden]

Sets the rating for a specific actor.

@param actor: Pointer to the `Actor` object whose rating is to be updated.
@param rating: The new rating to be added to the actor.
@return void

Description:
    - Calls the `addRating` method on the `Actor` object to update the actor's rating.
    - Assumes the rating is a valid double value, typically between 0 and 5.
    - Updates the actor's cumulative rating with the provided value.
----------------------------------------------------------------------------*/
void setActorRating(Actor* actor, double rating){
    actor->addRating(rating);
};

/*----------------------------------------------------------------------------
[Coder - Brayden]

Sets the rating for a specific movie.

@param movie: Pointer to the `Movie` object whose rating is to be updated.
@param rating: The new rating to be added to the movie.
@return void

Description:
    - Calls the `addRating` method on the `Movie` object to update the movie's rating.
    - Assumes the rating is a valid double value, typically between 0 and 5.
    - Updates the movie's cumulative rating with the provided value.
----------------------------------------------------------------------------*/
void setMovieRating(Movie* movie, double rating){
    movie->addRating(rating);
};

/*----------------------------------------------------------------------------
[Coder - Tevel]

Recommends the top 5 highest-rated movies from the list.

@param allMovies: Dynamic array containing all `Movie` objects.
@return void

Description:
    - Sorts the `allMovies` dynamic array by movie ratings in descending order.
    - Displays the top 5 movies, showing:
        - Movie rating.
        - Cast average rating (average rating of the actors in the cast).
        - Movie name and release year.
    - Uses the `roundToOneDecimal` function to format ratings to one decimal place.

Error Handling:
    - Assumes the `allMovies` dynamic array contains at least 5 movies.
    - If fewer than 5 movies are present, behavior depends on the array's implementation (may result in an out-of-bounds error).
----------------------------------------------------------------------------*/
void recommendMoviesByRating(DynamicArray<Movie*>& allMovies){
    allMovies.sortByRating();
    cout << "Top highest rated movies:\n";
    cout << "Rating - Cast Rating - Movie Name\n";
    for (int i = 0; i < 5; i++){
        Movie* movie = allMovies.get(i);
        cout << roundToOneDecimal(movie->getRating()) << "⭐  - " << roundToOneDecimal(movie->castAverageRating()) << "⭐       - " << movie->getName() << " (" << movie->getYear() << ")\n";
    };
};

/*----------------------------------------------------------------------------
[Coder - Tevel]

Recommends the top 5 highest-rated actors from the list.

@param allActors: Dynamic array containing all `Actor` objects.
@return void

Description:
    - Sorts the `allActors` dynamic array by actor ratings in descending order.
    - Displays the top 5 actors, showing:
        - Actor rating.
        - Actor name.
    - Uses the `roundToOneDecimal` function to format ratings to one decimal place.

Error Handling:
    - Assumes the `allActors` dynamic array contains at least 5 actors.
    - If fewer than 5 actors are present, behavior depends on the array's implementation (may result in an out-of-bounds error).
----------------------------------------------------------------------------*/
void recommendActorsByRating(DynamicArray<Actor*>& allActors){
    allActors.sortByRating();
    cout << "Top 5 Actors recommended by rating:\n";
    cout << "Rating - Actor Name\n";
    for (int i = 0; i < 5; i++){
        cout << roundToOneDecimal(allActors.get(i)->getRating()) << "⭐  - "<< allActors.get(i)->getName() <<  "\n";
    };
};