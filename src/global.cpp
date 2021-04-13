#include "global.h"
#include "entities.h"

using namespace std;


void clearBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


void clearScreen() {
    cout << string(100, '\n');
}


void waitForConfirmation() {
    char emptyInput = (char) cin.get();     // Waits until the user press enter
    if (emptyInput != '\n' && !cin.eof())   // Checks if the user inserted anything or just pressed enter as expected
        clearBuffer();                      // Clears the buffer if the input was not `EOF`
}


bool validInputType() {
    bool validInput = cin.good() && cin.peek() == '\n';     // Tracks if the user input is valid
    return validInput;
}


void warnUser(const string &warningType) {
    clearScreen();                              // clears the screen before the warning is displayed
    if (warningType == "menu") {                // warning layout for menu
        cout << "That is not a valid input (Options: 0, 1, 2)\n"
             << "Press ENTER to return to the main menu..." << endl;
    } else if (warningType == "fileIO") {       // warning layout for file input/output
        cout << "That is not a valid input (Options: 1, 2, ..., 99)" << endl;
    } else if (warningType == "game") {         // warning layout for file input/output
        cout << "That is not a valid input (Options: Q, W, E, A, S, D, Z, X, C)" << endl;
    } else if (warningType == "game-move") {    // warning layout for game movement
        cout << "Invalid move: There's something in the way!" << endl;
    } else if (warningType == "name") {         // warning layout for the player name
        cout << "Invalid input: maximum name length of 15!" << endl;
    } else if (warningType == "leaderboard") {  // warning layout for the leaderboard
        cout << "Invalid input: That leaderboard doesn't exist yet!" << endl;
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