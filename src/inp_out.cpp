#include "../includes/inp_out.h"
#include "../includes/global.h"
#include "../includes/menu.h"

using namespace std;


void mazePick() {
    // File Input loop that ends when user sends "EOF"
    do {
        const unsigned int SLEEP_TIME = 2;             // sleep time if the user decides to leave the maze picker stage
        short levelPick;                               // string type var to store the number of the selected maze

        cout << "Choose a level to play (0 to return to main menu)! " << endl;

        // gets an input and if it is successfully (`validInput` -> `true`) writes it on `levelPick` (if not clears the buffer)
        bool validInput = getInput<short>(levelPick);

        if (validInput) {               // Input of valid type
            clearBuffer();
            if (levelPick == 0) {       // Menu
                clearScreen();                          // Clears the screen
                cout << "Returning to the main menu ..." << flush;
                sleepFor(SLEEP_TIME);                   // Animation to improve UX: waits 2 seconds
                clearScreen();                          // Clears the screen
                menu();                                 // Goes to main menu
            } else {
                /*
                 * `fileNameOrNullopt` will have a string if it is valid or `std::nullopt` if invalid
                 * `fileNameOrNull` will contain a string with a maze filename if `fileNameOrNullopt` has a valid string or else "Null"
                 */
                optional<string> fileNameOrNullopt = getMazeName(levelPick);
                string fileNameOrNull = fileNameOrNullopt.value_or("Null");

                if (fileNameOrNullopt != "Null")        // Valid filename (0 < fileName < 100)
                    mazeOpen(fileNameOrNull);           // Opens maze
                else                                    // Invalid filename ( 0 >= filename or 100 <= filename)
                    warnUser("fileIO");      // Warns the user about invalid filename
            }
        } else if (!cin.eof()) {          // Input of invalid type (not EOF)
            warnUser("fileIO");
        }
    } while (!cin.eof());
}


void mazeOpen(string levelPick){

    ifstream levelFile;                   // input type var to open and read from
    string level, width, height;          // string type var to store the content of levelFile
    int i=1;

    const string PREFIX = "../mazes/";
    string FILE_PATH = PREFIX + levelPick;

    // TODO: method used to chose the user's level seems finicky and ignoring the first line is done in a weird way
    levelFile.open(FILE_PATH, ios::in);
    if (levelFile.is_open()) {
        while (!levelFile.eof()) {
            getline (levelFile, level);
            if (i==1) {
                for (int j = 0; j <= level.length() - 1; j++){
                    if (level[j] == ' ' && i == 1){
                        height = level.substr(0,j);
                        i++;
                    } else if (level[j] == ' ' && i == 2) {
                        width = level.substr(j + 1, level.length() - 1);
                    }
                }
            } else {
                cout << level << endl;
            }
        }
        cout << height << " " << width << endl;
    } else {
        // TODO: make the user able to retry the input (loop)
        cout << "That maze doesn't exist!" << endl;

    }
    levelFile.close();
}


optional<string> getMazeName(short levelChoice) {
    if (levelChoice < 1 || levelChoice > 99) {           // Invalid number for a maze file (there are only 99 mazes max)
        return nullopt;
    } else {                                             // Valid name for a maze
        // Checks if the user input number has one or two digits, turns it into a string, and, if it has one digit fills with a "0" at the left
        string firstPart = (levelChoice < 10) ? "0" + to_string(levelChoice) : to_string(levelChoice);
        string fileName = "MAZE_" + firstPart + ".txt";  // Passes the end format of the maze file to `fileName`
        return fileName;
    }
}