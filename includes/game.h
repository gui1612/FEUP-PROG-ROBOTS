#pragma once

#include "../includes/maze.h"
#include "../includes/player.h"
#include "../includes/robot.h"

using namespace std;

struct Game {
    Maze maze;
    Player player;
    Robot robot;
};


/**
 * @brief Starts a game based on the maze passed
 *
 * @param maze Maze instance
 */
void playGame(Maze &maze);
