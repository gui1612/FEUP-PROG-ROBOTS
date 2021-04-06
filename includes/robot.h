#pragma once

#include <vector>
#include <iostream>
#include "robot.h"
#include "player.h"

using namespace std;

using ID = int;

/**
 * @brief Data structure to store a Person (stores his position, score and his position)
 *
 */
struct Robot {
        bool alive;
        ID id;
        vector<int> coordinates;
};

void updateRobot(Robot &robot, const Maze &maze, const Player player);