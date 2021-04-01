#include "../includes/global.h"
#include "../includes/menu.h"

int menu() {
    float confirm = 1;                       // Leaving confirmation (initialized at a value different of 0 not to leave the loop)
    do {
        bool validInput;                     // Tracks if the user input is valid
        int menuPick;                        // Menu choice

        // Menu options
        cout << "(2) Play\n"
             << "(1) Rules\n"
             << "(0) Exit" << endl;

        cin >> menuPick;
        validInput = trackClearBuffer();     // Tracks if the user input is valid and clears the buffer

        if (validInput) {                    // Valid input type
            menuChoice(menuPick, confirm);
        } else {                             // If the input is invalid the screen is cleared and options are displayed again
            clearScreen();
        }
    } while (confirm != 0 && !cin.eof());
}


void menuChoice(int choice, float &confirm) {
    switch (choice) {
        case 0:         // Exit
            cout << "Are you sure you want to exit (0 to confirm)?\n";
            cin >> confirm;         // Updates confirm to the user input
            clearBuffer();
            clearScreen();
            break;
        case 1:         // Rules
            {
            //string emptyInput;
            clearScreen();          // Clears the screen
            displayRules();         // Displays the rules
            char emptyInput = (char) cin.get();     // Waits until the user press enter
            clearScreen();
            if (emptyInput != '\n')                 // Checks if the user inserted anything or just pressed enter as expected
                clearBuffer();
            break;
            }
        case 2:         // Play
            cout << "This is a stub for the main game" << endl;    //TODO: Insert the actual game
            break;
        default:        // The input was of type `int`, but not a valid option
            clearBuffer();          // Clears the buffer
    }
}


void clearScreen() {
    cout << string(100, '\n');
}


void displayRules() {
    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "|                                                          Instructions                                             |" << endl;
    cout << "|                                                                                                                   |" << endl;
    cout << "|   > MOVEMENT                                                                                                      |" << endl;
    cout << "|                                                                                                                   |" << endl;
    cout << "|               -------------------                               -----------------------------------               |" << endl;
    cout << "|               |  Q  |  W  |  E  |                               |  UP LEFT  |   UP   |  UP RIGHT  |               |" << endl;
    cout << "|               |-----------------|                               |---------------------------------|               |" << endl;
    cout << "|               |  A  |  S  |  D  |                   =>          |    LEFT   |  STAY  |    RIGHT   |               |" << endl;
    cout << "|               |-----------------|                               |---------------------------------|               |" << endl;
    cout << "|               |  Z  |  X  |  C  |                               | DOWN LEFT |  DOWN  | DOWN RIGHT |               |" << endl;
    cout << "|               -------------------                               -----------------------------------               |" << endl;
    cout << "|                                                                                                                   |" << endl;
    cout << "|                                                                                                                   |" << endl;
    cout << "|   > NOTATION                                                    |   > MAZE (*)                                    |" << endl;
    cout << "|                                                                 |                                                 |" << endl;
    cout << "|    H/h -> Player (alive/dead)                                   |    High voltage fences/posts                    |" << endl;
    cout << "|    R/r -> Robot (alive/dead)                                    |                                                 |" << endl;
    cout << "|    r   -> Several Robots collision                              |                                                 |" << endl;
    cout << "|    *   -> Fence/Post                                            |                                                 |" << endl;
    cout << "|                                                                                                                   |" << endl;
    cout << "|   > PLAYER (H/h)                                                |   > ROBOTS (R/r)                                |" << endl;
    cout << "|                                                                 |                                                 |" << endl;
    cout << "|    Overview                                                     |    Death                                        |" << endl;
    cout << "|     Robots will try to destroy the player                       |     Robots will die in contact with             |" << endl;
    cout << "|                                                                 |     walls/eachother                             |" << endl;
    cout << "|                                                                 |                                                 |" << endl;
    cout << "|    Movement                                                     |    Movement                                     |" << endl;
    cout << "|     The player can move in any direction to an adjacent cell    |     For each player's cell movement the robot   |" << endl;
    cout << "|     (horizontally, vertically, or diagonally)                   |     also moves one cell in the direction of     |" << endl;
    cout << "|                                                                 |     the shortest path                           |" << endl;
    cout << "|                                                                                                                   |" << endl;
    cout << "|                                                                                                                   |" << endl;
    cout << "|   > WIN CONDITION                                               |   > GAME OVER                                   |" << endl;
    cout << "|                                                                 |                                                 |" << endl;
    cout << "|     All robots are destroyed                                    |    Player touches maze or robot(s)              |" << endl;
    cout << "|                                                                                                                   |" << endl;
    cout << "|                                                                                                                   |" << endl;
    cout << "|                                                                                                                   |" << endl;
    cout << "|   Press ENTER to return to the main menu...                                                                       |" << endl;
    cout << "|                                                                                                                   |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
}