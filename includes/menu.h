#pragma once

// Includes
#include <iostream>
#include <string>

// Namespace
using namespace std;


/**
 * @brief Base menu caller function
 *
 */
void menu();


/**
 * @brief Takes the necessary course of action depending on the user input `choice`
 *
 * @param choice value that represents the user menu choice
 * @param confirm tracks if the user really wants to leave the game
 */
void menuChoice(short choice, short &confirm);


/**
 * @brief Displays the rules
 *
 */
void displayRules();