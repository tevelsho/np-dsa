/*----------------------------------------------------------------------------
 * DATA STRUCTURES & ALGORITHMS ASSIGNMENT
 *
 * Team Information:
 *   Author 1: Tevel Sho     | S10258591B | Group 4
 *   Author 2: Brayden Saga  | S10258659C | Group 4
 *----------------------------------------------------------------------------*/
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

// Function prototypes (Supporting).
bool authenticateAdmin();
Actor* findActorByName(Dictionary<string, int>& actorNameToIdMap, string actorName, Dictionary<int, Actor*>& actorIdToActorMap);
Movie* findMovieByName(Dictionary<string, int>& movieNameToIdMap, string movieName, Dictionary<int, Movie*>& movieIdToMovieMap);
void adminMenu(Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie, DynamicArray<Actor*>& allActors, DynamicArray<Movie*>& allMovies);
void userMenu(Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie, DynamicArray<Actor*>& allActors, DynamicArray<Movie*>& allMovies);
void readCSV(string fileName, Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Actor*>& yearToActor, AVLTree<Movie*>& yearToMovie, DynamicArray<Actor*>& allActors, DynamicArray<Movie*>& allMovies);
string roundToOneDecimal(double value);

// Function prototypes (Basic).
Movie* duplicateMovieViewer(Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, string movieName);
bool addNewActor(int id, int birth, string name, Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, DynamicArray<Actor*>& allActors);
bool addNewMovie(int id, int year, string name, string plot, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie, DynamicArray<Movie*>& allMovies);
bool addActorToMovie(Actor* actor, Movie* movie);
bool removeActorFromMovie(Actor* actor, Movie* movie);
void updateActorDetails(Actor* actorToUpdate, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor);
void updateMovieDetails(Movie* movieToUpdate, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie);
void displayActorsByAgeRange(int x, int y, AVLTree<Actor*>& yearToActor);
void displayRecentMovies(AVLTree<Movie*>& yearToMovie);
void displayActorsByMovie(Movie* movie); 
void displayMoviesByActor(Actor* actor); 
void displayActorsKnownBy(Actor* actor);
void displayActorsKnownByHelper(Actor* actor, DynamicArray<Actor*>& actors_known);

// Function prototypes (Advanced).
void setActorRating(Actor* actor, double rating);
void setMovieRating(Movie* movie, double rating);  
void recommendActorsByRating(DynamicArray<Actor*>& allActors);
void recommendMoviesByRating(DynamicArray<Movie*>& allMovies);

// Maximum number of Admin accounts.
const int MAX_ADMINS = 1;

// Admin credentials (hardcoded, stored in array).
char adminUsername[MAX_ADMINS][20] = {"admin"};
char adminPassword[MAX_ADMINS][20] = {"password"};

/*----------------------------------------------------------------------------
 * Main Function
 *
 * Description:
 *   This is the entry point of the program. It performs the following tasks:
 *     - Initializes dynamic arrays, dictionaries, and AVL trees to store and map
 *       actors and movies.
 *     - Reads data from "actors.csv", "movies.csv", and "cast.csv" to populate
 *       these data structures.
 *     - Prompts the user to indicate whether they are an administrator or a normal
 *       user.
 *         * If the user is an administrator, up to three authentication attempts
 *           are provided. Upon successful authentication, the adminMenu() is invoked.
 *           If authentication fails, the user is redirected to the userMenu().
 *         * If the user is a normal user, the program directly calls userMenu().
 *         * If the user opts to quit (by entering 'q'), a farewell message is displayed
 *           and the program exits.
 *   The function ensures robust input handling and appropriate redirection based on
 *   the user's responses.
 *
 * Returns:
 *   int - Returns 0 upon successful execution.
 *----------------------------------------------------------------------------*/
int main() {
    // Initialize dynamic arrays to hold all actors and movies.
    DynamicArray<Actor*> allActors;
    DynamicArray<Movie*> allMovies;

    // Initialize dictionaries to map actor IDs to Actor pointers and actor names to IDs.
    Dictionary<int, Actor*> actorIdToActorMap;
    Dictionary<string, int> actorNameToIdMap;

    // Initialize dictionaries to map movie IDs to Movie pointers and movie names to IDs.
    Dictionary<int, Movie*> movieIdToMovieMap;
    Dictionary<string, int> movieNameToIdMap;

    // Initialize AVL trees to index actors and movies by year.
    AVLTree<Actor*> yearToActor;
    AVLTree<Movie*> yearToMovie;

    // Read CSV files to populate the data structures.
    readCSV("actors.csv", actorIdToActorMap, actorNameToIdMap,
            movieIdToMovieMap, movieNameToIdMap, yearToActor, yearToMovie,
            allActors, allMovies);
    readCSV("movies.csv", actorIdToActorMap, actorNameToIdMap,
            movieIdToMovieMap, movieNameToIdMap, yearToActor, yearToMovie,
            allActors, allMovies);
    readCSV("cast.csv", actorIdToActorMap, actorNameToIdMap,
            movieIdToMovieMap, movieNameToIdMap, yearToActor, yearToMovie,
            allActors, allMovies);

    string userInput;

    // Main loop: Continuously prompt the user until they choose to quit.
    while (true) {
        cout << "Are you an administrator? (y/n, q to quit): ";
        cin >> userInput;

        if (userInput == "y" || userInput == "Y") {
            // Administrator flow: Allow up to three attempts for authentication.
            bool adminAuthenticated = false;
            for (int attempts = 0; attempts < 3; attempts++) {
                if (authenticateAdmin()) {
                    adminAuthenticated = true;
                    break;
                } else {
                    cout << "Invalid credentials! Try again (" 
                         << (2 - attempts) << " attempts remaining).\n";
                }
            }

            // Redirect based on authentication result.
            if (adminAuthenticated) {
                cout << "Welcome, Admin!\n";
                adminMenu(actorIdToActorMap, actorNameToIdMap, yearToActor,
                          movieIdToMovieMap, movieNameToIdMap, yearToMovie,
                          allActors, allMovies);
            } else {
                cout << "Failed all attempts! You will be logged in as a normal user.\n";
                userMenu(actorIdToActorMap, actorNameToIdMap, yearToActor,
                         movieIdToMovieMap, movieNameToIdMap, yearToMovie,
                         allActors, allMovies);
            }
        }
        else if (userInput == "n" || userInput == "N") {
            // Normal user flow.
            cout << "Welcome, User!\n";
            userMenu(actorIdToActorMap, actorNameToIdMap, yearToActor,
                     movieIdToMovieMap, movieNameToIdMap, yearToMovie,
                     allActors, allMovies);
        }
        else if (userInput == "q" || userInput == "Q") {
            // Quit the application.
            cout << "Thank you for visiting Silver Village! Hope to see you next time!\n";
            break;
        }
        else {
            // Handle invalid input.
            cout << "Invalid input! Please enter 'y' for yes, 'n' for no, or 'q' to quit: ";
        }
    }
    return 0;
}

/*----------------------------------------------------------------------------
 * Function: authenticateAdmin
 * Author: Tevel
 *
 * Description:
 *   Prompts the user to enter an admin username and password, then compares the 
 *   entered credentials against a list of stored admin credentials. The comparison 
 *   is done character-by-character to ensure an exact match.
 *
 * Parameters:
 *   None.
 *
 * Returns:
 *   bool - Returns true if the entered credentials match one of the stored admin 
 *          credentials; otherwise, returns false.
 *
 *----------------------------------------------------------------------------*/
bool authenticateAdmin() {
    char username[20], password[20];

    // Prompt the admin to enter username and password.
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;

    // Loop through all stored admin credentials.
    for (int i = 0; i < MAX_ADMINS; i++) {
        bool usernameMatch = true;
        bool passwordMatch = true;

        // Compare the entered username with the stored username at index i.
        for (int j = 0; username[j] != '\0' || adminUsername[i][j] != '\0'; j++) {
            if (username[j] != adminUsername[i][j]) {
                usernameMatch = false;
                break;
            }
        }

        // Compare the entered password with the stored password at index i.
        for (int j = 0; password[j] != '\0' || adminPassword[i][j] != '\0'; j++) {
            if (password[j] != adminPassword[i][j]) {
                passwordMatch = false;
                break;
            }
        }

        // If both username and password match, grant admin access.
        if (usernameMatch && passwordMatch) {
            return true;
        }
    }
    // If no matching credentials are found, deny access.
    return false;
}

/*----------------------------------------------------------------------------
 * Function: findActorByName
 * Author: Brayden
 *
 * Description:
 *   Searches for an actor by their name. The function first checks if the 
 *   actor's name exists in the `actorNameToIdMap` dictionary, retrieving their 
 *   associated ID. If the ID is found, it then searches for the corresponding 
 *   `Actor` object in the `actorIdToActorMap` dictionary.
 *
 * Parameters:
 *   actorNameToIdMap - Dictionary mapping actor names to their corresponding IDs.
 *   actorName        - The name of the actor to search for.
 *   actorIdToActorMap- Dictionary mapping actor IDs to their corresponding 
 *                      Actor objects.
 *
 * Returns:
 *   Actor* - A pointer to the Actor object if found; otherwise, returns nullptr.
 *
 * Error Handling:
 *   - Ensures that the actor name exists in `actorNameToIdMap` before retrieving the ID.
 *   - Ensures that the retrieved actor ID exists in `actorIdToActorMap` before returning 
 *     the Actor object.
 *   - Returns `nullptr` if the actor name is not found or if the actor ID does not exist.
 *----------------------------------------------------------------------------*/
