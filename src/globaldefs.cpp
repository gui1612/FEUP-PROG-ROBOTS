#include "globaldefs.h"
#include <optional>


void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void clearScreen() {
    std::cout << std::string(100, '\n');
}


void waitForConfirmation() {
    char emptyInput = (char) std::cin.get();     // Waits until the user presses enter
    if (emptyInput != '\n' && !std::cin.eof())
        clearBuffer();                      // Clears the buffer if the input was not `EOF`
}


void warnUser(const std::string &warningType) {
    clearScreen();                              // Clears the screen before the warning is displayed
    if (warningType == "menu") {                // Warning layout for menu
        std::cout << "That is not a valid input (Options: 0, 1, 2)\n"
             << "Press ENTER to return to the main menu..." << std::endl;
    } else if (warningType == "fileIO") {       // Warning layout for file input/output
        std::cout << "That is not a valid input (Options: 1, 2, ..., 99)" << std::endl;
    } else if (warningType == "game") {         // Warning layout for file input/output
        std::cout << "That is not a valid input (Options: Q, W, E, A, S, D, Z, X, C)" << std::endl;
    } else if (warningType == "game-move") {    // Warning layout for game movement
        std::cout << "Invalid move: There's something in the way!" << std::endl;
    } else if (warningType == "name") {         // Warning layout for the player name
        std::cout << "Invalid input: maximum name length of 15!" << std::endl;
    } else if (warningType == "leaderboard") {  // Warning layout for the leaderboard
        std::cout << "Invalid input: That leaderboard doesn't exist yet!" << std::endl;
    } else if (warningType == "mazefile") {     // Warning layout for the mazefile
        std::cout << "Invalid mazefile: The file format is not correct!" << std::endl;
    } else {                                    // Fall case
        std::cout << "That is not a valid input\n"
             << "Press ENTER to return to the main menu..." << std::endl;
    }
    waitForConfirmation();                  // Waits for the user to press something
    clearScreen();                          // Clears the screen
}


void sleepFor(unsigned int sec) {
    std::this_thread::sleep_for(std::chrono::seconds(sec));
}