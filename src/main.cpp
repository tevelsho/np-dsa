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

using namespace std;

// Maximum number of admin accounts
const int MAX_ADMINS = 1;

// Admin credentials (hardcoded, stored in array)
char adminUsername[MAX_ADMINS][20] = {"admin"};
char adminPassword[MAX_ADMINS][20] = {"password"};

// Function prototypes
bool authenticateAdmin();
void adminMenu();
void userMenu();
void readActorsCSV();
void readCSV(string filename);
bool addNewActor(List<Actor>& actorList); 
bool addNewMovie(List<Movie>& movieList); 
bool addActorToMovie(List<Actor> actorList, List<Movie> movieList, Dictionary<int, List<Actor>>& movieToActors); 
void updateActorDetails(List<Actor>& actorList); 
void updateMovieDetails(List<Movie>& movieList); 
void displayActorsByAgeRange(); 
void displayRecentMovies(); 
void displayMoviesByActor(); 
void displayActorsByMovie(); 
void displayActorsKnownBy(); 
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
    List<Actor> actorList;
    List<Movie> movieList;

    Dictionary<int, List<Actor>> movieToActor;

    Dictionary<int, Actor*> actorIdToActorMap;
    Dictionary<string, int> actorNameToIdMap;

    Dictionary<int, Movie*> movieIdToMovieMap;
    Dictionary<string, int> movieNameToIdMap;

    char isAdmin[5];
    cout << "Are you an administrator? (yes/no): ";
    cin >> isAdmin;
    
    // Convert input to lowercase
    for (int i = 0; isAdmin[i] != '\0'; i++) {
        if (isAdmin[i] >= 'A' && isAdmin[i] <= 'Z') {
            isAdmin[i] += ('a' - 'A'); 
        }
    }

    if (isAdmin[0] == 'y' && isAdmin[1] == 'e' && isAdmin[2] == 's' && isAdmin[3] == '\0') {
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
            adminMenu();
        } else {
            cout << "Failed all attempts! You will no be logged in as a normal user.\n";
            userMenu();
        }
    } else {
        cout << "Welcome, User!\n";
        userMenu();
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
}

/*----------------------------------------------------------------------------
Displays the admin menu and handles admin operations.

@return void

Description:
    - Allows the admin to perform various operations such as adding actors, 
      adding movies, updating details, and exiting the application.
    - Continues to prompt the admin until they choose to exit.
----------------------------------------------------------------------------*/
void adminMenu() {
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

        switch (option) {
            case 0:
                cout << " Thank you for visiting Silver Village! Hope to see you next time!";
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice! Try again.\n"; 

        }

    } while (option != 5);
}


