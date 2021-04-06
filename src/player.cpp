#include "../includes/player.h"


void updatePlayer(char key, Player &player, const Maze &maze){
    switch (key){
        case('q'):
            player.coordinates.at(0)--;
            player.coordinates.at(1)--;
            break;
        case ('w'):
            player.coordinates.at(1)--;
            break;
        case('e'):
            player.coordinates.at(0)++;
            player.coordinates.at(1)--;
            break;
        case('a'):
            player.coordinates.at(0)--;
            break;
        case('s'):
            break;
        case('d'):
            player.coordinates.at(0)++;
            break;
        case('z'):
            player.coordinates.at(0)--;
            player.coordinates.at(1)++;
            break;
        case('x'):
            player.coordinates.at(1)++;
            break;
        case('c'):
            player.coordinates.at(0)++;
            player.coordinates.at(1)++;
            break;
    }

    int x = player.coordinates.at(0);
    int y = player.coordinates.at(1);

    if (maze.coordinates.at(y).at(x) == '*' || maze.coordinates.at(y).at(x) == 'R'){
        player.alive = false;
    }
}

void playerDraw(Player player, Maze &maze){
    int x = player.coordinates.at(0);
    int y = player.coordinates.at(1);
    //maze.coordinates.at(y).at(x) = ' ';
    maze.coordinates.at(y).at(x) = 'H';
}