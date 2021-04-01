#include "../includes/global.h"
#include "../includes/menu.h"

int menu() {
    int confirm = 1;                       // Leaving confirmation (initialized at a value different of 0 not to leave the loop)
    do {
        short menuPick;                      // Menu choice

        // Menu options
        cout << "(2) Play\n"
             << "(1) Rules\n"
             << "(0) Exit" << endl;

        cin >> menuPick;

        if (validInputType()) {               // Valid input type
            clearBuffer();                    // Clears the buffer from the last `cin` call
            menuChoice(menuPick, confirm);
        } else {                              // If the input is invalid the screen is cleared and options are displayed again
            clearBuffer();
            clearScreen();
            warnUser();                       // Warns the user about wrong input
            waitForConfirmation();
        }
    } while (confirm != 0 && !cin.eof());
}


void menuChoice(short choice, int &confirm) {
    switch (choice) {
        case 0:         // Exit
            clearScreen();
            cout << "Are you sure you want to exit (0 to confirm)?\n";
            cin >> confirm;             // Updates confirm to the user input
            if (!validInputType()) {    // Invalid input
                confirm = 1;            // Resets `confirm` for cases in which user inputs a problematic value
                clearBuffer();          // Clears the input buffer from the last `cin` call

                clearScreen();          // Clears the screen
                warnUser();             // Warns the user about invalid input
                waitForConfirmation();  // Waits for user input
            } else {            // Valid input
                clearBuffer();          // Clears the buffer
            }
            clearScreen();           // clears the screen before the next menu display or the end of the game
            break;
        case 1:         // Rules
            {
            clearScreen();          // Clears the screen
            displayRules();         // Displays the rules
            waitForConfirmation();  // Waits for the user to press something
            break;
            }
        case 2:         // Play
            cout << "This is a stub for the main game" << endl;    //TODO: Insert the actual game
            break;
        default:        // The input was of type `int`, but not a valid option
            clearScreen();
            warnUser();             // Warns the user about wrong input
            waitForConfirmation();
    }
}


void warnUser() {
    cout << "That is not a valid input (Options: 0, 1, 2)\n"       // Warns the user of invalid input
         << "Press ENTER to return to the main menu..."<< endl;
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