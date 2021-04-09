#pragma once

#include "entities.h"

#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Type aliases
using xval = int;
using yval = int;
using ID = unsigned int;


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
 */
void initializeGame(Maze &maze, Player &player);


/**
 * @brief Checks if the player has won the game
 *
 * @param maze the maze of the current game
 *
 * @return `true` if the player has won and `false` if he hasn't
 */
bool playerWin(const Maze &maze);


/**
 * @brief Checks if the player has lost the game
 *
 * @param player player instance
 *
 * @return `true` if the player has lost and `false` if he hasn't
 */
bool playerLoss(const Player &player);


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