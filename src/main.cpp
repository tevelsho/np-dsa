/*
DATA STRUCTURES & ALGORITHMS ASSIGNMENT
    CODERS: Tevel Sho (S10258591B) & Brayden Saga (S10258659C)
    GROUP: 

`main.cpp` contains ...
*/

#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>


using namespace std;


void readActorsCSV() {
    // Open the file
    ifstream iFile("actors.csv");

    // Check if the file is opened
    if (!iFile.is_open()) {
        cout << "Error: Could not open file!" << endl;
        return;
    }

    string line;

    // Skip the header line
    getline(iFile, line);

    // Read and parse each line
    while (getline(iFile, line)) {
        stringstream ss(line);
        string id, name, birth;

        // Read values separated by commas
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, birth, ',');

        // Remove quotes from the name

        // Output the values
    }

    iFile.close();
}


void displayMenu() {
    cout << "\n=============================================\n";
    cout << "            🎬 Movie Application Menu               \n";
    cout << "=============================================\n";
    cout << " [1]  ➤ Add a New Actor\n";
    cout << " [2]  ➤ Add a New Movie\n";
    cout << " [3]  ➤ Assign an Actor to a Movie\n";
    cout << " [4]  ➤ Update Actor Details\n";
    cout << " [5]  ➤ Update Movie Details\n";
    cout << " [6]  ➤ Display Actors by Age Range\n";
    cout << " [7]  ➤ Show Movies from the Last 3 Years\n";
    cout << " [8]  ➤ List Movies an Actor Starred In\n";
    cout << " [9]  ➤ List Actors in a Specific Movie\n";
    cout << " [10] ➤ Find All Actors an Actor Knows\n";
    cout << " [11] ➤ Exit Application\n";
    cout << "=============================================\n";
    cout << "Please select an option by entering the number: ";
}

int main() {
    int option;

    displayMenu();
    cin >> option;

    // Input validation
    while (cin.fail() || option < 1 || option > 11) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        cout << "Invalid Option! Please enter a number between 1 and 11: ";
        cin >> option;
    }

    switch (option) {
        case 1:
            cout << "Option 1: Add a new actor selected.\n";
            
            // Call function to add a new actor
            break;

        case 2:


        default:
            cout << "Invalid option. Please try again.\n";
    }
}