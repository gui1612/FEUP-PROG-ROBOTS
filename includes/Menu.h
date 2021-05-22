//#ifndef FEUP_PROG_PROJ1_MENU_H
//#define FEUP_PROG_PROJ1_MENU_H
#pragma once


#include "globaldefs.h"
#include <iostream>
#include <string>
#include <optional>


void menu();
void menuChoice(short choice, short &confirm);
void displayRules();
std::optional<std::string> mazePick();
bool validMaze(const short &filename, std::string &fullPath, std::ifstream &mazeFile);
void displayLeaderboard();


std::optional<std::string> getMazeName(short levelChoice);

// #endif //FEUP_PROG_PROJ1_MENU_H