Actor* findActorByName(Dictionary<string, int>& actorNameToIdMap, 
                       string actorName, 
                       Dictionary<int, Actor*>& actorIdToActorMap) {
    // Check if the actor name exists in the dictionary.
    if (!actorNameToIdMap.contains(actorName)) {
        return nullptr;  // Actor name not found.
    }

    // Retrieve the actor's ID using their name.
    int actorID = actorNameToIdMap.get(actorName);

    // Verify that the actor ID exists in the actor map.
    if (!actorIdToActorMap.contains(actorID)) {
        return nullptr;  // Actor ID not found.
    }

    // Return the corresponding Actor object.
    return actorIdToActorMap.get(actorID);
}

/*----------------------------------------------------------------------------
 * Function: findMovieByName
 * Author: Brayden
 *
 * Description:
 *   Searches for a movie by its name. The function first checks if the movie's
 *   name exists in the `movieNameToIdMap` dictionary, retrieving its associated
 *   ID. If the ID is found, it then searches for the corresponding `Movie` 
 *   object in the `movieIdToMovieMap` dictionary.
 *
 * Parameters:
 *   movieNameToIdMap - Dictionary mapping movie names to their corresponding IDs.
 *   movieName        - The name of the movie to search for.
 *   movieIdToMovieMap- Dictionary mapping movie IDs to their corresponding 
 *                      Movie objects.
 *
 * Returns:
 *   Movie* - A pointer to the Movie object if found; otherwise, returns nullptr.
 *
 * Error Handling:
 *   - Ensures that the movie name exists in `movieNameToIdMap` before retrieving the ID.
 *   - Ensures that the retrieved movie ID exists in `movieIdToMovieMap` before returning 
 *     the Movie object.
 *   - Returns `nullptr` if the movie name is not found or if the movie ID does not exist.
 *----------------------------------------------------------------------------*/
Movie* findMovieByName(Dictionary<string, int>& movieNameToIdMap, 
                       string movieName, 
                       Dictionary<int, Movie*>& movieIdToMovieMap) {
    // Check if the movie name exists in the dictionary.
    if (!movieNameToIdMap.contains(movieName)) {
        return nullptr;  // Movie name not found.
    }

    // Retrieve the movie's ID using its name.
    int movieID = movieNameToIdMap.get(movieName);

    // Verify that the movie ID exists in the movie map.
    if (!movieIdToMovieMap.contains(movieID)) {
        return nullptr;  // Movie ID not found.
    }

    // Return the corresponding Movie object.
    return movieIdToMovieMap.get(movieID);
}

/*----------------------------------------------------------------------------
 * Function: adminMenu
 * Author: Tevel
 *
 * Description:
 *   Displays the admin menu and handles administrator operations. The menu
 *   allows the admin to perform various actions including:
 *     1. Add a New Actor
 *     2. Add a New Movie
 *     3. Assign an Actor to a Movie
 *     4. Update Actor Details
 *     5. Update Movie Details
 *     0. Log Out of Admin
 *
 *   The function continuously prompts the admin to select an option until
 *   they choose to log out. It validates the input to ensure that the selection
 *   is within the allowed range (0–5) and displays appropriate error messages for
 *   invalid input or operations (e.g., duplicate IDs, missing actors or movies).
 *   It calls helper functions such as addNewActor, addNewMovie, addActorToMovie,
 *   updateActorDetails, and updateMovieDetails to perform specific tasks.
 *
 * Parameters:
 *   actorIdToActorMap  - Dictionary mapping actor IDs to their corresponding Actor objects.
 *   actorNameToIdMap   - Dictionary mapping actor names to their corresponding IDs.
 *   yearToActor        - AVLTree mapping actor birth years to Actor objects.
 *   movieIdToMovieMap  - Dictionary mapping movie IDs to their corresponding Movie objects.
 *   movieNameToIdMap   - Dictionary mapping movie names to their corresponding IDs.
 *   yearToMovie        - AVLTree mapping movie release years to Movie objects.
 *   allActors          - Dynamic array containing all Actor objects.
 *   allMovies          - Dynamic array containing all Movie objects.
 *
 * Returns:
 *   void
 *----------------------------------------------------------------------------*/
void adminMenu(Dictionary<int, Actor*>& actorIdToActorMap,
               Dictionary<string, int>& actorNameToIdMap,
               AVLTree<Actor*>& yearToActor,
               Dictionary<int, Movie*>& movieIdToMovieMap,
               Dictionary<string, int>& movieNameToIdMap,
               AVLTree<Movie*>& yearToMovie,
               DynamicArray<Actor*>& allActors,
               DynamicArray<Movie*>& allMovies) {
    int option;

    do {
        // Display the admin menu header and options.
        cout << "\n=============================================\n";
        cout << "          Silver Village Admin Menu          \n";
        cout << "=============================================\n";
        cout << " [1] Add a New Actor\n";
        cout << " [2] Add a New Movie\n";
        cout << " [3] Assign an Actor to a Movie\n";
        cout << " [4] Remove an Actor from a Movie\n";
        cout << " [5] Update Actor Details\n";
        cout << " [6] Update Movie Details\n";
        cout << " [0] Log Out of Admin\n";
        cout << "=============================================\n";
        cout << "Please select an option by entering the number: ";
        cin >> option;

        // Validate the input: Ensure an integer is entered.
        if (cin.fail()) {
            cin.clear(); // Clear the error flag.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input.
            cout << "\nInvalid choice! Please enter a number between 0 and 6.\n";
            continue;
        }

        // Validate that the option is within the allowed range.
        if (option < 0 || option > 6) {
            cout << "\nInvalid choice! Please enter a number between 0 and 6.\n";
            continue;
        }

        // Process the selected option.
        switch (option) {
            case 0: {
                // Log out from admin mode.
                cout << "Logged out from Admin\n";
                break;
            }
            case 1: {
                // Option 1: Add a new actor.
                cout << "Adding a new actor...\n";
                int actorId, actorBirthYear;
                string actorName;

                // Prompt for the actor's ID.
                cout << "Enter new actor's ID: ";
                while (!(cin >> actorId) || actorId < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid number for actor ID: ";
                }

                // Check for duplicate actor ID.
                if (actorIdToActorMap.contains(actorId)) {
                    cout << "Error: Actor ID already exists or is invalid. Please choose a different ID.\n";
                    break;
                }

                // Clear the input buffer.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Prompt for the actor's name.
                cout << "Enter new actor's name: ";
                getline(cin, actorName);

                // Check for duplicate actor name.
                if (actorNameToIdMap.contains(actorName)) {
                    cout << "Error: Actor name already exists. Please choose a different name.\n";
                    break;
                }

                // Prompt for the actor's year of birth.
                cout << "Enter new actor's year of birth: ";
                while (!(cin >> actorBirthYear) || actorBirthYear < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid number for actor year of birth: ";
                }

                // Add the new actor.
                addNewActor(actorId, actorBirthYear, actorName, actorIdToActorMap, actorNameToIdMap, yearToActor, allActors);
                cout << "Actor successfully added!\n";
                break;
            }
            case 2: {
                // Option 2: Add a new movie.
                cout << "Adding a new movie...\n";
                int movieId, movieReleaseYear;
                string movieName, moviePlot, movieActor;

                // Prompt for the movie's ID.
                cout << "Enter new movie's ID: ";
                while (!(cin >> movieId) || movieId < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid non-negative number for movie ID: ";
                }

                // Check for duplicate movie ID.
                if (movieIdToMovieMap.contains(movieId)) {
                    cout << "Error: Movie ID already exists. Please choose a different ID.\n";
                    break;
                }

                // Clear the input buffer.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Prompt for the movie's name.
                cout << "Enter new movie's name: ";
                getline(cin, movieName);

                // Check for duplicate movie name.
                if (movieNameToIdMap.contains(movieName)) {
                    cout << "Error: Movie name already exists. Please choose a different name.\n";
                    break;
                }

                // Prompt for the movie's plot.
                cout << "Enter new movie's plot: ";
                getline(cin, moviePlot);

                // Prompt for the movie's release year.
                cout << "Enter new movie's release year: ";
                while (!(cin >> movieReleaseYear) || movieReleaseYear < 0) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cin.clear();
                    cout << "Invalid input. Please enter a valid non-negative number for movie release year: ";
                }

                // Attempt to add the new movie.
                if (addNewMovie(movieId, movieReleaseYear, movieName, moviePlot, movieIdToMovieMap, movieNameToIdMap, yearToMovie, allMovies)) {
                    cout << "Movie successfully added!\n";
                    // Prompt for the movie's cast.
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter name of actor to add to movie (blank to quit): ";
                    while (true) {
                        getline(cin, movieActor);
                        if (movieActor.empty()) {
                            break;
                        } else if (!actorNameToIdMap.contains(movieActor)) {
                            cout << "Error: Actor not found. Please check the name and try again: ";
                            continue;
                        } else {
                            Actor* actor = findActorByName(actorNameToIdMap, movieActor, actorIdToActorMap);
                            Movie* movie = movieIdToMovieMap.get(movieId);
                            if (addActorToMovie(actor, movie)){
                                cout << "Success: " << movieActor << " has been successfully assigned to \"" << movieName << "\". Add another actor: ";
                            } else {
                                cout << "Please try again: ";
                            }
                            continue;
                        }
                    }
                    
                } else {
                    cout << "Failed to add movie due to an error.\n";
                }
                break;
            }
            case 3: {
                // Option 3: Assign an actor to a movie.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string actorName, movieName;
                while (true) {
                    // Prompt for the actor's name.
                    cout << "Enter the actor's name: ";
                    getline(cin, actorName);

                    if (actorName.empty()) {
                        cout << "Error: Actor name cannot be empty. Please enter a valid name.\n";
                        continue;
                    }

                    // Retrieve the Actor object.
                    Actor* actor = findActorByName(actorNameToIdMap, actorName, actorIdToActorMap);
                    if (actor == nullptr) {
                        cout << "Error: Actor not found. Please check the name and try again.\n";
                        continue;
                    }

                    while (true) {
                        // Prompt for the movie's name.
                        cout << "Enter the movie's name: ";
                        getline(cin, movieName);

                        if (movieName.empty()) {
                            cout << "Error: Movie name cannot be empty. Please enter a valid name.\n";
                            continue;
                        }

                        // Retrieve the Movie object.
                        Movie* movie = findMovieByName(movieNameToIdMap, movieName, movieIdToMovieMap);
                        if (movie == nullptr) {
                            cout << "Error: Movie not found. Please check the name and try again.\n";
                            continue;
                        }

                        // Assign the actor to the movie.
                        addActorToMovie(actor, movie);
                        cout << "Success: " << actorName << " has been successfully assigned to \"" << movieName << "\".\n";
                        break; // Exit movie loop.
                    }
                    break; // Exit actor loop.
                }
                break;
            }
            case 4: {
                // Option 4: Remove an actor from a movie.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string actorName, movieName;
                while (true) {
                    // Prompt for the movie's name.
                    cout << "Enter the movie's name: ";
                    getline(cin, movieName);

                    if (movieName.empty()) {
                        cout << "Error: Movie name cannot be empty. Please enter a valid name.\n";
                        continue;
                    }

                    // Retrieve the Movie object.
                    Movie* movie = findMovieByName(movieNameToIdMap, movieName, movieIdToMovieMap);
                    if (movie == nullptr) {
                        cout << "Error: Movie not found. Please check the name and try again.\n";
                        continue;
                    }

                    // Display actors in this movie.
                    displayActorsByMovie(movie);

                    while (true) {
                        // Prompt for the actor's name.
                        cout << "Enter the actor's name: ";
                        getline(cin, actorName);

                        if (actorName.empty()) {
                            break;
                        }

                        // Retrieve the Actor object.
                        Actor* actor = findActorByName(actorNameToIdMap, actorName, actorIdToActorMap);
                        if (actor == nullptr) {
                            cout << "Error: Actor not found. Please check the name and try again.\n";
                            continue;
                        }

                        // Remove the actor from the movie.
                        if (removeActorFromMovie(actor, movie)) {
                            cout << "Success: " << actorName << " has been successfully removed from \"" << movieName << "\".\n";
                        } else {
                            cout << "Error: " << actorName << " is not part of \"" << movieName << "\".\n";
                        }
                        break; // Exit actor loop.
                    }
                    break; // Exit movie loop.
                }

                break;
            }
            case 5: {
                // Option 5: Update actor details.
                string actorName;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (true) {
                    cout << "Enter the actor's name to update: ";
                    getline(cin, actorName);

                    if (actorName.empty()) {
                        cout << "Error: Actor name cannot be empty. Please try again.\n";
                        continue;
                    }

                    // Retrieve the Actor object.
                    Actor* actorToUpdate = findActorByName(actorNameToIdMap, actorName, actorIdToActorMap);
                    if (actorToUpdate != nullptr) {
                        updateActorDetails(actorToUpdate, actorNameToIdMap, yearToActor);
                        break;  // Exit loop after successful update.
                    } else {
                        cout << "Error: Actor not found. Please ensure the name is correct.\n";
                    }
                }
                break;
            }
            case 6: {
                // Option 6: Update movie details.
                string movieName;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (true) {
                    cout << "Enter the movie's name to update: ";
                    getline(cin, movieName);

                    if (movieName.empty()) {
                        cout << "Error: Movie name cannot be empty. Please try again.\n";
                        continue;
                    }

                    // Retrieve the Movie object.
                    Movie* movieToUpdate = findMovieByName(movieNameToIdMap, movieName, movieIdToMovieMap);
                    if (movieToUpdate != nullptr) {
                        updateMovieDetails(movieToUpdate, movieNameToIdMap, yearToMovie);
                        break;  // Exit loop after successful update.
                    } else {
                        cout << "Error: Movie not found. Please ensure the name is correct.\n";
                    }
                }
                break;
            }
            default: {
                // This default case should not be reached due to prior validation.
                cout << "Error: Unexpected error occurred.\n";
                break;
            }
        }
    } while (option != 0);
}

