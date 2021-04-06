#include "game.h"
#include "global.h"


void playGame(Maze &maze) {
    Player player;
    Robot robot;
    vector<int> robotIDS;
    Point lastPos;

    // TODO: Implement multiple robots with their respective IDs

    // Getting all the necessary values for the player and robots
    initializeGame(maze, player, robot);

    do {
        char key;                                                   // Initialize the player's input variable

        drawMaze(maze);
        cout << "Where do you wish to move to?" << endl;

        bool validInput = getInput<char>(key);                   // Checks if the input is valid for the type "char"

        if (validInput){                             // Valid input
            if (validMove(key)) {                   // Valid move

                clearBuffer();

                // TODO: Create a function that does both at a time
                updatePlayer(player, key, maze);                   // Updates the player position
                updateRobot(robot, player, maze);                  // Updates the robot position

                if (outOfBounds(player.coordinates, maze)) {           // Checking if the player is inbounds
                    cout << "Watch out you are leaving the play area! Input a valid move!" << endl;
                    continue;
                } else if (!player.alive) {                            // Checking if the player is alive
                    cout << "you died!" << endl;
                    break;
                }
            } else {                                // Invalid input
                clearBuffer();
                warnUser("game");
            }
        } else {                                    // The user's input was not valid (correct type)
            warnUser("game");
        }
    } while (!cin.eof() && (player.alive || robotIDS.size() != 0));
}


void initializeGame(Maze maze, Player &player, Robot &robot) {

    vector<int> entPos(2);       // Stub variable for the position vector of the player/robot
    vector<int> robotIDS;           // Currently not used, but in the future a vector to store all IDs and keep track of living robots
    int idSelector = 1;             // Stub variable fot the future of the robots IDs

    //  Iterating through the maze object in order to find instances of players/robots
    for (yval y = 0; y < maze.rows; y++) {
        for (xval x = 0; x < maze.columns; x++) {
           char currPos = maze.coordinates.at(y).at(x);         // Current maze position
            switch (currPos) {
                case ('H'): case ('h'):                         // Player
                    cout << "found the player!" << endl;        // Debugging tool
                    entPos.push_back(x);                        // Saving x coordinate
                    entPos.push_back(y);                        // Saving y coordinate
                    player.coordinates = entPos;                // Giving the player instance its "coordinates" attribute
                    entPos.clear();                             // Clearing the position vector for use in the next iteration
                    player.alive = isupper(currPos);            // Giving the player instance its "alive" attribute
                    break;
                case ('R'):                                     // Robot (alive)
                    cout << "found a robot!" << endl;           // Debugging tool
                    entPos.push_back(x);                        // Saving x coordinate
                    entPos.push_back(y);                        // Saving y coordinate
                    robot.coordinates = entPos;                 // Giving the robot instance its "coordinates" attribute
                    entPos.clear();                             // Clearing the position vector for use in the next iteration
                    robot.alive = true;                         // Giving the robot instance its "alive" attribute
                    robot.id = idSelector;                      // Giving the robot its ID
                    robotIDS.push_back(robot.id);               // Appending the robot's ID to the 'robotIDS' vector
                    idSelector++;                               // Moving to the next ID
                    break;
                case ('r'):                                     // Robot (dead) - same procedure used in the alive instance, except the instance is dead
                    entPos.push_back(x);
                    entPos.push_back(y);
                    robot.coordinates = entPos;
                    entPos.clear();
                    robot.alive = false;
                    robot.id = idSelector;
                    robotIDS.push_back(robot.id);
                    idSelector++;
                    break;
            }
        }
    }
}


bool outOfBounds(const vector<int> &pos,const Maze &maze){
    const unsigned int HEIGHT = maze.rows, WIDTH = maze.columns;    // Creating height and width variables by looking at the maze instance
    int x = pos.at(0), y = pos.at(1);                           // Getting the x and y position of the player
    return !(0 < y < HEIGHT && 0 < x < WIDTH);                      // Returning true (if inbounds) and false (if out of bounds)
}


bool validMove(char key) {
    vector<char> movements = {'q', 'w', 'e', 'a', 's', 'd', 'z', 'x', 'c'};
    // Checks if `key` is in `movements`
    return find(movements.begin(), movements.end(), static_cast<char>(tolower(key))) != movements.end();
}