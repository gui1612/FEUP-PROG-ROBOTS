#pragma once

#include "entities.h"

#include <algorithm>

using namespace std;

// Type aliases
using xval = int;
using yval = int;
using ID = int;


/**
 * @brief
 *
 * @param maze
 */
void playGame(Maze &maze);


/**
 * @brief Parses the maze info into the Player, Robot and Maze structs
 *
 * @param maze Maze to be read from
 * @param player Player instance
 * @param robot Robot instance
 */
void initializeGame(Maze maze, Player &player, Robot &robot);


/**
 * @brief Checks if the player is trying to move to a position out of bounds
 *
 * @param pos Position the player is trying to move
 * @param maze Maze instance
 * @return returns `true` if out of bounds, `false` if not
 */
bool outOfBounds(const vector<int> &pos,const Maze &maze);


/**
 * @brief Checks if the player input is a valid move
 *
 * @param key player input key
 * @return `true` if the input is valid and `false` if not
 *
 * @note Before using this function you should make sure that
 * `key` is of type `char`
 *
 * @note Valid moves: {'q', 'Q', 'w', 'W', 'e', 'E', 'a', 'A',
 * 's', 'S', 'd', 'D', 'z', 'Z', 'x', 'X', 'c', 'C'}
 */
bool validMove(char key);