/*----------------------------------------------------------------------------
 * Function: readCSV
 * Author: Tevel
 *
 * Description:
 *   Reads and processes a CSV file based on its type and populates appropriate
 *   data structures with actor and movie information. Supported file names include:
 *     - "actors.csv": Contains actor information with columns (id, name, birth).
 *     - "cast.csv": Contains cast information with columns (person_id, movie_id).
 *     - "movies.csv": Contains movie information with columns (id, title, year, plot).
 *
 * Parameters:
 *   fileName           - The name of the CSV file to read from the "./data/" directory.
 *   actorIdToActorMap  - Dictionary mapping actor IDs to their corresponding Actor objects.
 *   actorNameToIdMap   - Dictionary mapping actor names to their corresponding IDs.
 *   movieIdToMovieMap  - Dictionary mapping movie IDs to their corresponding Movie objects.
 *   movieNameToIdMap   - Dictionary mapping movie names to their corresponding IDs.
 *   yearToActor        - AVLTree mapping actor birth years to Actor objects.
 *   yearToMovie        - AVLTree mapping movie release years to Movie objects.
 *   allActors          - Dynamic array containing all Actor objects.
 *   allMovies          - Dynamic array containing all Movie objects.
 *
 * Returns:
 *   void
 *
 * Error Handling:
 *   - If the file cannot be opened, displays an error message.
 *   - Handles unsupported file names by displaying an error message and closing the file.
 *----------------------------------------------------------------------------*/
void readCSV(string fileName,
             Dictionary<int, Actor*>& actorIdToActorMap,
             Dictionary<string, int>& actorNameToIdMap,
             Dictionary<int, Movie*>& movieIdToMovieMap,
             Dictionary<string, int>& movieNameToIdMap,
             AVLTree<Actor*>& yearToActor,
             AVLTree<Movie*>& yearToMovie,
             DynamicArray<Actor*>& allActors,
             DynamicArray<Movie*>& allMovies) {
    // Construct the full file path.
    fstream inputFile;
    string filePath = "./data/" + fileName;

    // Open the CSV file in input mode.
    inputFile.open(filePath, ios::in);
    if (!inputFile.is_open()) {
        cout << "Error: Could not open file!" << endl;
        return;
    }

    string line, word;
    // Skip the header line.
    getline(inputFile, line);

    // Process the file based on its name.
    if (fileName == "actors.csv") {
        // Process "actors.csv": Each line contains actor id, name, and birth year.
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string temp, actorName;
            int actorId, actorBirthYear;

            // Parse actor ID.
            getline(ss, temp, ',');
            actorId = stoi(temp);

            // Parse actor name.
            getline(ss, actorName, ',');
            // Remove quotes from the actor name if present.
            if (actorName.size() > 1 && actorName.front() == '"' && actorName.back() == '"') {
                actorName = actorName.substr(1, actorName.size() - 2);
            }

            // Parse actor birth year.
            getline(ss, temp, ',');
            if (temp == "")
                actorBirthYear = 0;
            else
                actorBirthYear = stoi(temp);

            // Add the new actor to the data structures.
            addNewActor(actorId, actorBirthYear, actorName, actorIdToActorMap, actorNameToIdMap, yearToActor, allActors);
        }
        inputFile.close();
    }
    else if (fileName == "cast.csv") {
        // Process "cast.csv": Each line contains a person ID and a movie ID.
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string temp;
            int personID, movieID;

            // Parse person ID.
            getline(ss, temp, ',');
            personID = stoi(temp);

            // Parse movie ID.
            getline(ss, temp, ',');
            movieID = stoi(temp);

            // Retrieve the corresponding Actor and Movie objects.
            Actor* actor = actorIdToActorMap.get(personID);
            Movie* movie = movieIdToMovieMap.get(movieID);

            // Establish the bidirectional relationship.
            addActorToMovie(actor, movie);
        }
        inputFile.close();
    }
    else if (fileName == "movies.csv") {
        // Process "movies.csv": Each line contains movie id, title, plot, and year.
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string temp, title, plot;
            int movieId, releaseYear;

            // Parse movie ID.
            getline(ss, temp, ',');
            movieId = stoi(temp);

            // Parse movie title (handle titles enclosed in quotes).
            if (ss.peek() == '"') {
                getline(ss, temp, '"'); // Skip the initial quote.
                getline(ss, title, '"'); // Read title.
                ss.get(); // Skip the comma.
            } else {
                getline(ss, title, ',');
            }

            // Parse movie plot (handle plots enclosed in quotes).
            if (ss.peek() == '"') {
                getline(ss, temp, '"'); // Skip the initial quote.
                while (getline(ss, temp, '"')) {
                    plot += temp;
                    if (ss.peek() == '"') {
                        plot += '"'; // Append escaped quote.
                        ss.get();    // Skip the escape quote.
                    } else {
                        break;
                    }
                }
                ss.get(); // Skip the comma.
            } else {
                getline(ss, plot, ',');
            }

            // Parse movie release year.
            getline(ss, temp);
            releaseYear = stoi(temp);

            // Add the new movie to the data structures.
            addNewMovie(movieId, releaseYear, title, plot, movieIdToMovieMap, movieNameToIdMap, yearToMovie, allMovies);
        }
        inputFile.close();
    }
    else {
        // Handle unsupported file names.
        cout << "Error: Unsupported file name \"" << fileName << "\". Please provide a valid file name." << endl;
        inputFile.close();
    }
}

