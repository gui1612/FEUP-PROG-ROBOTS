#pragma once
#ifndef PROJ_MENU_H
#define PROJ_MENU_H

#include <iostream>
#include <string>

using namespace std;


/**
 * @brief Base menu caller function
 *
 * @return returns 0 if the player leaves the game
 */
int menu();


/**
 * @brief Takes the necessary course of action depending on the user input `choice`
 *
 * @param choice int value that represents the user menu choice
 * @param confirm tracks if the user really wants to leave the game
 */
void menuChoice(short choice, int &confirm);


/**
 * @brief Warns the user about bad input
 */
void warnUser();


/**
 * @brief Displays the rules
 *
 */
void displayRules();

#endif //PROJ_MENU_H