#pragma once

#include "game.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * @brief Updates the scoreboard with a new time and name
 *
 * @param playerName Name of the player
 * @param time Time of the game (in seconds)
 * @param maze maze in which the player has won the game
 */
//void updateScoreBoard(string playerName, int time, string filename, const Maze &maze);


void updateScoreBoard(Player player, const Maze maze, string fullPath);


void displayScoreboard(Player player, const Maze maze);


void getPlayerName(string &playerName);


void printScoreboard(string fullPath);
