#pragma once

#include <vector>
#include <iostream>
#include "maze.h"

using namespace std;

/**
 * @brief Data structure to store a Person (stores his position, score and his position)
 *
 */
struct Player {
    bool alive;
    int score;
    vector<int> coordinates;
};

void updatePlayer(char key, Player &player, const Maze &maze);

void playerDraw(Player player, Maze &maze);