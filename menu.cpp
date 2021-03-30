#include "menu.h"
#include <iostream>
#include <string>

//TODO: Possibly convert this into a class
int menu() {

    //Work-around: we should use a char
    string menuPick;

    cout << "1)Rules\n"
         << "2)Play\n"
         << "0)Exit" << endl;

    cin >> menuPick;

    //TODO: We should make a loop out of this
    if (menuPick == "1") {
        clearScreen();
        displayRules();
        cin.clear();
        cin.ignore(1);
        cin.get();
        clearScreen();
        menu();
        // TODO: GAME
    } else if (menuPick == "2") {
        clearScreen();
        menu();
    } else if (menuPick == "0") {
        cout << "Are you sure you want to exit (0 to confirm)?\n";
        cin >> menuPick;
        if (menuPick != "0") {
            clearScreen();
            menu();
        } else {
            return 0;
        }
    } else {
        clearScreen();
        cout << "That's not a valid input!\nPress ENTER to return to the main menu..." << endl;
        cin.clear();
        cin.ignore(1);
        cin.get();
        menu();
    }
    return 0;
}


void clearScreen() {
    // cout << "\033[2J\033[1;1H";     //escape key to clear screen and position cursor at the beginning of it
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