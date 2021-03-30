#pragma once
#ifndef PROJ_MENU_H
#define PROJ_MENU_H

#include <iostream>

using namespace std;


/**
 * @brief Base menu caller function
 *
 * @return returns 0 if the player leaves the game
 */
int menu();


/**
 * @brief Clears the console screen
 *
 */
void clearScreen();


/**
 * @brief Displays the rules
 *
 */
void displayRules();

#endif //PROJ_MENU_H