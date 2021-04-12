#pragma once

#include "game.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>


using namespace std;


// Vector of players to store each player in the scoreboard
using ScoreBoard = vector<Player>;


/**
 * @brief Fully updates the scoreboard with the new playerName
 *
 * @param fullPath  full relative filepath
 * @param scoreboard `ScoreBoard` instance
 * @param player the `Player` instance of the current game
 */
void getScoreBoard(const string &fullPath, ScoreBoard &scoreboard, const Player &player);


/**
 * @brief Gets the player name (length <= 15)
 *
 * @param player `Player` instance
 */
void getPlayerName(Player &player);


/**
 * @brief Function to ask for the username and update the scoreboard
 *
 * @param player `Player` instance
 * @param maze The `Maze` of the current game
 */
void updateScoreboard(Player &player, const Maze &maze);


/*
 * @brief Parses the current leaderboard file to a `scoreBoard` instance
 *
 * @param leaderBoard file stream for input
 * @param scoreBoard type alias to vector<Player>
 * @param player `Player` instance to check if the current player username already exists in the previous table
 *
 * @note If the current player username exists, always checks sticks to the new score (even if it's lower) for integrity purposes
 */
void parseLines(ifstream &leaderBoard, ScoreBoard &scoreBoard, const Player &player);


/**
 * @brief Gets the index of the last character that is not a space ()
 *
 * @param str the string to check
 *
 * @return returns the index of the last "non-space character"
 */
size_t getLastAlphaIdx(string str);