/*----------------------------------------------------------------------------
 * Function: addNewActor
 * Author: Brayden
 *
 * Description:
 *   Adds a new actor to the system and updates the relevant data structures.
 *   This function creates a new Actor object using the provided `id`, `name`, 
 *   and `birth` year, then integrates it into multiple data structures for 
 *   efficient retrieval and organization.
 *
 * Parameters:
 *   id                - Unique integer identifier for the actor.
 *   birth             - Birth year of the actor.
 *   name              - Full name of the actor.
 *   actorIdToActorMap - Dictionary mapping actor IDs to their corresponding 
 *                       Actor objects.
 *   actorNameToIdMap  - Dictionary mapping actor names to their corresponding 
 *                       unique IDs.
 *   yearToActor       - AVLTree that organizes actors by their birth year.
 *   allActors         - Dynamic array containing all Actor objects for easy iteration.
 *
 * Returns:
 *   bool - Returns true if the actor is successfully added to all data structures; 
 *          returns false if any insertion fails due to invalid input.
 *
 * Error Handling:
 *   - Checks for duplicate actor ID and name before insertion.
 *   - Ensures input parameters are valid (non-empty name, valid birth year).
 *   - Handles memory allocation failures.
 *   - Assumes that `add`, `insertItem`, and `addActor` methods handle internal duplicates.
 *----------------------------------------------------------------------------*/
bool addNewActor(int actorId, int actorBirthYear, string actorName, 
                 Dictionary<int, Actor*>& actorIdToActorMap, 
                 Dictionary<string, int>& actorNameToIdMap, 
                 AVLTree<Actor*>& yearToActor, 
                 DynamicArray<Actor*>& allActors) {
    // Validate input: actor name must not be empty and birth year must be positive.
    if (actorName.empty() || actorBirthYear <= 0) {
        return false;  // Invalid actor name or birth year.
    }

    // Check for duplicate actor ID.
    if (actorIdToActorMap.contains(actorId)) {
        return false;  // Duplicate actor ID detected.
    }

    // Check for duplicate actor name.
    if (actorNameToIdMap.contains(actorName)) {
        return false;  // Duplicate actor name detected.
    }

    // Create a new Actor object using nothrow to handle memory allocation failure.
    Actor* newActor = new (std::nothrow) Actor(actorId, actorName, actorBirthYear);
    if (!newActor) {
        return false;  // Memory allocation failed.
    }

    // Insert the new actor into the actor ID map.
    actorIdToActorMap.add(actorId, newActor);

    // Insert the new actor's name to ID mapping.
    actorNameToIdMap.add(actorName, actorId);

    // Add the actor to the dynamic array for iteration.
    allActors.add(newActor);

    // Insert the actor into the AVL tree keyed by birth year.
    yearToActor.insertItem(actorBirthYear, newActor);

    return true;  // Actor successfully added to all data structures.
}

/*----------------------------------------------------------------------------
 * Function: addNewMovie
 * Author: Tevel
 *
 * Description:
 *   Adds a new movie to the system and updates all relevant data structures.
 *   This function creates a new Movie object and integrates it into multiple 
 *   mappings and data structures to allow efficient retrieval and organization.
 *
 * Parameters:
 *   id                  - Unique integer identifier for the movie.
 *   year                - Release year of the movie.
 *   name                - Name or title of the movie.
 *   plot                - Plot summary of the movie.
 *   movieIdToMovieMap   - Dictionary mapping movie IDs to their corresponding 
 *                         Movie objects.
 *   movieNameToIdMap    - Dictionary mapping movie names to their corresponding 
 *                         unique IDs.
 *   yearToMovie         - AVLTree that organizes movies by their release year.
 *   allMovies           - Dynamic array containing all Movie objects for easy iteration.
 *
 * Returns:
 *   bool - Returns true if the movie is successfully added to all data structures; 
 *          returns false if any insertion fails due to invalid input.
 *
 * Error Handling:
 *   - Checks for duplicate movie ID and title before insertion.
 *   - Ensures input parameters are valid (non-empty name, valid year).
 *   - Handles memory allocation failures.
 *   - Assumes that `add`, `insertItem`, and `addMovie` methods handle internal duplicates.
 *----------------------------------------------------------------------------*/
bool addNewMovie(int movieId, int releaseYear, string movieTitle, string plot, 
                 Dictionary<int, Movie*>& movieIdToMovieMap, 
                 Dictionary<string, int>& movieNameToIdMap, 
                 AVLTree<Movie*>& yearToMovie, 
                 DynamicArray<Movie*>& allMovies) {
    // Validate input: movie title must not be empty and release year must be positive.
    if (movieTitle.empty() || releaseYear <= 0) {
        return false;  // Invalid movie title or release year.
    }

    // Check for duplicate movie ID.
    if (movieIdToMovieMap.contains(movieId)) {
        return false;  // Duplicate movie ID detected.
    }

    // Check for duplicate movie title.
    if (movieNameToIdMap.contains(movieTitle)) {
        for (int i = 2; i < 100; i++) {
            if (!(movieNameToIdMap.contains(movieTitle + " " + to_string(i)))) {
                movieTitle = movieTitle + " " + to_string(i);
                break;
            }
        }
    }

    // Create a new Movie object using nothrow to handle memory allocation failure.
    Movie* newMovie = new (std::nothrow) Movie(movieId, movieTitle, plot, releaseYear);
    if (!newMovie) {
        return false;  // Memory allocation failed.
    }

    // Insert the new movie into the movie ID map.
    movieIdToMovieMap.add(movieId, newMovie);

    // Insert the new movie's title to ID mapping.
    movieNameToIdMap.add(movieTitle, movieId);

    // Add the movie to the dynamic array for iteration.
    allMovies.add(newMovie);

    // Insert the movie into the AVL tree keyed by release year.
    yearToMovie.insertItem(releaseYear, newMovie);

    return true;  // Movie successfully added to all data structures.
}

/*----------------------------------------------------------------------------
 * Function: addActorToMovie
 * Author: Brayden
 *
 * Description:
 *   Establishes a bidirectional relationship between an actor and a movie.
 *   This function updates the Actor object by adding the Movie to its list of associated
 *   movies and updates the Movie object by adding the Actor to its list of associated actors.
 *
 * Parameters:
 *   actor - Pointer to the Actor object to be assigned to the movie.
 *   movie - Pointer to the Movie object to which the actor will be assigned.
 *
 * Returns:
 *   bool - Returns true if the actor is successfully added to the movie and vice versa.
 *
 * Error Handling:
 *   - Checks if the actor and movie pointers are valid before proceeding.
 *   - Ensures that addMovie and addActor methods are called only when both objects are valid.
 *   - Assumes that the addMovie and addActor methods internally handle duplicate entries.
 *----------------------------------------------------------------------------*/
bool addActorToMovie(Actor* actor, Movie* movie) {
    // Validate input: Check that both the actor and movie pointers are not null.
    if (actor == nullptr) {
        cerr << "Error: Actor pointer is null." << std::endl;
        return false;
    }
    if (movie == nullptr) {
        cerr << "Error: Movie pointer is null." << std::endl;
        return false;
    }
    if (movie->hasActor(actor)) {
        cerr << "Error: Actor already assigned to movie." << std::endl;
        return false;
    }

    // Establish the bidirectional relationship:
    // Add the movie to the actor's list of movies.
    actor->addMovie(movie);
    // Add the actor to the movie's list of actors.
    movie->addActor(actor);

    return true;  // Relationship successfully established.
}

/*----------------------------------------------------------------------------
 * Function: removeActorFromMovie
 * Author: Brayden
 *
 * Description:
 *   Deletes a bidirectional relationship between an actor and a movie.
 *   This function updates the Actor object by removing the Movie from its list of associated
 *   movies and updates the Movie object by removing the Actor from its list of associated actors.
 *
 * Parameters:
 *   actor - Pointer to the Actor object to be removed from the movie.
 *   movie - Pointer to the Movie object from which the actor will be removed.
 *
 * Returns:
 *   bool - Returns true if the actor is successfully removed from the movie and vice versa.
 *
 * Error Handling:
 *   - Checks if the actor and movie pointers are valid before proceeding.
 *   - Ensures that addMovie and addActor methods are called only when both objects are valid.
 *   - Assumes that the addMovie and addActor methods internally handle duplicate entries.
 *----------------------------------------------------------------------------*/
