#include "../includes/global.h"

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


void warnUser(string warningType) {
    clearScreen();                  // clears the screen before the warning is displayed
    if (warningType == "menu") {            // warning layout for menu
        cout << "That is not a valid input (Options: 0, 1, 2)\n"
             << "Press ENTER to return to the main menu..."<< endl;
    } else if (warningType == "fileIO") {   // warning layout for file input/output
        cout << "That is not a valid input (fileNumber: 1, 2, ..., 99)\n"
             << "Press ENTER to return to the main menu..."<< endl;
    } else  {
        cout << "That is not a valid input\n"
             << "Press ENTER to return to the main menu..." << endl;
    }
    waitForConfirmation();          // Waits for the user to press something
    clearScreen();                  //Clears the screen
}

void sleepFor(unsigned int sec) {
    this_thread::sleep_for(chrono::seconds(sec));
}