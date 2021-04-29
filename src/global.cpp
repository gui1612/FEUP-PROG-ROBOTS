// Includes
#include "global.h"
#include "entities.h"

// Namespace
using namespace std;


void clearBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


void clearScreen() {
    cout << string(100, '\n');
}


void waitForConfirmation() {
    char emptyInput = (char) cin.get();     // Waits until the user presses enter
    if (emptyInput != '\n' && !cin.eof())
        clearBuffer();                      // Clears the buffer if the input was not `EOF`
}


void warnUser(const string &warningType) {
    clearScreen();                              // Clears the screen before the warning is displayed
    if (warningType == "menu") {                // Warning layout for menu
        cout << "That is not a valid input (Options: 0, 1, 2)\n"
             << "Press ENTER to return to the main menu..." << endl;
    } else if (warningType == "fileIO") {       // Warning layout for file input/output
        cout << "That is not a valid input (Options: 1, 2, ..., 99)" << endl;
    } else if (warningType == "game") {         // Warning layout for file input/output
        cout << "That is not a valid input (Options: Q, W, E, A, S, D, Z, X, C)" << endl;
    } else if (warningType == "game-move") {    // Warning layout for game movement
        cout << "Invalid move: There's something in the way!" << endl;
    } else if (warningType == "name") {         // Warning layout for the player name
        cout << "Invalid input: maximum name length of 15!" << endl;
    } else if (warningType == "leaderboard") {  // Warning layout for the leaderboard
        cout << "Invalid input: That leaderboard doesn't exist yet!" << endl;
    } else if (warningType == "mazefile") {  // Warning layout for the mazefile
        cout << "Invalid mazefile: The file format is not correct!" << endl;
    } else {                                    // Fall case
        cout << "That is not a valid input\n"
             << "Press ENTER to return to the main menu..." << endl;
    }
    waitForConfirmation();                  // Waits for the user to press something
    clearScreen();                          // Clears the screen
}


void sleepFor(unsigned int sec) {
    this_thread::sleep_for(chrono::seconds(sec));
}