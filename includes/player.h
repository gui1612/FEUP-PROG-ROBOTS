#pragma once

#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief Data structure to store a Person (stores his position, score and his position)
 *
 */
struct Player {
    bool alive;
    int score;
    vector<int> pos;
};