bool removeActorFromMovie(Actor* actor, Movie* movie) {
    // Validate input: Check that both the actor and movie pointers are not null.
    if (actor == nullptr) {
        cerr << "Error: Actor pointer is null." << std::endl;
        return false;
    }
    if (movie == nullptr) {
        cerr << "Error: Movie pointer is null." << std::endl;
        return false;
    }

    // Remove the actor from the movie's list of actors.
    if (!movie->removeActor(actor)) {
        cerr << "Error: Actor not found in movie." << std::endl;
        return false;
    }

    // Remove the movie from the actor's list of movies.
    if (!actor->removeMovie(movie)) {
        cerr << "Error: Movie not found in actor." << std::endl;
        return false;
    }

    return true;  // Actor successfully removed from the movie.
}

/*----------------------------------------------------------------------------
 * Function: updateActorDetails
 * Author: Tevel
 *
 * Description:
 *   Updates the details of an existing actor in the system. The function displays the
 *   current details of the actor, prompts the user for new information (name and year
 *   of birth), and updates the actor's record accordingly. It also updates relevant data
 *   structures to maintain consistency.
 *
 * Parameters:
 *   actorToUpdate    - Pointer to the Actor object whose details are to be updated.
 *   actorNameToIdMap - Dictionary mapping actor names to their corresponding IDs.
 *   yearToActor      - AVLTree mapping actor birth years to Actor objects.
 *
 * Returns:
 *   void
 *
 * Error Handling:
 *   - Assumes that the provided actorToUpdate pointer is valid and properly initialized.
 *   - If invalid input is provided for the new year of birth, the function displays an error
 *     message and retains the current details.
 *   - Catches exceptions during updates to maintain data consistency.
 *----------------------------------------------------------------------------*/
void updateActorDetails(Actor* actorToUpdate, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor) {
    // Validate input: Ensure the actor pointer is valid.
    if (actorToUpdate == nullptr) {
        cerr << "Error: Null pointer provided for actor update.\n";
        return;
    }

    // Display the actor's current details.
    cout << "\nCurrent Details:\n";
    cout << "--------------------------------\n";
    cout << "ID: " << actorToUpdate->getID() << "\n";
    cout << "Name: " << actorToUpdate->getName() << "\n";
    cout << "Year of Birth: " << actorToUpdate->getYearOfBirth() << "\n";
    cout << "--------------------------------\n";

    string newName;
    int newYear;

    // Prompt the user for a new name. An empty input retains the current name.
    cout << "Enter the new name (leave blank to keep current): ";
    getline(cin, newName);

    if (actorNameToIdMap.contains(newName)) {
        cout << "Error: Actor name already exists. \n";
        return;
    }

    // Prompt the user for a new year of birth. An empty input retains the current year.
    while (true) {
        cout << "Enter the new year of birth (leave blank to keep current): ";
        string yearInput;
        getline(cin, yearInput);

        if (yearInput.empty()) {
            newYear = actorToUpdate->getYearOfBirth(); // Retain current year.
            break;
        }

        try {
            newYear = stoi(yearInput);
            if (newYear < 0) {
                // Negative years are invalid.
                throw invalid_argument("Year cannot be negative.");
            }
            break; // Valid input received.
        } catch (...) {
            cout << "Invalid input. Please enter a valid non-negative year.\n";
        }
    }

    bool detailsUpdated = false;  // Flag to track if any detail is updated.

    // Update the actor's name if a new valid name is provided and it differs from the current name.
    if (!newName.empty() && newName != actorToUpdate->getName()) {
        actorNameToIdMap.remove(actorToUpdate->getName());
        actorToUpdate->setName(newName);
        actorNameToIdMap.add(newName, actorToUpdate->getID());
        detailsUpdated = true;
    }

    // Update the actor's year of birth if it has changed.
    if (newYear != actorToUpdate->getYearOfBirth()) {
        yearToActor.removeItem(actorToUpdate->getYearOfBirth(), actorToUpdate);
        actorToUpdate->setYearOfBirth(newYear);
        yearToActor.insertItem(newYear, actorToUpdate);
        detailsUpdated = true;
    }

    // Display the updated details if any changes were made.
    if (detailsUpdated) {
        cout << "\nActor details updated successfully!\n";
        cout << "--------------------------------\n";
        cout << "Updated Details:\n";
        cout << "ID: " << actorToUpdate->getID() << "\n";
        cout << "Name: " << actorToUpdate->getName() << "\n";
        cout << "Year of Birth: " << actorToUpdate->getYearOfBirth() << "\n";
        cout << "--------------------------------\n";
    } else {
        cout << "No changes were made. The actor's details remain the same.\n";
    }
}

/*----------------------------------------------------------------------------
 * Function: updateMovieDetails
 * Author: Tevel
 *
 * Description:
 *   Updates the details of an existing movie in the system. This function displays
 *   the current details of the specified movie (ID, title, and year of release), then
 *   prompts the user to enter updated information. If the user leaves the title blank,
 *   the movie's current title is retained; if the user enters -1 for the year, the
 *   current year of release is retained. The function also updates relevant data
 *   structures to ensure consistency.
 *
 * Parameters:
 *   movieToUpdate    - Pointer to the Movie object whose details are to be updated.
 *   movieNameToIdMap - Dictionary mapping movie titles to their corresponding IDs.
 *   yearToMovie      - AVLTree mapping movie release years to Movie objects.
 *
 * Returns:
 *   void
 *
 * Error Handling:
 *   Assumes that the movieToUpdate pointer is valid. If invalid input is provided
 *   for the year of release, an error message is displayed and no changes are made.
 *----------------------------------------------------------------------------*/
void updateMovieDetails(Movie* movieToUpdate, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie) {
    // Validate input: Ensure the movie pointer is valid.
    if (movieToUpdate == nullptr) {
        cerr << "Error: Null pointer provided for movie update.\n";
        return;
    }

    // Display the movie's current details.
    cout << "\nCurrent Details:\n";
    cout << "--------------------------------\n";
    cout << "ID: " << movieToUpdate->getID() << "\n";
    cout << "Title: " << movieToUpdate->getName() << "\n";
    cout << "Plot: " << movieToUpdate->getPlot() << "\n";
    cout << "Year of Release: " << movieToUpdate->getYear() << "\n";
    cout << "--------------------------------\n";

    string newTitle, newPlot;
    int newYear;

    // Prompt the user for a new title. An empty input retains the current title.
    cout << "Enter the new title (leave blank to keep current): ";
    getline(cin, newTitle);

    if (movieNameToIdMap.contains(newTitle)) {
        cout << "Error: Movie title already exists. \n";
        return;
    }

    // Prompt the user for a new plot. An empty input retains the current plot.
    cout << "Enter the new plot (leave blank to keep current): ";
    getline(cin, newPlot);

    // Prompt the user for a new year of release. An empty input retains the current year.
    while (true) {
        cout << "Enter the new year of release (leave blank to keep current): ";
        string yearInput;
        getline(cin, yearInput);

        if (yearInput.empty()) {
            newYear = movieToUpdate->getYear();  // Retain current year.
            break;
        }

        try {
            newYear = stoi(yearInput);
            if (newYear < 0) {
                // Negative years are invalid.
                throw invalid_argument("Year cannot be negative.");
            }
            break; // Valid input received.
        } catch (...) {
            cout << "Invalid input. Please enter a valid non-negative year.\n";
        }
    }

    bool detailsUpdated = false;  // Flag to track if any detail is updated.

    // Update the movie's title if a new valid title is provided and it differs from the current title.
    if (!newTitle.empty() && newTitle != movieToUpdate->getName()) {
        movieNameToIdMap.remove(movieToUpdate->getName());
        movieToUpdate->setName(newTitle);
        movieNameToIdMap.add(newTitle, movieToUpdate->getID());
        detailsUpdated = true;
    }

    // Update the movie's plot if a new plot is provided and it differs from the current plot.
    if (!newPlot.empty() && newPlot != movieToUpdate->getPlot()) {
        movieToUpdate->setPlot(newPlot);
        detailsUpdated = true;
    }

    // Update the movie's year of release if it has changed.
    if (newYear != movieToUpdate->getYear()) {
        yearToMovie.removeItem(movieToUpdate->getYear(), movieToUpdate);
        movieToUpdate->setYear(newYear);
        yearToMovie.insertItem(newYear, movieToUpdate);
        detailsUpdated = true;
    }

    // Display the updated details if any changes were made.
    if (detailsUpdated) {
        cout << "\nMovie details updated successfully!\n";
        cout << "--------------------------------\n";
        cout << "Updated Details:\n";
        cout << "ID: " << movieToUpdate->getID() << "\n";
        cout << "Title: " << movieToUpdate->getName() << "\n";
        cout << "Plot: " << movieToUpdate->getPlot() << "\n";
        cout << "Year of Release: " << movieToUpdate->getYear() << "\n";
        cout << "--------------------------------\n";
    } else {
        cout << "No changes were made. The movie's details remain the same.\n";
    }
}

