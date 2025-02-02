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

// Function prototypes (Advanced).
void setActorRating(Actor* actor, double rating);
void setMovieRating(Movie* movie, double rating);  
void recommendMoviesByRating(DynamicArray<Movie*>& allMovies);
void recommendActorsByRating(DynamicArray<Actor*>& allActors);

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

    char isAdmin;

    // Main loop: Continuously prompt the user until they choose to quit.
    while (true) {
        cout << "Are you an administrator? (y/n, q to quit): ";
        cin >> isAdmin;

        if (isAdmin == 'y' || isAdmin == 'Y') {
            // Administrator flow: Allow up to three attempts for authentication.
            bool isAdminAuthenticated = false;
            for (int attempts = 0; attempts < 3; attempts++) {
                if (authenticateAdmin()) {
                    isAdminAuthenticated = true;
                    break;
                } else {
                    cout << "Invalid credentials! Try again (" 
                         << (2 - attempts) << " attempts remaining).\n";
                }
            }

            // Redirect based on authentication result.
            if (isAdminAuthenticated) {
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
        } else if (isAdmin == 'n' || isAdmin == 'N') {
            // Normal user flow.
            cout << "Welcome, User!\n";
            userMenu(actorIdToActorMap, actorNameToIdMap, yearToActor,
                     movieIdToMovieMap, movieNameToIdMap, yearToMovie,
                     allActors, allMovies);
        } else if (isAdmin == 'q' || isAdmin == 'Q') {
            // Quit the application.
            cout << "Thank you for visiting Silver Village! Hope to see you next time!\n";
            break;
        } else {
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

    // Prompt the user to enter their admin username and password.
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;

    // Loop through all stored admin credentials.
    for (int i = 0; i < MAX_ADMINS; i++) {
        bool usernameMatch = true;
        bool passwordMatch = true;

        // Perform a character-by-character comparison of the entered username 
        // with the stored username at index i.
        for (int j = 0; username[j] != '\0' || adminUsername[i][j] != '\0'; j++) {
            if (username[j] != adminUsername[i][j]) {
                usernameMatch = false;
                break;
            }
        }

        // Perform a character-by-character comparison of the entered password 
        // with the stored password at index i.
        for (int j = 0; password[j] != '\0' || adminPassword[i][j] != '\0'; j++) {
            if (password[j] != adminPassword[i][j]) {
                passwordMatch = false;
                break;
            }
        }

        // If both username and password match, return true to grant admin access.
        if (usernameMatch && passwordMatch) {
            return true;
        }
    }
    // If no match is found, return false to deny admin access.
    return false;
}

/*----------------------------------------------------------------------------
 * Function: findActorByName
 * Author: Brayden
 *
 * Description:
 *   Finds an actor by their name. The function first retrieves the actor's ID
 *   from a dictionary mapping actor names to IDs, and then uses that ID to obtain
 *   the corresponding Actor object from another dictionary mapping IDs to Actor pointers.
 *
 * Parameters:
 *   actorNameToIdMap - Dictionary mapping actor names to their corresponding IDs.
 *   actorName        - The name of the actor to search for.
 *   actorIdToActorMap- Dictionary mapping actor IDs to their corresponding Actor objects.
 *
 * Returns:
 *   Actor* - A pointer to the Actor object if found; otherwise, returns nullptr.
 *----------------------------------------------------------------------------*/
Actor* findActorByName(Dictionary<string, int>& actorNameToIdMap, string actorName, Dictionary<int, Actor*>& actorIdToActorMap) {
    // Retrieve the actor's ID using their name.
    int actorID = actorNameToIdMap.get(actorName);
    
    // Return the Actor object corresponding to the retrieved ID.
    return actorIdToActorMap.get(actorID);
}


/*----------------------------------------------------------------------------
 * Function: findMovieByName
 * Author: Brayden
 *
 * Description:
 *   Finds a movie by its name. The function first looks up the movie's ID in a 
 *   dictionary mapping movie names to IDs, and then uses that ID to retrieve the 
 *   corresponding Movie object from another dictionary mapping IDs to Movie pointers.
 *
 * Parameters:
 *   movieNameToIdMap - Dictionary mapping movie names to their corresponding IDs.
 *   movieName        - The name of the movie to search for.
 *   movieIdToMovieMap- Dictionary mapping movie IDs to their corresponding Movie objects.
 *
 * Returns:
 *   Movie* - A pointer to the Movie object if found; otherwise, returns nullptr.
 *----------------------------------------------------------------------------*/
Movie* findMovieByName(Dictionary<string, int>& movieNameToIdMap, string movieName, Dictionary<int, Movie*>& movieIdToMovieMap) {
    // Retrieve the movie's ID using its name.
    int movieID = movieNameToIdMap.get(movieName);
    
    // Return the Movie object corresponding to the retrieved ID.
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
void adminMenu(Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie, DynamicArray<Actor*>& allActors, DynamicArray<Movie*>& allMovies) {
    int option;

    do {
        // Display the admin menu header and options.
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
        
        // Prompt the admin to select an option.
        cout << "Please select an option by entering the number: ";
        cin >> option;

        // Validate the input: check for non-integer input.
        if (cin.fail()) {
            cin.clear(); // Clear the error flag.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input.
            cout << "\nInvalid choice! Please enter a number between 0 and 5.\n";
            continue; 
        }

        // Validate that the option is within the allowed range.
        if (option < 0 || option > 5) {
            cout << "\nInvalid choice! Please enter a number between 0 and 5.\n";
            continue; 
        }

        // Process the selected option.
        switch (option) {
            case 0: {
                // Log out option.
                cout << "Logged out from Admin\n";
                break;
            }
            case 1: {
                // Add a new actor.
                cout << "Adding a new actor...\n";
                int actor_id, actor_birth;
                string actor_name;

                // Prompt for the actor's ID.
                cout << "Enter new actor's ID: ";
                cin >> actor_id;

                // Check for duplicate actor ID.
                if (actorIdToActorMap.contains(actor_id)) {
                    cout << "Error: Actor ID already exists. Please choose a different ID.\n";
                    break;
                }

                // Clear the input buffer.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Prompt for the actor's name.
                cout << "Enter new actor's name: ";
                getline(cin, actor_name);

                // Check for duplicate actor name.
                if (actorNameToIdMap.contains(actor_name)) {
                    cout << "Error: Actor name already exists. Please choose a different name.\n";
                    break;
                }

                // Prompt for the actor's year of birth.
                cout << "Enter new actor's year of birth: ";
                cin >> actor_birth;
                
                // Add the new actor.
                addNewActor(actor_id, actor_birth, actor_name, actorIdToActorMap, actorNameToIdMap, yearToActor, allActors);
                cout << "Actor successfully added!\n";
                break;
            }
            case 2:{
                // Add a new movie.
                cout << "Adding a new movie...\n";
                int movie_id, movie_year;
                string movie_name;

                // Prompt for the movie's ID with input validation.
                cout << "Enter new movie's ID: ";
                while (!(cin >> movie_id)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid number for movie ID: ";
                }

                // Check for duplicate movie ID.
                if (movieIdToMovieMap.contains(movie_id)) {
                    cout << "Error: Movie ID already exists. Please choose a different ID.\n";
                    break;
                }

                // Clear the input buffer before reading a string.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Prompt for the movie's name.
                cout << "Enter new movie's name: ";
                getline(cin, movie_name);

                // Check for duplicate movie name.
                if (movieNameToIdMap.contains(movie_name)) {
                    cout << "Error: Movie name already exists. Please choose a different name.\n";
                    break;
                }

                // Prompt for the movie's release year with input validation.
                cout << "Enter new movie's release year: ";
                while (!(cin >> movie_year)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid number for the release year: ";
                }

                // Attempt to add the new movie.
                if (addNewMovie(movie_id, movie_year, movie_name, movieIdToMovieMap, movieNameToIdMap, yearToMovie, allMovies)) {
                    cout << "Movie successfully added!\n";
                } else {
                    cout << "Failed to add movie due to an error.\n";
                }
                break;
            }
            case 3:{
                // Assign an actor to a movie.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                string actor_name, movie_name;
                // Prompt for the actor's name.
                cout << "Enter the actor's name: ";
                getline(cin, actor_name);

                // Prompt for the movie's name.
                cout << "Enter the movie's name: ";
                getline(cin, movie_name);

                // Retrieve the corresponding Actor and Movie objects.
                Actor* actor = findActorByName(actorNameToIdMap, actor_name, actorIdToActorMap);
                Movie* movie = findMovieByName(movieNameToIdMap, movie_name, movieIdToMovieMap);

                // Check if both actor and movie exist.
                if (actor != nullptr && movie != nullptr) {
                    addActorToMovie(actor, movie);
                    cout << "Success: " << actor_name << " has been successfully assigned to \"" << movie_name << "\".\n";
                } else {
                    cout << "Error: Actor or Movie not found. Please ensure the Name is correct.\n";
                }
                break;
            }
            case 4: {
                // Update actor details.
                string actor_name;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                while (true) {
                    // Prompt for the actor's name to update.
                    cout << "Enter the actor's name to update: ";
                    getline(cin, actor_name);

                    // Validate that the actor's name is not empty.
                    if (actor_name.empty()) {
                        cout << "Error: Actor name cannot be empty. Please try again.\n";
                        continue;
                    }

                    // Retrieve the Actor object based on the provided name.
                    Actor* actorToUpdate = findActorByName(actorNameToIdMap, actor_name, actorIdToActorMap);

                    if (actorToUpdate != nullptr) {
                        // Update actor details if found.
                        updateActorDetails(actorToUpdate, actorNameToIdMap, yearToActor);
                        break;  // Exit loop after successful update.
                    } else {
                        cout << "Error: Actor not found. Please ensure the Name is correct.\n";
                    }
                }
                break;
            }
            case 5: {
                // Update movie details.
                string movie_name;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                while (true) {
                    // Prompt for the movie's name to update.
                    cout << "Enter the movie's name to update: ";
                    getline(cin, movie_name);

                    // Validate that the movie's name is not empty.
                    if (movie_name.empty()) {
                        cout << "Error: Movie name cannot be empty. Please try again.\n";
                        continue;
                    }

                    // Retrieve the Movie object based on the provided name.
                    Movie* movieToUpdate = findMovieByName(movieNameToIdMap, movie_name, movieIdToMovieMap);

                    if (movieToUpdate != nullptr) {
                        // Update movie details if found.
                        updateMovieDetails(movieToUpdate, movieNameToIdMap, yearToMovie);
                        break;  // Exit loop after successful update.
                    } else {
                        cout << "Error: Movie not found. Please ensure the Name is correct.\n";
                    }
                }
                break;
            }
            default:
                // This default case should not be reached due to prior validation.
                cout << "Error: Unexpected error occurred.\n";
                break;
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
 *     - "movies.csv": Contains movie information with columns (id, title, year).
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
void readCSV(string fileName, Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Actor*>& yearToActor, AVLTree<Movie*>& yearToMovie, DynamicArray<Actor*>& allActors, DynamicArray<Movie*>& allMovies) {
    // File pointer and file path construction.
    fstream fin;
    string filePath = "./data/" + fileName;

    // Open the CSV file in input mode.
    fin.open(filePath, ios::in);

    // Check if the file was opened successfully.
    if (!fin.is_open()) {
        cout << "Error: Could not open file!" << endl;
        return;
    }

    string line, word;

    // Skip the header line in the CSV file.
    getline(fin, line);

    // Process the file based on its name.
    if (fileName == "actors.csv") {
        // Process "actors.csv": Each line contains actor id, name, and birth year.
        while (getline(fin, line)) {
            stringstream s(line);

            // Temporary variables for parsing.
            string name, temp;
            int id, birth;

            // Parse actor ID.
            getline(s, temp, ',');
            id = stoi(temp);

            // Parse actor name, assuming it is enclosed in double quotes.
            getline(s, temp, '"');
            getline(s, name, '"');
            s.ignore(1); // Skip the comma after the closing quote.

            // Parse actor birth year.
            getline(s, temp, ','); 
            birth = stoi(temp);  

            // Add the new actor to the data structures.
            addNewActor(id, birth, name, actorIdToActorMap, actorNameToIdMap, yearToActor, allActors);
        }

        fin.close();

    } else if (fileName == "cast.csv") {
        // Process "cast.csv": Each line contains a person ID and a movie ID.
        while (getline(fin, line)) {
            stringstream s(line);

            // Temporary variables for parsing.
            string temp;
            int personID, movieID;

            // Parse person ID.
            getline(s, temp, ',');
            personID = stoi(temp);

            // Parse movie ID.
            getline(s, temp, ','); 
            movieID = stoi(temp);  

            // Retrieve the corresponding actor and movie objects.
            Actor* actor = actorIdToActorMap.get(personID);
            Movie* movie = movieIdToMovieMap.get(movieID);

            // Assign the actor to the movie.
            addActorToMovie(actor, movie);
        }

        fin.close();

    } else if (fileName == "movies.csv") {
        // Process "movies.csv": Each line contains movie id, title, and release year.
        while (getline(fin, line)) {
            stringstream s(line);

            // Temporary variables for parsing.
            string title, temp;
            int id, year;

            // Parse movie ID.
            getline(s, temp, ',');
            id = stoi(temp);

            // Parse movie title, assuming it is enclosed in double quotes.
            getline(s, temp, '"');
            getline(s, title, '"');
            s.ignore(1); // Skip the comma after the closing quote.

            // Parse movie release year.
            getline(s, temp, ','); 
            year = stoi(temp);  

            // Add the new movie to the data structures.
            addNewMovie(id, year, title, movieIdToMovieMap, movieNameToIdMap, yearToMovie, allMovies);
        }

        fin.close();
    } else {
        // Handle unsupported file names.
        cout << "Error: Unsupported file name \"" << fileName << "\". Please provide a valid file name." << endl;
        fin.close();
    }
}

/*----------------------------------------------------------------------------
 * Function: addNewActor
 * Author: Brayden
 *
 * Description:
 *   Adds a new actor to the system and updates the relevant data structures.
 *   This function creates a new Actor object using the provided id, name, and
 *   birth year, then integrates it into several data structures for efficient
 *   lookup and iteration.
 *
 * Parameters:
 *   id                - A unique integer identifier for the actor.
 *   birth             - The year of birth of the actor.
 *   name              - The full name of the actor.
 *   actorIdToActorMap - Dictionary mapping actor IDs to their corresponding Actor objects.
 *   actorNameToIdMap  - Dictionary mapping actor names to their corresponding IDs.
 *   yearToActor       - AVLTree mapping actor birth years to Actor objects.
 *   allActors         - Dynamic array containing all Actor objects.
 *
 * Returns:
 *   bool - Returns true if the actor is successfully added to all data structures.
 *
 * Error Handling:
 *   Assumes that the provided id and name are unique. No additional input
 *   validation is performed for negative birth years or empty names.
 *----------------------------------------------------------------------------*/
bool addNewActor(int id, int birth, string name, Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, DynamicArray<Actor*>& allActors) {
    // Create a new actor object.
    Actor* actor = new Actor(id, name, birth);

    // Map the ID to the Actor pointer.
    actorIdToActorMap.add(id, actor);

    // Map the actor's name to their ID.
    actorNameToIdMap.add(name, id);

    // Add the actor to the dynamic array for iteration.
    allActors.add(actor);

    // Insert the actor into the AVL tree using the birth year as the key.
    yearToActor.insertItem(birth, actor);

    return true;
}

/*----------------------------------------------------------------------------
 * Function: addNewMovie
 * Author: Tevel
 *
 * Description:
 *   Adds a new movie to the system and updates the relevant data structures.
 *   This function creates a new Movie object using the provided id, name, and
 *   release year, and then integrates it into several data structures for
 *   efficient lookup and iteration.
 *
 * Parameters:
 *   id                - A unique integer identifier for the movie.
 *   year              - The release year of the movie.
 *   name              - The name or title of the movie.
 *   movieIdToMovieMap - Dictionary mapping movie IDs to their corresponding Movie objects.
 *   movieNameToIdMap  - Dictionary mapping movie names to their corresponding IDs.
 *   yearToMovie       - AVLTree mapping movie release years to Movie objects.
 *   allMovies         - Dynamic array containing all Movie objects.
 *
 * Returns:
 *   bool - Returns true if the movie is successfully added to all data structures;
 *          otherwise, returns false.
 *
 * Error Handling:
 *   Assumes that the provided id and name are unique. Input parameters are not further
 *   validated (e.g., for an invalid release year or empty name). Memory allocation and
 *   insertion operations are wrapped in try-catch blocks to handle exceptions.
 *----------------------------------------------------------------------------*/
bool addNewMovie(int id, int year, string name, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie, DynamicArray<Movie*>& allMovies) {
    // Attempt to create a new movie object.
    Movie* movie = nullptr;
    try {
        movie = new Movie(id, name, year);
    } catch (const std::exception &e) {
        cerr << "Error: Unable to allocate memory for new movie. " << e.what() << "\n";
        return false;
    }
    
    // Add the movie to all the data structures with error handling.
    try {
        // Map the ID to the Movie pointer.
        movieIdToMovieMap.add(id, movie);

        // Map the movie's title to its ID.
        movieNameToIdMap.add(name, id);

        // Add the movie to the dynamic array for iteration.
        allMovies.add(movie);

        // Insert the movie into the AVL tree using the release year as the key.
        yearToMovie.insertItem(year, movie);
    } catch (const std::exception &e) {
        cerr << "Error adding new movie: " << e.what() << "\n";
        // Clean up allocated memory if any operation fails.
        delete movie;
        return false;
    }
    
    return true;
}

/*----------------------------------------------------------------------------
 * Function: addActorToMovie
 * Author: Brayden
 *
 * Description:
 *   Assigns an actor to a specific movie and establishes a bidirectional relationship.
 *   This function updates the Actor object by adding the Movie to its list of associated
 *   movies, and it updates the Movie object by adding the Actor to its list of associated
 *   actors.
 *
 * Parameters:
 *   actor - Pointer to the Actor object to be assigned to the movie.
 *   movie - Pointer to the Movie object to which the actor will be assigned.
 *
 * Returns:
 *   bool - Returns true if the actor is successfully added to the movie and vice versa.
 *
 * Error Handling:
 *   This function assumes that both the actor and movie pointers are valid and properly
 *   initialized. It also assumes that the addMovie and addActor methods internally handle
 *   duplicate entries.
 *----------------------------------------------------------------------------*/
bool addActorToMovie(Actor* actor, Movie* movie) {
    // Add the movie to the actor's list.
    actor->addMovie(movie);
    // Add the actor to the movie's list.
    movie->addActor(actor);
    // Return true indicating a successful bidirectional association.
    return true;
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
    // Check if the actor pointer is valid.
    if (actorToUpdate == nullptr) {
        cerr << "Error: Null pointer provided for actor update.\n";
        return;
    }

    // Display the current details of the actor.
    cout << "\nCurrent Details:\n";
    cout << "--------------------------------\n";
    cout << "ID: " << actorToUpdate->getID() << "\n";
    cout << "Name: " << actorToUpdate->getName() << "\n";
    cout << "Year of Birth: " << actorToUpdate->getYearOfBirth() << "\n";
    cout << "--------------------------------\n";

    // Prompt the user for new details.
    string newName;
    int newYear;

    cout << "Enter the new name (leave blank to keep current): ";
    getline(cin, newName);

    cout << "Enter the new year of birth (enter -1 to keep current): ";
    cin >> newYear;
    
    // Validate the input for the new year.
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: Invalid input for year of birth. No changes were made.\n";
        return;
    }

    // Flag to indicate if any changes have been made.
    bool updated = false;

    // Update the actor's name if a new, non-empty name is provided.
    if (!newName.empty() && newName != actorToUpdate->getName()) {
        try {
            // Remove the current name mapping.
            actorNameToIdMap.remove(actorToUpdate->getName());
            // Update the actor's name.
            actorToUpdate->setName(newName);
            // Add the new name mapping.
            actorNameToIdMap.add(newName, actorToUpdate->getID());
            updated = true;
        } catch (const exception& e) {
            cerr << "Error updating actor name: " << e.what() << "\n";
        }
    }
    
    // Update the actor's year of birth if a new value is provided.
    if (newYear != -1 && newYear != actorToUpdate->getYearOfBirth()) {
        try {
            // Remove the actor from the AVL tree using the current birth year.
            yearToActor.removeItem(actorToUpdate->getYearOfBirth(), actorToUpdate);
            // Update the actor's birth year.
            actorToUpdate->setYearOfBirth(newYear);
            // Insert the actor back into the AVL tree with the new birth year.
            yearToActor.insertItem(newYear, actorToUpdate);
            updated = true;
        } catch (const exception& e) {
            cerr << "Error updating actor year of birth: " << e.what() << "\n";
        }
    }

    // Display updated details if any changes were made; otherwise, indicate no changes.
    if (updated) {
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
    // Check if the provided movie pointer is valid.
    if (movieToUpdate == nullptr) {
        cerr << "Error: Null pointer provided for movie update.\n";
        return;
    }

    // Display the current details of the movie.
    cout << "\nCurrent Details:\n";
    cout << "--------------------------------\n";
    cout << "ID: " << movieToUpdate->getID() << "\n";
    cout << "Title: " << movieToUpdate->getName() << "\n";
    cout << "Year of Release: " << movieToUpdate->getYear() << "\n";
    cout << "--------------------------------\n";

    // Prompt the user for new details.
    string newTitle;
    int newYear;

    cout << "Enter the new title (leave blank to keep current): ";
    getline(cin, newTitle);

    cout << "Enter the new year of release (enter -1 to keep current): ";
    cin >> newYear;
    
    // Check if the input for the year was valid.
    if (cin.fail()) {
        cin.clear();  // Clear the error state.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input.
        cout << "Error: Invalid input for year of release. No changes were made.\n";
        return;
    }

    // Flag to track if any updates have been made.
    bool updated = false;

    // If a new title was entered and it differs from the current title, update it.
    if (!newTitle.empty() && newTitle != movieToUpdate->getName()) {
        try {
            // Remove the old title mapping.
            movieNameToIdMap.remove(movieToUpdate->getName());
            // Update the movie's title.
            movieToUpdate->setName(newTitle);
            // Add the new title mapping.
            movieNameToIdMap.add(newTitle, movieToUpdate->getID());
            updated = true;
        } catch (const exception& e) {
            cerr << "Error updating title: " << e.what() << "\n";
        }
    }
    // If a new year is provided and it differs from the current year, update it.
    if (newYear != -1 && newYear != movieToUpdate->getYear()) {
        try {
            // Remove the movie from the AVL tree using the current year as the key.
            yearToMovie.removeItem(movieToUpdate->getYear(), movieToUpdate);
            // Update the movie's release year.
            movieToUpdate->setYear(newYear);
            // Insert the movie into the AVL tree with the new release year.
            yearToMovie.insertItem(newYear, movieToUpdate);
            updated = true;
        } catch (const exception& e) {
            cerr << "Error updating year of release: " << e.what() << "\n";
        }
    }

    // Display a success message with updated details if any changes were made.
    if (updated) {
        cout << "\nMovie details updated successfully!\n";
        cout << "--------------------------------\n";
        cout << "Updated Details:\n";
        cout << "ID: " << movieToUpdate->getID() << "\n";
        cout << "Title: " << movieToUpdate->getName() << "\n";
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
void userMenu(Dictionary<int, Actor*>& actorIdToActorMap, Dictionary<string, int>& actorNameToIdMap, AVLTree<Actor*>& yearToActor, Dictionary<int, Movie*>& movieIdToMovieMap, Dictionary<string, int>& movieNameToIdMap, AVLTree<Movie*>& yearToMovie, DynamicArray<Actor*>& allActors, DynamicArray<Movie*>& allMovies) {
    int option;

    do {
        // Display the user menu header and options.
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
        
        // Process the user's menu selection.
        switch (option) {
            case 0: {
                // Log out the user.
                cout << "Logged out from User\n";
                break;
            }
            case 1: {
                // Option 1: Display actors by age range.
                int x, y;
                cout << "Enter the age range (x, y): ";
                cin >> x >> y;
                displayActorsByAgeRange(x, y, yearToActor);
                break;
            }
            case 2: {
                // Option 2: Show movies from the last 3 years.
                displayRecentMovies(yearToMovie);
                break;
            }
            case 3: {
                // Option 3: List movies an actor starred in (alphabetically).
                string actor_name;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear leftover newline.
                cout << "Enter the actor's name: ";
                getline(cin, actor_name);
                Actor* actor = findActorByName(actorNameToIdMap, actor_name, actorIdToActorMap);
                if (actor != nullptr) {
                    displayMoviesByActor(actor);
                } else {
                    cout << "Actor not found.\n";
                }
                break;
            }
            case 4: {
                // Option 4: List actors in a specific movie (alphabetically).
                string movie_name;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear leftover newline.
                cout << "Enter the movie's name: ";
                getline(cin, movie_name);
                Movie* movie = findMovieByName(movieNameToIdMap, movie_name, movieIdToMovieMap);
                if (movie != nullptr) {
                    displayActorsByMovie(movie);
                } else {
                    cout << "Movie not found.\n";
                }
                break;
            }
            case 5: {
                // Option 5: Find all actors an actor knows.
                string actor_name;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear leftover newline.
                cout << "Enter the actor's name: ";
                getline(cin, actor_name);
                Actor* actor = findActorByName(actorNameToIdMap, actor_name, actorIdToActorMap);
                if (actor != nullptr) {
                    displayActorsKnownBy(actor);
                } else {
                    cout << "Actor not found.\n";
                }
                break;
            }
            case 6: {
                // Option 6: Rate an actor.
                string actor_name;
                double rating;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear leftover newline.
                cout << "Enter the actor's name: ";
                getline(cin, actor_name);
                Actor* actor = findActorByName(actorNameToIdMap, actor_name, actorIdToActorMap);
                if (actor == nullptr) {
                    cout << "Actor not found.\n";
                    break;
                }
                // Prompt for rating with validation.
                while (true) {
                    cout << "Actor's current rating: " << roundToOneDecimal(actor->getRating()) << endl;
                    cout << "Enter a rating (e.g., 1.5, 4.9): ";
                    cin >> rating;
                    if (cin.fail() || rating < 0 || rating > 5) {
                        cin.clear(); // Clear the error flag.
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input.
                        cout << "Invalid input. Please enter a number between 1 and 5." << endl;
                    } else {
                        break; // Valid rating entered.
                    }
                }
                setActorRating(actor, rating);
                break;
            }
            case 7: {
                // Option 7: Rate a movie.
                string movie_name;
                double rating;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear leftover newline.
                cout << "Enter the movie's name: ";
                getline(cin, movie_name);
                Movie* movie = findMovieByName(movieNameToIdMap, movie_name, movieIdToMovieMap);
                if (movie == nullptr) {
                    cout << "Movie not found.\n";
                    break;
                }
                // Prompt for rating with validation.
                while (true) {
                    cout << "Movie's current rating: " << roundToOneDecimal(movie->getRating()) << endl;
                    cout << "Enter a rating (e.g., 1.5, 4.9): ";
                    cin >> rating;
                    if (cin.fail() || rating < 0 || rating > 5) {
                        cin.clear(); // Clear the error flag.
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input.
                        cout << "Invalid input. Please enter a number between 1 and 5." << endl;
                    } else {
                        break; // Valid rating entered.
                    }
                }
                setMovieRating(movie, rating);
                break;
            }
            case 8: {
                // Option 8: Recommend movies by rating.
                recommendMoviesByRating(allMovies);
                break;
            }
            case 9: {
                // Option 9: Recommend actors by rating.
                recommendActorsByRating(allActors);
                break;
            }
            default:
                // Handle any unexpected input.
                cout << "Invalid choice! Try again.\n";
        }

    } while (option != 0);
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
 *   x           - The minimum age of actors to display (inclusive).
 *   y           - The maximum age of actors to display (inclusive).
 *   yearToActor - AVLTree mapping actor birth years to Actor objects.
 *
 * Returns:
 *   void
 *
 * Error Handling:
 *   - Ensures that x (min age) is greater than or equal to y (max age).
 *   - If an invalid age range is provided, an error message is displayed and the function exits.
 *   - If no actors exist within the specified range, the AVLTree method determines the output.
 *----------------------------------------------------------------------------*/
void displayActorsByAgeRange(int x, int y, AVLTree<Actor*>& yearToActor) {
    // Validate input: Ensure that the age range is logical
    if (x < y) {
        cerr << "Error: Invalid age range. The minimum age cannot be greater than the maximum age.\n";
        return;
    }

    int currentYear = 2025; // Define the reference year

    // Convert age range to birth years
    int latestBirthYear = currentYear - x;
    int earliestBirthYear = currentYear - y;

    // Display section header
    cout << "\n============================================\n";
    cout << "Actors Aged Between " << y << " and " << x << " Years\n";
    cout << "--------------------------------------------\n";

    // Call the AVLTree method to display actors within the birth year range
    yearToActor.DisplayActors(earliestBirthYear, latestBirthYear);

    // Display section footer
    cout << "============================================\n\n";
}

/*----------------------------------------------------------------------------
 * Function: displayRecentMovies
 * Author: Tevel
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
 *   - If the AVLTree is empty, a message is displayed instead of an empty list.
 *   - Assumes that the AVLTree correctly filters and displays movies from the last three years.
 *----------------------------------------------------------------------------*/
void displayRecentMovies(AVLTree<Movie*>& yearToMovie) {
    int currentYear = 2025; // Define the reference year

    // Display section header
    cout << "\n============================================\n";
    cout << "Movies Released in the Last 3 Years\n";
    cout << "--------------------------------------------\n";

    // Check if there are any movies available
    if (yearToMovie.isEmpty()) {
        cout << "No recent movies found.\n";
    } else {
        // Call the AVLTree method to display movies within the last 3 years
        yearToMovie.DisplayMovies();
    }

    // Display section footer
    cout << "============================================\n\n";
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
    // Validate input parameters
    if (actor == nullptr) {
        cerr << "Error: Null pointer provided for actor. Cannot display movies.\n";
        return;
    }

    List<Movie*>* movies = &actor->movies;

    // Display section header
    cout << "\n============================================\n";
    cout << "Movies Starring: " << actor->getName() << "\n";
    cout << "--------------------------------------------\n";

    // Check if the actor has any movies
    if (movies->getLength() == 0) {
        cout << "No movies found for this actor.\n";
    } else {
        // Iterate over the actor's movie list and display each movie's details
        for (int i = 0; i < movies->getLength(); i++) {
            cout << "- " << movies->get(i)->getName() << " (" 
                 << movies->get(i)->getYear() << ")\n";
        }
    }

    // Display section footer
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
    // Validate input parameters
    if (movie == nullptr) {
        cerr << "Error: Null pointer provided for movie. Cannot display actors.\n";
        return;
    }

    // Display section header
    cout << "\n============================================\n";
    cout << "Actors in \"" << movie->getName() << "\"\n";
    cout << "--------------------------------------------\n";

    // Check if the movie has any associated actors
    if (movie->cast.getLength() == 0) {
        cout << "No actors found for this movie.\n";
    } else {
        // Iterate through the cast list and display each actor's name
        for (int i = 0; i < movie->cast.getLength(); i++) {
            cout << "- " << movie->cast.get(i)->getName() << "\n";
        }
    }

    // Display section footer
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
 *   actors_known  - Reference to a dynamic array that stores the list of actors known by the target actor.
 *   originalActor - Pointer to the original Actor object initiating the search (to prevent self-references).
 *
 * Returns:
 *   void
 *
 * Error Handling:
 *   - If targetActor is nullptr, an error message is displayed, and the function exits.
 *   - If targetActor has no associated movies, a message is displayed, and no actors are added.
 *----------------------------------------------------------------------------*/
void displayActorsKnownByHelper(Actor* targetActor, DynamicArray<Actor*>& actors_known, Actor* originalActor) {
    // Validate input parameters
    if (targetActor == nullptr) {
        cerr << "Error: Null pointer provided for target actor. Cannot retrieve known actors.\n";
        return;
    }

    List<Movie*>* movies = &targetActor->movies;

    if (movies->isEmpty()) {
        cout << "No movies associated with " << targetActor->getName() << ". No known actors found.\n";
        return;
    }

    // Iterate through each movie the target actor has appeared in.
    for (int i = 0; i < movies->getLength(); i++) {
        Movie* movie = movies->get(i);

        // Iterate through each actor in the movie's cast.
        for (int j = 0; j < movie->cast.getLength(); j++) {
            Actor* knownActor = movie->cast.get(j);

            // Ensure the actor is not the target actor or the original actor.
            if (knownActor != targetActor && knownActor != originalActor) {
                actors_known.add(knownActor);
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
    // Validate input parameters
    if (targetActor == nullptr) {
        cerr << "Error: Null pointer provided for target actor. Cannot display known actors.\n";
        return;
    }

    DynamicArray<Actor*> actors_known; // Array for direct connections.

    // Add direct connections.
    displayActorsKnownByHelper(targetActor, actors_known, targetActor);

    DynamicArray<Actor*> actors_known_indirect; // Array for indirect connections.

    // For each direct connection, add their known actors (indirect connections).
    for (int i = 0; i < actors_known.getSize(); i++) {
        displayActorsKnownByHelper(actors_known.get(i), actors_known_indirect, targetActor);
    }

    // Combine direct and indirect connections.
    for (int i = 0; i < actors_known_indirect.getSize(); i++) {
        actors_known.add(actors_known_indirect.get(i));
    }

    // Display the results in a structured format.
    cout << "\n============================================\n";
    cout << "Actors known by " << targetActor->getName() << ":\n";
    cout << "--------------------------------------------\n";

    if (actors_known.getSize() == 0) {
        cout << "No known actors found for " << targetActor->getName() << ".\n";
    } else {
        for (int i = 0; i < actors_known.getSize(); i++) {
            cout << actors_known.get(i)->getName() << "\n";
        }
    }

    cout << "--------------------------------------------\n";
    cout << "Total Known Actors: " << actors_known.getSize() << "\n";
    cout << "============================================\n\n";
}

/*----------------------------------------------------------------------------
 * Function: roundToOneDecimal
 * Author: Brayden
 *
 * Description:
 *   Rounds a double value to one decimal place and converts it to a string.
 *   If the value is 0, the function returns the string "nul".
 *
 * Parameters:
 *   value - The double value to be rounded and converted.
 *
 * Returns:
 *   string - The rounded value as a string with one decimal place, or "nul" if the value is 0.
 *----------------------------------------------------------------------------*/
string roundToOneDecimal(double value) {
    if (value == 0) {
        return "nul";
    }

    ostringstream oss;

    // Round the value to one decimal place and format as a fixed-point string.
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
    // Validate input parameters
    if (actor == nullptr) {
        cerr << "Error: Null Actor pointer provided. Cannot update rating.\n";
        return;
    }

    if (rating < 0.0 || rating > 5.0) {
        cerr << "Error: Invalid rating value (" << rating 
             << "). Please enter a value between 0 and 5.\n";
        return;
    }

    // Update the actor's rating
    actor->addRating(rating);

    // Display confirmation message
    cout << "\n============================================\n";
    cout << "Successfully updated rating for Actor: " << actor->getName() << "\n";
    cout << "New Rating: " << roundToOneDecimal(actor->getRating()) << "⭐  (Total Ratings: " 
         << actor->getNumRatings() << ")\n";
    cout << "============================================\n\n";
};

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
 *   - If rating is out of the valid range (0-5), an error message is displayed.
 *----------------------------------------------------------------------------*/
void setMovieRating(Movie* movie, double rating) {
    // Validate input parameters
    if (movie == nullptr) {
        cerr << "Error: Null Movie pointer provided. Cannot update rating.\n";
        return;
    }

    if (rating < 0.0 || rating > 5.0) {
        cerr << "Error: Invalid rating value (" << rating 
             << "). Please enter a value between 0 and 5.\n";
        return;
    }

    // Update the movie's rating
    movie->addRating(rating);

    // Display confirmation message
    cout << "\n============================================\n";
    cout << "Successfully updated rating for Movie: " << movie->getName() << " (" 
         << movie->getYear() << ")\n";
    cout << "New Rating: " << roundToOneDecimal(movie->getRating()) << "⭐  (Total Ratings: " 
         << movie->getNumRatings() << ")\n";
    cout << "============================================\n\n";
};

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
    // Ensure there are movies available to recommend
    if (allMovies.getSize() == 0) {
        cout << "\n============================================\n";
        cout << "No movies available for recommendation.\n";
        cout << "============================================\n\n";
        return;
    }

    // Sort movies by rating in descending order
    allMovies.sortByRating();

    // Determine the number of movies to display (up to 5)
    int moviesToDisplay = (allMovies.getSize() < 5) ? allMovies.getSize() : 5;

    // Display the header
    cout << "\n============================================\n";
    cout << "        Top " << moviesToDisplay << " Highest Rated Movies\n";
    cout << "--------------------------------------------\n";
    cout << "Rating  | Cast Rating | Movie Name\n";
    cout << "--------------------------------------------\n";

    // Iterate through the top movies and display their details
    for (int i = 0; i < moviesToDisplay; i++) {
        Movie* movie = allMovies.get(i);
        cout << setw(6) << roundToOneDecimal(movie->getRating()) << "⭐  | "
             << setw(6) << roundToOneDecimal(movie->castAverageRating()) << "⭐  | "
             << movie->getName() << " (" << movie->getYear() << ")\n";
    }

    // Display the footer
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
    // Ensure there are actors available to recommend
    if (allActors.getSize() == 0) {
        cout << "\n============================================\n";
        cout << "No actors available for recommendation.\n";
        cout << "============================================\n\n";
        return;
    }

    // Sort actors by rating in descending order
    allActors.sortByRating();

    // Determine the number of actors to display (up to 5)
    int actorsToDisplay = (allActors.getSize() < 5) ? allActors.getSize() : 5;

    // Display the header
    cout << "\n============================================\n";
    cout << "        Top " << actorsToDisplay << " Highest Rated Actors\n";
    cout << "--------------------------------------------\n";
    cout << "Rating  | Actor Name\n";
    cout << "--------------------------------------------\n";

    // Iterate through the top actors and display their details
    for (int i = 0; i < actorsToDisplay; i++) {
        cout << setw(6) << roundToOneDecimal(allActors.get(i)->getRating()) << "⭐  | "
             << allActors.get(i)->getName() << "\n";
    }

    // Display the footer
    cout << "============================================\n\n";
}