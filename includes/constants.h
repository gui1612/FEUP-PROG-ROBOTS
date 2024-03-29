#pragma once

// Lib includes
#include <limits>

/** @page Global Constants definition 
 *  @note Changing the values in here will
 * change them in the entire program.
 */


////////////////////////////// CHAR REPRESENTATION ////////////////

const char PLAYER_ALIVE_CHAR      = 'H';			// Default: 'H'
const char PLAYER_DEAD_CHAR       = 'h';			// Default: 'h'
const char ROBOT_ALIVE_CHAR       = 'R';			// Default: 'R'
const char ROBOT_DEAD_CHAR        = 'r';			// Default: 'r'
const char ELECTRIC_POST_CHAR     = '*';			// Default: '*'
const char NON_ELECTRIC_POST_CHAR = '+';			// Default: '+'
const char EXIT_POST_CHAR		  = 'O';			// Default: 'O'
const char BLANK_CHAR			  =	' ';			// Default: ' '



//////////////////////////////// INTERNALS /////////////////////////


// 'MAX_MAZES_NUM' represents the limit of Mazes that can exist in the program
// Warning: Changing this value may affect the performance
const int MAX_MAZES_NUM			  = 99; 		    // Default: 99


// 'CLEAR_SCREEN_NL' represents the newline characters given when clearing screen
const int CLEAR_SCREEN_NL		  = 100;			 // Default: 100


/// 'SLEEP_TIME' sets the waiting time for animations in the game
const unsigned int SLEEP_TIME     = 2;					  // Default: 2


// 'MAX_STREAM_LIMIT' represents the amount of character to ignore when reading the Maze file
const auto MAX_STREAM_LIMIT = std::numeric_limits<std::streamsize>::max();

