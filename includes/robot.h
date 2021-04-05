#pragma once

#include <vector>
#include <iostream>

using namespace std;

using ID = int;

/**
 * @brief Data structure to store a Person (stores his position, score and his position)
 *
 */
struct Robot {
        bool alive;
        int ID;
        vector<int> pos;
};