/*----------------------------------------------------------------------------
 * Function: userMenu
 * Author: Tevel
 *
 * Description:
 *   Displays the user menu and handles user operations. This function provides
 *   an interface for users to interact with the system and perform various operations,
 *   including:
 *     1. Displaying actors by age range.
 *     2. Showing movies released in the last three years.
 *     3. Listing movies an actor starred in (sorted alphabetically).
 *     4. Listing actors in a specific movie (sorted alphabetically).
 *     5. Finding all actors that an actor "knows."
 *     6. Rating an actor (with input validation for ratings between 0 and 5).
 *     7. Rating a movie (with input validation for ratings between 0 and 5).
 *     8. Recommending movies by rating.
 *     9. Recommending actors by rating.
 *    The menu is repeatedly displayed until the user logs out by entering '0'.
 *
 * Parameters:
 *   actorIdToActorMap  - Dictionary mapping actor IDs to their corresponding Actor objects.
 *   actorNameToIdMap   - Dictionary mapping actor names to their corresponding IDs.
 *   yearToActor        - AVLTree mapping actor birth years to Actor objects.
 *   movieIdToMovieMap  - Dictionary mapping movie IDs to their corresponding Movie objects.
 *   movieNameToIdMap   - Dictionary mapping movie names to their corresponding IDs.
 *   yearToMovie        - AVLTree mapping movie release years to Movie objects.
 *   allActors          - Dynamic array containing all Actor objects.
 *   allMovies          - Dynamic array containing all Movie objects.
 *
 * Returns:
 *   void
 *
 * Error Handling:
 *   Validates user input for menu selection (ensuring it is within 0–9) and for operations
 *   requiring additional input (e.g., names, ratings). Displays appropriate error messages if an
 *   actor or movie is not found or if input is invalid.
 *----------------------------------------------------------------------------*/
void userMenu(Dictionary<int, Actor*>& actorIdToActorMap,
              Dictionary<string, int>& actorNameToIdMap,
              AVLTree<Actor*>& yearToActor,
              Dictionary<int, Movie*>& movieIdToMovieMap,
              Dictionary<string, int>& movieNameToIdMap,
              AVLTree<Movie*>& yearToMovie,
              DynamicArray<Actor*>& allActors,
              DynamicArray<Movie*>& allMovies) {
    int userChoice;

    do {
        // Display the user menu header and available options.
        cout << "\n=============================================\n";
        cout << "         Silver Village User Menu            \n";
        cout << "=============================================\n";
        cout << " [1] Display Actors by Age Range\n";
        cout << " [2] Show Movies from the Last 3 Years\n";
        cout << " [3] List Actors in a Specific Movie\n";
        cout << " [4] List Movies an Actor Starred In\n";
        cout << " [5] Find All Actors an Actor Knows\n";
        cout << " [6] Rate an Actor\n";
        cout << " [7] Rate a Movie\n";
        cout << " [8] Recommend Actors by Rating\n";
        cout << " [9] Recommend Movies by Rating\n";
        cout << " [0] Log Out of User\n";
        cout << "=============================================\n";
        cout << "Please select an option by entering the number: ";
        cin >> userChoice;
        
        // Process the user's menu selection using a switch-case structure.
        switch (userChoice) {
            case 0: {
                // Option 0: Log out the user.
                cout << "Logged out from User\n";
                break;
            }
            case 1: {
                // Option 1: Display actors by age range.
                int minAge, maxAge;
                while (true) {
                    cout << "Enter the age range (minAge maxAge): ";
                    cin >> minAge >> maxAge;

                    // Validate that numeric input was provided.
                    if (cin.fail()) {
                        cin.clear(); // Clear error flags.
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input.
                        cout << "Invalid input. Please enter numeric values for the age range.\n";
                        continue;
                    }

                    // Ensure that ages are non-negative.
                    if (minAge < 0 || maxAge < 0) {
                        cout << "Ages cannot be negative. Please enter a valid age range.\n";
                        continue;
                    }

                    // Validate that the minimum age is not greater than the maximum age.
                    if (maxAge < minAge) {
                        cout << "Error: Minimum age cannot be greater than maximum age. Please try again.\n";
                        continue;
                    }
                    break; // Valid input received.
                }
                displayActorsByAgeRange(minAge, maxAge, yearToActor);
                break;
            }
            case 2: {
                // Option 2: Show movies released in the last 3 years.
                displayRecentMovies(yearToMovie);
                break;
            }
            case 3: {
                // Option 3: List actors in a specific movie (sorted alphabetically).
                string movieName;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear leftover newline.

                while (true) {
                    cout << "Enter the movie's name: ";
                    getline(cin, movieName);

                    Movie* movie = duplicateMovieViewer(movieIdToMovieMap, movieNameToIdMap, movieName);

                    if (movie != nullptr) {
                        displayActorsByMovie(movie);
                        break;
                    } else {
                        cout << "Movie not found. Please try again.\n";
                    }
                }
                break;
            }
            case 4: {
                // Option 4: List movies an actor starred in (sorted alphabetically).
                string actorName;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear leftover newline.
                while (true) {
                    cout << "Enter the actor's name: ";
                    getline(cin, actorName);

                    Actor* actor = findActorByName(actorNameToIdMap, actorName, actorIdToActorMap);
                    if (actor != nullptr) {
                        displayMoviesByActor(actor);
                        break;
                    } else {
                        cout << "Actor not found. Please try again.\n";
                    }
                }
                break;
            }
            case 5: {
                // Option 5: Find all actors that a given actor knows.
                string actorName;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear leftover newline.
                while (true) {
                    cout << "Enter the actor's name: ";
                    getline(cin, actorName);
                    
                    Actor* actor = findActorByName(actorNameToIdMap, actorName, actorIdToActorMap);
                    if (actor != nullptr) {
                        displayActorsKnownBy(actor);
                        break;
                    } else {
                        cout << "Actor not found. Please try again.\n";
                    }
                }
                break;
            }
            case 6: {
                // Option 6: Rate an actor.
                string actorName;
                double rating;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear leftover newline.
                cout << "Enter the actor's name: ";
                getline(cin, actorName);

                Actor* actor = findActorByName(actorNameToIdMap, actorName, actorIdToActorMap);
                if (actor == nullptr) {
                    cout << "Actor not found. Please try again.\n";
                    break;
                }

                // Prompt the user for a valid rating between 0 and 5.
                while (true) {
                    cout << "Actor's current rating: " << roundToOneDecimal(actor->getRating()) << endl;
                    cout << "Enter a rating (e.g., 1.5, 4.9): ";
                    cin >> rating;

                    if (cin.fail() || rating < 0 || rating > 5) {
                        cin.clear(); // Clear error flags.
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input.
                        cout << "Invalid input. Please enter a number between 0 and 5." << endl;
                    } else {
                        break; // Valid rating received.
                    }
                }
                setActorRating(actor, rating);
                break;
            }
            case 7: {
                // Option 7: Rate a movie.
                string movieName;
                double rating;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear leftover newline.
                cout << "Enter the movie's name: ";
                getline(cin, movieName);

                Movie* movie = duplicateMovieViewer(movieIdToMovieMap, movieNameToIdMap, movieName);
                if (movie == nullptr) {
                    cout << "Movie not found. Please try again.\n";
                    break;
                }

                // Prompt the user for a valid rating between 0 and 5.
                while (true) {
                    cout << "Movie's current rating: " << roundToOneDecimal(movie->getRating()) << endl;
                    cout << "Enter a rating (e.g., 1.5, 4.9): ";
                    cin >> rating;

                    if (cin.fail() || rating < 0 || rating > 5) {
                        cin.clear(); // Clear error flags.
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input.
                        cout << "Invalid input. Please enter a number between 0 and 5." << endl;
                    } else {
                        break; // Valid rating received.
                    }
                }
                setMovieRating(movie, rating);
                break;
            }
            case 8: {
                // Option 8: Recommend actors by rating.
                recommendActorsByRating(allActors);
                break;
            }
            case 9: {
                // Option 9: Recommend movies by rating.
                recommendMoviesByRating(allMovies);
                break;
            }
            default:
                // Handle invalid menu selections.
                cout << "Invalid choice! Try again.\n";
        }
    } while (userChoice != 0);
}
/*----------------------------------------------------------------------------
 * Function: duplicateMovieViewer
 * Author: Brayden
 *
 * Description:
 *   Given a movie name, either directly finds the movie or prompts the user to
 *   select the correct movie if multiple movies with the same name exist.
 *
 * Parameters:
 *   movieIdToMovieMap - Dictionary mapping movie IDs to their corresponding Movie objects.
 *   movieNameToIdMap  - Dictionary mapping movie names to their corresponding IDs.
 *   movieName         - Name of the movie to find.
 *
 * Returns:
 *   Movie* - Pointer to the Movie object with the specified name.
 *
 * Error Handling:
 *   - Ensures that movie name is entered correctly.
 *----------------------------------------------------------------------------*/
Movie* duplicateMovieViewer(Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, string movieName) {
    if (!(movieNameToIdMap.contains(movieName + " 2"))) {
        return findMovieByName(movieNameToIdMap, movieName, movieIdToMovieMap);
    }
    Movie* movie = findMovieByName(movieNameToIdMap, movieName, movieIdToMovieMap);
    cout << "Movie Name: " << movie->getName() << " Movie Year: " << movie->getYear() << endl;
    for (int i = 2; i < 100; i++) {
        if ((movieNameToIdMap.contains(movieName + " " + to_string(i)))) {
            movie = findMovieByName(movieNameToIdMap, movieName + " " + to_string(i), movieIdToMovieMap);
            cout << "Movie Name: " << movie->getName() << " Movie Year: " << movie->getYear() << endl;
        } else {
            break;
        }
    }
    cout << "Confirm the movie's name: ";
    getline(cin, movieName);
    while (!(movieNameToIdMap.contains(movieName))) {
        cout << "Invalid movie name. Please try again: ";
        getline(cin, movieName);
    }
    movie = findMovieByName(movieNameToIdMap, movieName, movieIdToMovieMap);
    return movie;
}

