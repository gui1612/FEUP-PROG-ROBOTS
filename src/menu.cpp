#include "../includes/global.h"
#include "../includes/menu.h"

void menu() {
    short confirm = 1;                       // Leaving confirmation (initialized at a value different of 0 not to leave the loop)
    do {
        short menuPick;                      // Menu choice

        const string banner = R"(
                                 _____       ____      ____       ____      _______                    _____                  __  __     ______
                                |  __ \     / __ \    |  _ \     / __ \    |__   __|                  / ____|       /\       |  \/  |   |  ____|
                                | |__) |   | |  | |   | |_) |   | |  | |      | |                    | |  __       /  \      | \  / |   | |__
                                |  _  /    | |  | |   |  _ <    | |  | |      | |                    | | |_ |     / /\ \     | |\/| |   |  __|
                                | | \ \    | |__| |   | |_) |   | |__| |      | |                    | |__| |    / ____ \    | |  | |   | |____
                                |_|  \_\    \____/    |____/     \____/       |_|                     \_____|   /_/    \_\   |_|  |_|   |______|
        )";

        // Banner and menu options display
        cout << banner << endl;
        cout << "(2) Play\n"
             << "(1) Rules\n"
             << "(0) Exit" << endl;

        bool validInput = getInput<short>(menuPick);    // gets an input and if it is successfully (`validInput` -> `true`) writes it on `menuPick` (if not clears the buffer)

        if (validInput) {               // Valid input type
            clearBuffer();                    // Clears the buffer from the last `cin` call
            menuChoice(menuPick, confirm);
        } else {                              // If the input is invalid the screen is cleared and options are displayed again
            clearScreen();
            warnUser();                       // Warns the user about wrong input
            waitForConfirmation();
        }
    } while (confirm != 0 && !cin.eof());
}


void menuChoice(short choice, short &confirm) {
    switch (choice) {
        case 0: {               // Exit
            clearScreen();
            cout << "Are you sure you want to exit (0 to confirm)?\n";
            bool validInput = getInput<short>(confirm);    // gets an input and if it is successfully (`validInput` -> `true`) writes it on `confirm` (if not clears the buffer)
            if (!validInput) {    // Invalid input
                confirm = 1;            // Resets `confirm` for cases in which user inputs a problematic value
                clearScreen();          // Clears the screen
                warnUser();             // Warns the user about invalid input
                waitForConfirmation();  // Waits for user input
            } else {                    // Valid input
                clearBuffer();          // Clears the buffer
            }
            clearScreen();              // clears the screen before the next menu display or the end of the game
            break;
        }
        case 1: {               // Rules
            clearScreen();          // Clears the screen
            displayRules();         // Displays the rules
            waitForConfirmation();  // Waits for user input
            break;
        }
        case 2: {               // Play
            cout << "This is a stub for the main game" << endl;    //TODO: Insert the actual game
            break;
        }
        default: {              // The input was of type `int`, but not a valid option
            clearScreen();
            warnUser();             // Warns the user about wrong input
            waitForConfirmation();
        }
    }
}


void warnUser() {
    cout << "That is not a valid input (Options: 0, 1, 2)\n"       // Warns the user of invalid input
         << "Press ENTER to return to the main menu..."<< endl;
}


void displayRules() {
    cout << R"(
    --------------------------------------------------------------------------------------------------------------------
    |                                                          Instructions                                            |
    |                                                                                                                  |
    |   > MOVEMENT                                                                                                     |
    |                                                                                                                  |
    |               -------------------                               -----------------------------------              |
    |               |  Q  |  W  |  E  |                               |  UP LEFT  |   UP   |  UP RIGHT  |              |
    |               |-----------------|                               |---------------------------------|              |
    |               |  A  |  S  |  D  |                   =>          |    LEFT   |  STAY  |    RIGHT   |              |
    |               |-----------------|                               |---------------------------------|              |
    |               |  Z  |  X  |  C  |                               | DOWN LEFT |  DOWN  | DOWN RIGHT |              |
    |               -------------------                               -----------------------------------              |
    |                                                                                                                  |
    |                                                                                                                  |
    |   > NOTATION                                                    |   > MAZE (*)                                   |
    |                                                                 |                                                |
    |    H/h -> Player (alive/dead)                                   |    High voltage fences/posts                   |
    |    R/r -> Robot (alive/dead)                                    |                                                |
    |    r   -> Several Robots collision                              |                                                |
    |    *   -> Fence/Post                                            |                                                |
    |                                                                                                                  |
    |   > PLAYER (H/h)                                                |   > ROBOTS (R/r)                               |
    |                                                                 |                                                |
    |    Overview                                                     |    Death                                       |
    |     Robots will try to destroy the player                       |     Robots will die in contact with            |
    |                                                                 |     walls/eachother                            |
    |                                                                 |                                                |
    |    Movement                                                     |    Movement                                    |
    |     The player can move in any direction to an adjacent cell    |     For each player's cell movement the robot  |
    |     (horizontally, vertically, or diagonally)                   |     also moves one cell in the direction of    |
    |                                                                 |     the shortest path                          |
    |                                                                                                                  |
    |                                                                                                                  |
    |   > WIN CONDITION                                               |   > GAME OVER                                  |
    |                                                                 |                                                |
    |     All robots are destroyed                                    |    Player touches maze or robot(s)             |
    |                                                                                                                  |
    |                                                                                                                  |
    |                                                                                                                  |
    |   Press ENTER to return to the main menu...                                                                      |
    |                                                                                                                  |
    --------------------------------------------------------------------------------------------------------------------
    )";
}