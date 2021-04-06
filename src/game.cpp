#include "../includes/game.h"
#include "../includes/player.h"
#include "../includes/robot.h"


void playGame(Maze &maze) {
    Player player;
    Robot robot;
    vector<int> robotIDS;

    char key;

    initializeGame(maze, player, robot);

    do{
        cout << "hi" << endl;
        drawMaze(maze);

        cout << "Where do you wish to move to?\t\t";
        cin >> key;

        updatePlayer(key, player, maze);
        updateRobot(robot, maze, player);
        if (outOfBounds(player.coordinates, maze)){
            cout << "Watch out you are leaving the play area! Input a valid move!" << endl;
            continue;
        } else if (!player.alive){
            cout << "you died!" << endl;
            break;
        } else {
            playerDraw(player,maze);
        }
        //playerDraw(player, maze);
    }while (player.alive || robotIDS.size() != 0);
}


void initializeGame(Maze maze, Player &player, Robot &robot) {

    vector<int> entPos(2);
    vector<int> robotIDS;
    int idSelector = 1;

    for (yval y = 0; y < maze.rows; y++) {
        for (xval x = 0; x < maze.columns; x++) {
            switch (maze.coordinates.at(y).at(x)) {
                case ('H'):
                    cout << "found the player!" << endl;
                    entPos.push_back(x);
                    entPos.push_back(y);
                    player.coordinates = entPos;
                    entPos.clear();
                    player.alive = true;
                    break;
                case ('R'):
                    cout << "found a robot!" << endl;
                    entPos.push_back(x);
                    entPos.push_back(y);
                    robot.coordinates = entPos;
                    entPos.clear();
                    robot.alive = true;
                    robot.id = idSelector;
                    robotIDS.push_back(robot.id);
                    idSelector++;
                    break;
                case ('h'):
                    entPos.push_back(x);
                    entPos.push_back(y);
                    player.coordinates = entPos;
                    entPos.clear();
                    player.alive = false;
                    break;
                case ('r'):
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
    unsigned int HEIGHT = maze.rows;
    unsigned int WIDTH = maze.columns;
    int x = pos.at(0), y = pos.at(1);

    if (0< y <HEIGHT && 0 < x < WIDTH)
        return false;
    else
        return true;
}