/*----------------------------------------------------------------------------
 * Function: displayActorsByAgeRange
 * Author: Brayden
 *
 * Description:
 *   Displays a list of actors whose ages fall within the specified range.
 *   Converts the provided age range into corresponding birth years based on the
 *   reference year (2025) and utilizes an AVLTree to display actors born within
 *   that period.
 *
 * Parameters:
 *   minAge      - The minimum age of actors to display (inclusive).
 *   maxAge      - The maximum age of actors to display (inclusive).
 *   yearToActor - AVLTree mapping actor birth years to Actor objects.
 *
 * Returns:
 *   void
 *
 * Error Handling:
 *   - Ensures that minAge is less than or equal to maxAge.
 *   - If an invalid age range is provided, an error message is displayed and the function exits.
 *   - If no actors exist within the specified range, the AVLTree method determines the output.
 *----------------------------------------------------------------------------*/
void displayActorsByAgeRange(int minAge, int maxAge, AVLTree<Actor*>& yearToActor) {
    int currentYear = 2025; // Define the reference year

    // Convert the age range to birth years.
    int latestBirthYear = currentYear - minAge;   // Actors must be born on or before this year.
    int earliestBirthYear = currentYear - maxAge;   // Actors must be born on or after this year.

    // Display actors whose birth years fall within the calculated range.
    yearToActor.DisplayActors(earliestBirthYear, latestBirthYear);
}

/*----------------------------------------------------------------------------
 * Function: displayRecentMovies
 * Author: Tevel1
 *
 * Description:
 *   Displays movies that have been released in the last three years.
 *   The function calls an AVLTree method to fetch and display movies categorized
 *   by their release years.
 *
 * Parameters:
 *   yearToMovie - AVLTree mapping movie release years to Movie objects.
 *
 * Returns:
 *   void
 *
 * Error Handling:
 *   - If the AVLTree is empty or contains no movies for the last three years,
 *     a clear and professional message is displayed.
 *----------------------------------------------------------------------------*/
void displayRecentMovies(AVLTree<Movie*>& yearToMovie) {
    int currentYear = 2025; // Define the reference year

    // Check if the AVLTree is empty, indicating no available movies.
    if (yearToMovie.isEmpty()) {
        cout << "No movies found for the last three years.\n";
    } else {
        // Call the AVLTree method to display movies released in the last three years.
        yearToMovie.DisplayMovies();
    }
}

/*----------------------------------------------------------------------------
 * Function: displayMoviesByActor
 * Author: Brayden
 *
 * Description:
 *   Displays all movies that a specific actor has starred in, sorted alphabetically.
 *   The function retrieves and iterates through the actor's movie list, displaying
 *   each movie's title along with its release year.
 *
 * Parameters:
 *   actor - Pointer to the Actor object whose movies are to be displayed.
 *
 * Returns:
 *   void
 *
 * Error Handling:
 *   - If the actor pointer is null, an error message is displayed and the function exits.
 *   - If the actor has no associated movies, a message is displayed instead of an empty list.
 *----------------------------------------------------------------------------*/
void displayMoviesByActor(Actor* actor) {
    // Validate the actor pointer.
    if (actor == nullptr) {
        cerr << "Error: Null pointer provided for actor. Cannot display movies.\n";
        return;
    }

    // Retrieve the list of movies associated with the actor.
    List<Movie*>* movies = &actor->movies;

    // Display header for the movie list.
    cout << "\n============================================\n";
    cout << "Movies Starring: " << actor->getName() << "\n";
    cout << "--------------------------------------------\n";

    // Check if the actor has any movies.
    if (movies->getLength() == 0) {
        cout << "No movies found for this actor.\n";
    } else {
        // Sort the movie list alphabetically.
        movies->sortByAlphabetical();

        // Iterate through the sorted movie list and display each movie's details.
        for (int i = 0; i < movies->getLength(); i++) {
            Movie* currentMovie = movies->get(i);
            cout << "- " << currentMovie->getName() << " (" 
                 << currentMovie->getYear() << ")\n";
        }
    }

    // Display footer for the movie list.
    cout << "============================================\n\n";
}

/*----------------------------------------------------------------------------
 * Function: displayActorsKnownByHelper
 * Author: Brayden
 *
 * Description:
 *   Identifies and adds actors known by a specific target actor through shared movies.
 *   The function scans each movie that the target actor has appeared in and iterates 
 *   through the movie's cast list to find actors who have worked with them. Any actor
 *   found (except the target and original actor) is added to the known actors list.
 *
 * Parameters:
 *   targetActor   - Pointer to the Actor object whose known connections are being identified.
 *   knownActors   - Reference to a dynamic array that stores the list of actors known by the target actor.
 *   originalActor - Pointer to the original Actor object initiating the search (to prevent self-references).
 *
 * Returns:
 *   void
 *
 * Error Handling:
 *   - If targetActor is nullptr, an error message is displayed, and the function exits.
 *   - If targetActor has no associated movies, a message is displayed, and no actors are added.
 *----------------------------------------------------------------------------*/
void displayActorsKnownByHelper(Actor* targetActor, DynamicArray<Actor*>& knownActors, Actor* originalActor) {
    // Validate the target actor pointer.
    if (targetActor == nullptr) {
        cerr << "Error: Null pointer provided for target actor. Cannot retrieve known actors.\n";
        return;
    }

    // Retrieve the list of movies associated with the target actor.
    List<Movie*>* movies = &targetActor->movies;

    // Check if the target actor has any associated movies.
    if (movies->isEmpty()) {
        cout << "No movies associated with " << targetActor->getName() << ". No known actors found.\n";
        return;
    }

    // Iterate through each movie in which the target actor has appeared.
    for (int i = 0; i < movies->getLength(); i++) {
        Movie* currentMovie = movies->get(i);

        // Iterate through each actor in the current movie's cast.
        for (int j = 0; j < currentMovie->cast.getLength(); j++) {
            Actor* knownActor = currentMovie->cast.get(j);

            // Exclude the target actor and the original actor to avoid self-references.
            if (knownActor != targetActor && knownActor != originalActor) {
                knownActors.add(knownActor);
            }
        }
    }
}

/*----------------------------------------------------------------------------
 * Function: displayActorsKnownBy
 * Author: Brayden
 *
 * Description:
 *   Displays all actors directly and indirectly known by a specific target actor.
 *   First, the function gathers direct connections (actors who co-starred with 
 *   the target actor). Then, for each direct connection, their known actors are 
 *   added as indirect connections. The final list of known actors is displayed 
 *   in a structured format along with the total count.
 *
 * Parameters:
 *   targetActor - Pointer to the Actor object whose network of known actors is to be displayed.
 *
 * Returns:
 *   void
 *
 * Error Handling:
 *   - If targetActor is nullptr, an error message is displayed, and the function exits.
 *   - If no known actors are found, a message is displayed instead of an empty list.
 *----------------------------------------------------------------------------*/
void displayActorsKnownBy(Actor* targetActor) {
    // Validate the target actor pointer.
    if (targetActor == nullptr) {
        cerr << "Error: Null pointer provided for target actor. Cannot display known actors.\n";
        return;
    }

    // Create a dynamic array to store direct connections (actors directly known by the target).
    DynamicArray<Actor*> directActors;
    displayActorsKnownByHelper(targetActor, directActors, targetActor);

    // Create a dynamic array to store indirect connections (actors known by direct connections).
    DynamicArray<Actor*> indirectActors;
    for (int i = 0; i < directActors.getSize(); i++) {
        displayActorsKnownByHelper(directActors.get(i), indirectActors, targetActor);
    }

    // Combine indirect connections into the direct actors array.
    for (int i = 0; i < indirectActors.getSize(); i++) {
        directActors.add(indirectActors.get(i));
    }

    // Display the complete list of known actors.
    cout << "\n============================================\n";
    cout << "Actors known by " << targetActor->getName() << ":\n";
    cout << "--------------------------------------------\n";

    // Check if any known actors were found.
    if (directActors.getSize() == 0) {
        cout << "No known actors found for " << targetActor->getName() << ".\n";
    } else {
        // Iterate through the combined list and display each actor's name.
        for (int i = 0; i < directActors.getSize(); i++) {
            cout << directActors.get(i)->getName() << "\n";
        }
    }

    // Display footer with the total count of known actors.
    cout << "--------------------------------------------\n";
    cout << "Total Known Actors: " << directActors.getSize() << "\n";
    cout << "============================================\n\n";
}

/*----------------------------------------------------------------------------
 * Function: displayActorsByMovie
 * Author: Tevel
 *
 * Description:
 *   Displays all actors who starred in a specific movie, sorted alphabetically.
 *   The function retrieves and iterates through the movie's cast list, displaying
 *   each actor's name.
 *
 * Parameters:
 *   movie - Pointer to the Movie object whose cast (actors) are to be displayed.
 *
 * Returns:
 *   void
 *
 * Error Handling:
 *   - If the movie pointer is null, an error message is displayed and the function exits.
 *   - If the movie has no associated actors, a message is displayed instead of an empty list.
 *----------------------------------------------------------------------------*/
