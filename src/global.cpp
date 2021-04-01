#include "../includes/global.h"

using namespace std;

bool trackClearBuffer() {
    bool result = cin.good();
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return result;
}


void clearBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


void clearScreen() {
    cout << string(100, '\n');
}


void waitForConfirmation() {
    char emptyInput = (char) cin.get();     // Waits until the user press enter
    clearScreen();
    if (emptyInput != '\n')                 // Checks if the user inserted anything or just pressed enter as expected
        clearBuffer();
}


bool validInputType() {
    bool validInput = cin.good() && cin.peek() == '\n';     // Tracks if the user input is valid
    //clearBuffer();                                          // Clears the buffer
    return validInput;
}