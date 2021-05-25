#include "Player.h"

Player::Player(char status, Point coordinates)
        : Entity(status, coordinates)
    {
        _win = false;
    }


Player::Player(std::string name, int score, char status, Point coordinates)
        : Entity(status, coordinates)
    {
        _name = name;
        _score = score;
        _win = false;
    }


Player::Player(): Entity() { _win = false; _score = 0; }