void displayActorsByMovie(Movie* movie) {
    // Validate the movie pointer.
    if (movie == nullptr) {
        cerr << "Error: Null pointer provided for movie. Cannot display actors.\n";
        return;
    }

    // Display the header for the actor list.
    cout << "\n============================================\n";
    cout << "Actors in \"" << movie->getName() << "\"\n";
    cout << "--------------------------------------------\n";

    // Check if the movie's cast list is empty.
    if (movie->cast.getLength() == 0) {
        cout << "No actors found for this movie.\n";
    } else {
        // Sort the cast list alphabetically before displaying.
        movie->cast.sortByAlphabetical();
        // Iterate through the sorted cast list and display each actor's name.
        for (int i = 0; i < movie->cast.getLength(); i++) {
            cout << "[" << i+1 << "] " << movie->cast.get(i)->getName() << "\n";
        }
    }

    // Display the footer for the actor list.
    cout << "============================================\n\n";
}

/*----------------------------------------------------------------------------
 * Function: roundToOneDecimal
 * Author: Brayden
 *
 * Description:
 *   Rounds a double value to one decimal place and converts it to a string.
 *   If the value is 0, the function returns "No Rating".
 *
 * Parameters:
 *   value - The double value to be rounded and converted.
 *
 * Returns:
 *   string - The rounded value as a string with one decimal place, or "No Rating" if the value is 0.
 *----------------------------------------------------------------------------*/
string roundToOneDecimal(double value) {
    // Return "No Rating" if the provided value is zero.
    if (value == 0) {
        return "No Rating";
    }
    
    // Create an output string stream to format the value.
    ostringstream oss;
    // Round the value to one decimal place using a standard rounding technique.
    oss << fixed << setprecision(1) << floor(value * 10 + 0.5) / 10;
    return oss.str();
}

/*----------------------------------------------------------------------------
 * Function: setActorRating
 * Author: Brayden
 *
 * Description:
 *   Sets the rating for a specific actor while ensuring input validity.
 *   This function validates the rating range (0 to 5) and ensures that the
 *   actor pointer is valid before calling the addRating method.
 *   After updating, a confirmation message is displayed with the new rating.
 *
 * Parameters:
 *   actor  - Pointer to the Actor object whose rating is to be updated.
 *   rating - The new rating to be added (expected between 0.0 and 5.0).
 *
 * Returns:
 *   void
 *
 * Error Handling:
 *   - If actor is a null pointer, an error message is displayed, and the function exits.
 *   - If rating is out of the valid range (0-5), an error message is displayed.
 *----------------------------------------------------------------------------*/
void setActorRating(Actor* actor, double rating) {
    // Validate the actor pointer to ensure it is not null.
    if (actor == nullptr) {
        cerr << "Error: Null Actor pointer provided. Cannot update rating.\n";
        return;
    }

    // Validate that the provided rating is within the acceptable range.
    if (rating < 0.0 || rating > 5.0) {
        cerr << "Error: Invalid rating value (" << rating
             << "). Please enter a value between 0 and 5.\n";
        return;
    }

    // Update the actor's rating using the addRating method.
    actor->addRating(rating);

    // Display a confirmation message showing the updated average rating and total number of ratings.
    cout << "\n--------------------------------------------\n";
    cout << "Rating successfully updated for Actor: " << actor->getName() << "\n";
    cout << "New Average Rating: " << roundToOneDecimal(actor->getRating())
         << " (Total Ratings: " << actor->getNumRatings() << ")\n";
    cout << "--------------------------------------------\n\n";
}

/*----------------------------------------------------------------------------
 * Function: setMovieRating
 * Author: Brayden
 *
 * Description:
 *   Sets the rating for a specific movie while ensuring input validity.
 *   This function validates the rating range (0 to 5) and ensures that the
 *   movie pointer is valid before calling the addRating method.
 *   After updating, a confirmation message is displayed with the new rating.
 *
 * Parameters:
 *   movie  - Pointer to the Movie object whose rating is to be updated.
 *   rating - The new rating to be added (expected between 0.0 and 5.0).
 *
 * Returns:
 *   void
 *
 * Error Handling:
 *   - If movie is a null pointer, an error message is displayed, and the function exits.
 *   - If rating is out of the valid range (0-5), the function ensures a valid input.
 *----------------------------------------------------------------------------*/
void setMovieRating(Movie* movie, double rating) {
    // Validate the movie pointer to ensure it is not null.
    if (movie == nullptr) {
        cerr << "Error: Null Movie pointer provided. Cannot update rating.\n";
        return;
    }

    // Validate that the provided rating is within the acceptable range.
    if (rating < 0.0 || rating > 5.0) {
        cerr << "Error: Invalid rating value (" << rating
             << "). Please enter a value between 0 and 5.\n";
        return;
    }

    // Update the movie's rating using the addRating method.
    movie->addRating(rating);

    // Display a confirmation message showing the updated average rating and total number of ratings.
    cout << "\n============================================\n";
    cout << "Successfully updated rating for Movie: " << movie->getName()
         << " (" << movie->getYear() << ")\n";
    cout << "New Average Rating: " << roundToOneDecimal(movie->getRating())
         << " (Total Ratings: " << movie->getNumRatings() << ")\n";
    cout << "============================================\n\n";
}

/*----------------------------------------------------------------------------
 * Function: recommendActorsByRating
 * Author: Tevel
 *
 * Description:
 *   Recommends the top 5 highest-rated actors from the provided dynamic array.
 *   The function sorts the actors by their ratings in descending order and then
 *   displays the top 5 actors along with their ratings. Each rating is formatted to
 *   one decimal place.
 *
 * Parameters:
 *   allActors - Dynamic array containing all Actor objects.
 *
 * Returns:
 *   void
 *
 * Error Handling:
 *   Assumes that the allActors array contains at least 5 actors. If fewer than 5
 *   actors are present, the behavior depends on the dynamic array's implementation.
 *----------------------------------------------------------------------------*/
void recommendActorsByRating(DynamicArray<Actor*>& allActors) {
    // Check if there are any actors to recommend
    if (allActors.getSize() == 0) {
        cout << "\n============================================\n";
        cout << "        No actors available for recommendation.\n";
        cout << "============================================\n\n";
        return;
    }

    // Sort the actors in descending order by rating
    allActors.sortByRating();

    // Determine how many actors to display (up to 5)
    int numActorsToDisplay = (allActors.getSize() < 5) ? allActors.getSize() : 5;

    // Display header for the recommendation list
    cout << "\n============================================\n";
    cout << "        Top " << numActorsToDisplay << " Highest Rated Actors\n";
    cout << "============================================\n";
    cout << "Rating    " << " | Actor Name\n";
    cout << "--------------------------------------------\n";

    // Loop through the top actors and display their rating and name
    for (int i = 0; i < numActorsToDisplay; i++) {
        Actor* currentActor = allActors.get(i);
        // Format the rating to one decimal place if available; otherwise, display "No Rating"
        string formattedRating = (currentActor->getRating() > 0)
                                     ? roundToOneDecimal(currentActor->getRating())
                                     : "No Rating";

        cout << setw(9) << left << formattedRating << "  | "
             << setw(30) << left << currentActor->getName() << "\n";
    }

    cout << "============================================\n\n";
}

/*----------------------------------------------------------------------------
 * Function: recommendMoviesByRating
 * Author: Tevel
 *
 * Description:
 *   Recommends the top 5 highest-rated movies from the provided dynamic array.
 *   The function sorts the movies by their ratings in descending order and then
 *   displays the top 5 movies. For each movie, the following details are shown:
 *     - Movie rating (formatted to one decimal place).
 *     - Cast average rating (formatted to one decimal place).
 *     - Movie name along with its release year.
 *
 * Parameters:
 *   allMovies - Dynamic array containing all Movie objects.
 *
 * Returns:
 *   void
 *
 * Error Handling:
 *   Assumes that the allMovies array contains at least 5 movies. If fewer than 5
 *   movies are present, the behavior depends on the dynamic array's implementation.
 *----------------------------------------------------------------------------*/
void recommendMoviesByRating(DynamicArray<Movie*>& allMovies) {
    // Check if there are any movies to recommend
    if (allMovies.getSize() == 0) {
        cout << "\n============================================\n";
        cout << "        No movies available for recommendation.\n";
        cout << "============================================\n\n";
        return;
    }

    // Sort the movies in descending order by rating
    allMovies.sortByRating();

    // Determine how many movies to display (up to 5)
    int numMoviesToDisplay = (allMovies.getSize() < 5) ? allMovies.getSize() : 5;

    // Display header for the recommendation list
    cout << "\n==================================================================\n";
    cout << "           Top " << numMoviesToDisplay << " Highest Rated Movies\n";
    cout << "==================================================================\n";
    cout << setw(10) << "Rating" << " | " 
         << setw(13) << "Cast Rating" << " | "
         << "Movie Name (Release Year)\n";
    cout << "------------------------------------------------------------------\n";

    // Loop through the top movies and display their details
    for (int i = 0; i < numMoviesToDisplay; i++) {
        Movie* currentMovie = allMovies.get(i);

        // Format the movie's rating and cast average rating to one decimal place if available;
        // otherwise, display "No Rating"
        string formattedMovieRating = (currentMovie->getRating() > 0)
                                          ? roundToOneDecimal(currentMovie->getRating())
                                          : "No Rating";
        string formattedCastRating = (currentMovie->castAverageRating() > 0)
                                         ? roundToOneDecimal(currentMovie->castAverageRating())
                                         : "No Rating";

        cout << setw(9) << left << formattedMovieRating << "  | "
             << setw(12) << left << formattedCastRating << "  | "
             << setw(30) << left << currentMovie->getName() << " ("
             << currentMovie->getYear() << ")\n";
    }

    cout << "==================================================================\n\n";
}