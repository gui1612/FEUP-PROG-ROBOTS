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
void updateScoreBoard(const string fullPath, ScoreBoard &scoreboard, const string mazeNumber);


/**
 * @brief
 *
 * @param player
 * @param maze
 */
void displayScoreboard(const string &fullPath);



/**
 * @brief
 *
 * @param player
 */
void getPlayerName(Player &player);


void getScoreboard(Player &player, const Maze &maze);


void parseLines(ifstream &leaderBoard, ScoreBoard &scoreBoard);


size_t getLastAlphaIdx(string str);


int findLastIndex(string& str, char x);