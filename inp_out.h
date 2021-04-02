#pragma once
#ifndef FEUP_PROG_PROJ1_INP_OUT_H
#define FEUP_PROG_PROJ1_INP_OUT_H

#include <iostream>

using namespace std;


/**
 * @brief reads the user input for the selected maze
 *
 */
void mazePick();


/**
 * @brief opens the  MAZE_XX.txt file based on user input provided in mazePick();
 *
 */
void mazeOpen(string levelPick);

#endif //FEUP_PROG_PROJ1_INP_OUT_H