/*----------------------------------------------------------------------------
Displays the user menu and handles user operations.

@return void

Description:
    - Allows the user to perform various actions such as 
      viewing actors and movies based on specific criteria.
    - Continues to prompt the user until they choose to exit.
-----------------------------------------------------------------------------*/
void userMenu() {
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
            case 0:
                cout << " Thank you for visiting Silver Village! Hope to see you next time!";
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice! Try again.\n"; 

        }

    } while (option != 5);
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
void readCSV(string fileName) {
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

            // Map the ID to the Actor object
            actorIdToActorMap.put(id, actor);

            // Map the Name to the ID
            actorNameToIdMap.put(name, id);
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
            cout << "Person ID: " << personID << ", Movie ID: " << movieID << endl;
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

            // Output the parsed data
            cout << "ID: " << id << ", Title: " << title << ", Year: " << year << endl;
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
bool addNewActor(List<Actor>& actorList) {
    int id, birth;
    string name;

    // Prompt user for id, name, and birth for new actor
    cout << "Enter new actor's ID: ";
    cin >> id;

    cout << "Enter new actor's name: ";
    getline(cin, name);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter new actor's year of birth: ";
    cin >> birth;

    // Create a new actor object and add it to the list
    Actor newActor(id, name, birth);
    return actorList.add(newActor);
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
bool addNewMovie(List<Movie>& movieList) {
    int id, year;
    string movie;

    // Prompt user for id, movie, and year for new movie
    cout << "Enter new movie's ID: ";
    cin >> id;

    cout << "Enter new movie's name: ";
    getline(cin, movie);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter new movie's release year: ";
    cin >> year;

    // Create a new movie object and add it to the list
    Movie newMovie(id, movie, year);
    return movieList.add(newMovie);
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
bool addActorToMovie(List<Actor> actorList, List<Movie> movieList, Dictionary<int, List<Actor>>& movieToActors) {
    int actorID, movieID;

    // Prompt user to select an actor by ID
    cout << "Enter the actor's ID: ";
    cin >> actorID;

    // Search for actor in actor list
    Actor* selectedActor = nullptr;
    for (int i = 0; i < actorList.getLength(); i++) {
        if (actorList.get(i).getID() == actorID) {
            selectedActor = &actorList.get(i);
            break;
        }
    }

    // Actor not founded
    if (selectedActor == nullptr) {
        cout << "Error: Actor not found. Please ensure the ID is correct.\n";
        return false;
    }

    // Prompt user to select a movie by ID
    cout << "Enter the movie's ID: ";
    cin >> movieID;

    // Search for movie in movie list
    Movie* selectedMovie = nullptr;
    for (int i = 0; i < movieList.getLength(); i ++) {
        if (movieList.get(i).getID() == movieID) {
            selectedMovie = &movieList.get(i);
            break;
        }
    }
    
    // Movie not founded
    if (selectedMovie == nullptr) {
        cout << "Error: Movie not found. Please ensure the ID is correct.\n";
        return false;
    }

    // Check if movie has already an associated list of actors
    if (!movieToActors.contains(movieID)) {
        // Create a new list of actors associated to the movie
        List<Actor> newActorList;
        newActorList.add(*selectedActor);
        movieToActors.put(movieID, newActorList);
    } else {
        // Add the actor to the existing list of actors for the movie
        movieToActors.get(movieID).add(*selectedActor);
    }

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
void updateActorDetails(List<Actor>& actorList) {
    int actorID;

    // Prompt user for actor ID to update actor's details
    cout << "Enter the actor's ID to update: ";
    cin >> actorID;

    // Search actor by ID
    Actor* actorToUpdate = nullptr;
    for (int i = 0; i < actorList.getLength(); i++) {
        if (actorList.get(i).getID() == actorID) {
        actorToUpdate = &actorList.get(i);
        break;
    }

    // Actor not founded
    if (actorToUpdate == nullptr) {
        cout << "Error: Actor not found. Please ensure the ID is correct.\n";
        return;
    }

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
        actorToUpdate->setName(newName);
    }
    if (newYear != -1) {
        actorToUpdate->setYearOfBirth(newYear);
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
void updateMovieDetails(List<Movie>& movieList) {
    int movieID;

    // Prompt user for movie ID to update movie's details
    cout << "Enter the movie's ID to update: ";
    cin >> movieID;

    // Search movie by ID
    Movie* movieToUpdate = nullptr;
    for (int i = 0; i < movieList.getLength(); ++i) {
        if (movieList.get(i).getID() == movieID) {
            movieToUpdate = &movieList.get(i);
            break;
        }
    }

    // Movie not founded
    if (movieToUpdate == nullptr) {
        cout << "Movie with ID " << movieID << " not found.\n";
        return;
    }

    // Display the current details of the movie
    cout << "Current Details:\n";
    cout << "ID: " << movieToUpdate->getID() << "\n";
    cout << "Title: " << movieToUpdate->getTitle() << "\n";
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
        movieToUpdate->setTitle(newTitle);
    }
    if (newYear != -1) {
        movieToUpdate->setYear(newYear);
    }

    cout << "Movie details updated successfully!\n";
}