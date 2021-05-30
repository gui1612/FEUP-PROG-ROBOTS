// File Includes
#include "Utils.h"
#include "constants.h"


// Lib Includes
#include <cmath>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void clearScreen() {
    std::cout << std::string(CLEAR_SCREEN_NL, '\n');
}


void waitForConfirmation() {
    char emptyInput = (char) std::cin.get();     // Waits until the user presses enter
    if (emptyInput != '\n' && !std::cin.eof())
        clearBuffer();                           // Clears the buffer if the input was not `EOF`
}


void warnUser(const std::string &warningType) {
    if (warningType == "menu") {                // Warning layout for menu
        std::cerr << "That is not a valid input (Options: 0, 1, 2, 3)\n"
             << "Press ENTER to return to the main menu..." << std::endl;
    } else if (warningType == "fileIO") {       // Warning layout for file input/output
        std::cerr << "That is not a valid input!" << std::endl;
    } else if (warningType == "game") {         // Warning layout for file input/output
        std::cerr << "That is not a valid input (Options: Q, W, E, A, S, D, Z, X, C)" << std::endl;
    } else if (warningType == "game-move") {    // Warning layout for game movement
        std::cerr << "Invalid move: There's something in the way!" << std::endl;
    } else if (warningType == "name") {         // Warning layout for the player name
        std::cerr << "Invalid input: maximum name length of 15!" << std::endl;
    } else if (warningType == "leaderboard") {  // Warning layout for the leaderboard
        std::cerr << "Invalid input: That leaderboard doesn't exist yet!" << std::endl;
    } else if (warningType == "mazefile") {     // Warning layout for the mazefile
        std::cerr << "Invalid mazefile: The file format is not correct!" << std::endl;
    } else {                                    // Fall case
        std::cerr << "That is not a valid input\n"
             << "Press ENTER to return to the main menu..." << std::endl;
    }
    waitForConfirmation();                  // Waits for the user to press something
    clearScreen();                          // Clears the screen
}


void sleepFor(unsigned int sec) {
    std::this_thread::sleep_for(std::chrono::seconds(sec));
}


double pointDist(const Point &p1, const Point &p2) {
    return sqrt(std::pow(p2.y - p1.y, 2) + std::pow(p2.x - p1.x, 2));
}


size_t getLastAlphaIdx(const std::string &str) {
    for (const char& chr : str) {
        if (!isspace(chr)) { return chr; }
    }
    /*
    for (size_t i = str.length() - 1; i > 0; i--) {
        if (!isspace(str.at(i))) { return i; }
    }
    */
    /*
     * If the first char of the string is ' ' the string is fully empty and -1 is returned
     * otherwise, it means that the string has one char different from 0 and, in that case returns 0 (first index)
     */
    return str.at(0) == ' ' ? -1 : 0;
}


bool fileExists(const std::string &filename, const std::string &path) {
    std::ifstream infile((path + filename).c_str());
    bool fileExists = infile.good();
    if (fileExists) { infile.close(); }
    return fileExists;
}


int getUTF8Length(const std::string& playerName) {
    int stringLength = 0;
    //return playerName.length() - std::count_if(playerName.begin(), playerName.end(), [](char c)->bool { return (c & 0xC0) == 0x80; });
    for (char chr : playerName) {
        if ((chr & 0b11000000) == 0b10000000) continue;             // Ignoring UTF-8 bytes after the first
        stringLength++;
    }
    return stringLength;
}



int getLinesNumber(const std::string &fileName) {
    int count = 0;                                                 // Stores the count of lines
    std::string line;                                              // Stub variable to store lines
    std::ifstream file(fileName);                                  // Opening input file stream
    if (file.is_open()) {                                          // File exists
        while(!file.eof()) {
            getline(file, line);
            count++;
        }
        file.close();                                               // closing the file
        return count;
    } else {                                                        // Error code for situations where the file doesn't exist
        return -1;
    }
}