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
 * @brief Updates the scoreboard with a new time and name
 *
 * @param playerName Name of the player
 * @param time Time of the game (in seconds)
 * @param maze maze in which the player has won the game
 */
//void updateScoreBoard(string playerName, int time, string filename, const Maze &maze);





/**
 * @brief
 *
 * @param player
 * @param maze
 * @param fullPath
 */
void updateScoreBoard(Player player, const Maze maze, ScoreBoard &scoreboard);


/**
 * @brief
 *
 * @param player
 * @param maze
 */
void displayScoreboard(Player player, const Maze maze);


/**
 * @brief
 *
 * @param player
 */
void getPlayerName(Player &player);


/**
 * @brief
 *
 * @param fullPath
 */
void printScoreboard(string fullPath);


void getScoreboard(Player &player, const Maze &maze);
