//
// Created by ANTONIO on 5/9/2021.
//

#include "robot.h"

void Robot::updateAllRobots(int &player, int &maze){
    for (int i = 0; i < maze.robotVec.size(); i++) {

        Robot currRobot = maze.robotVec.at(i);
        Point lastPos = currRobot.coordinates;

        if (!currRobot.alive) {continue;};

        Point newPos = bestMove(currRobot, player, maze);

        char charInPos = maze.gameBoard.at(newPos.y).at(newPos.x);

        if (charInPos == 'R' || charInPos == 'r') {                 // Robot gets stuck
            maze.robotVec.at(i).alive = false;                      // First robot dies
            maze.aliveRobots--;                                     // Updates aliveRobots
            maze.robotVec.at(i).coordinates = newPos;               // Coordinates update
            for (int j = 0; j < maze.robotVec.size(); j++) {
                Robot secRobot = maze.robotVec.at(j);
                if (currRobot == secRobot) {continue;};

                if (secRobot.coordinates == newPos) {               // If there's a robot collision, kills the other robot
                    maze.robotVec.at(j).alive = false;              // Second robot dies
                    if (secRobot.alive) {maze.aliveRobots--;};      // Updates aliveRobots
                }
                mazeReplace(maze, lastPos, ' ');
                mazeReplace(maze, newPos, 'r');
            }

        } else if (charInPos == '*') {                              // Robot moves to electric fence
            maze.robotVec.at(i).alive = false;                      // Robot dies
            maze.aliveRobots--;                                     // Updates aliveRobots
            mazeReplace(maze, lastPos, ' ');
            mazeReplace(maze, newPos, 'r');
        } else if (charInPos == 'H') {                              // Player gets caught by robot
            player.alive = false;                                   // Player dies
            mazeReplace(maze, lastPos, 'R');
            mazeReplace(maze, newPos, 'h');
            break;
        } else {                                                    // Regular robot move
            maze.robotVec.at(i).coordinates = newPos;               // Updates robot position
            mazeReplace(maze, lastPos, ' ');
            mazeReplace(maze, newPos, 'R');
        }
    }
}


int Robot::bestMove(const Robot &robot, const Player &player, const Maze &maze) {
    xval x = robot.coordinates.x;
    yval y = robot.coordinates.y;

    // Possible move positions for the Robot
    vector<Point> moveVec = {{x-1, y-1}, {x, y-1}, {x+1, y-1},
                             {x-1, y},             {x+1, y},
                             {x-1, y+1}, {x, y+1}, {x+1, y+1}};

    double minDist = numeric_limits<double>::max();
    Point bestMove;                                                         // Variable to store the optimal position to move
    for (int i = 0; i < moveVec.size(); i++) {
        if (!outOfBounds(moveVec.at(i), maze)) {                            // The position is inside the maze bounds
            double dist = pointDist(moveVec.at(i), player.coordinates);     // Distance between that move option and the player
            if (dist < minDist) {                                           // If that move is the best until the moment
                minDist = dist;
                bestMove = moveVec.at(i);
            }
        }
    }
    return bestMove;
}


double pointDist(Point p1, Point p2) {
    return sqrt(pow(p2.y - p1.y, 2) + pow(p2.x - p1.x, 2));
}

