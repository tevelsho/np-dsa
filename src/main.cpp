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
void readCSV();
bool addNewActor();

/*----------------------------------------------------------------------------
Main function of the program.

@return int: Returns 0 upon successful execution.

Description:
    - Initializes the program and determines if the user is an admin or a 
      normal user based on input.
    - Redirects user to either adminMenu() or userMenu() accordingly.
----------------------------------------------------------------------------*/
int main() {
    Dictionary<int, Actor*> idToActorDict;
    Dictionary<string, int> nameToActorIdDict;

    Dictionary<int, Movie*> idToMovieDict;
    Dictionary<string, int> nameToMovieIdDict;
    //AVL TREE FOR YEAR TO ACTOR 
    //AVL TREE FOR YEAR TO MOVIE
   
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

Example Usage:
    - readCSV("actors.csv"); // Reads and prints actor information
    - readCSV("cast.csv");   // Reads and prints cast information
    - readCSV("movies.csv"); // Reads and prints movie information
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

            // Output the parsed data
            cout << "ID: " << id << ", Name: " << name << ", Birth Year: " << birth << endl;
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

bool addNewActor() {
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
}