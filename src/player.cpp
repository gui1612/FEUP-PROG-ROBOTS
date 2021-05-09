//
// Created by ANTONIO on 5/9/2021.
//

#include "player.h"

bool Player::updatePlayer(Player &player, char key, Maze &maze){
    // Player position before the movement
    Point lastPos = {player.coordinates.x, player.coordinates.y};

    switch (static_cast<char>(tolower(key))) {
        case('q'):                             // Up left
            player.coordinates.x--;
            player.coordinates.y--;
            break;
        case ('w'):                            // Up
            player.coordinates.y--;
            break;
        case('e'):                             // Up right
            player.coordinates.x++;
            player.coordinates.y--;
            break;
        case('a'):                             // Left
            player.coordinates.x--;
            break;
        case('s'):                             // Stay
            break;
        case('d'):                             // Right
            player.coordinates.x++;
            break;
        case('z'):                             // Down left
            player.coordinates.x--;
            player.coordinates.y++;
            break;
        case('x'):                              // Down
            player.coordinates.y++;
            break;
        case('c'):                              // Down right
            player.coordinates.x++;
            player.coordinates.y++;
            break;
    }
    // New position
    xval x = player.coordinates.x;
    yval y = player.coordinates.y;

    if (!outOfBounds(player.coordinates, maze)) {                                // Checks if the player is inside the maze bounds
        char newPosChar = maze.gameBoard.at(y).at(x);
        if (newPosChar == ' ' || newPosChar == 'H') {                            // Valid player movement
            playerDraw(lastPos, player, maze);                               // Updates coordinates on the maze
            return true;
        } else if (newPosChar == 'R' || newPosChar == '*') {                     // Kills the player if they move into a live robot or electric fence
            player.alive = false;
            mazeReplace(maze, lastPos, 'h');
            return true;
        } else {                                                                 // Invalid player move
            player.coordinates = lastPos;
            return false;
        }
    } else {                                                                     // Invalid move (out of maze bounds)
        player.coordinates = lastPos;
        return false;
    }
}

void Player::playerDraw(int lastPos, const Player &player, int &maze) {
    maze.gameBoard.at(lastPos.y).at(lastPos.x) = ' ';             // Replacing player last position
    mazeReplace(maze, player.coordinates, 'H');  // Replacing player new position
}


bool Player::outOfBounds(const int &pos, const int &maze) {
    const unsigned int HEIGHT = maze.rows, WIDTH = maze.columns;                    // Creating height and width variables by looking at the maze instance
    return !(0 <= pos.y && pos.y < HEIGHT && 0 <= pos.x && pos.x < WIDTH);          // Returning true (if inbounds) and false (if out of bounds)
}