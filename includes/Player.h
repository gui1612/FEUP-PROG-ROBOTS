#pragma once

// File Includes
#include "globaldefs.h"
#include "Entity.h"

// Lib Includes
#include <string>

/** @brief Store a Player (Position, name, status and their coordinates) */
class Player : public Entity {
    /** @brief Name of the Player */
    std::string _name;

    /** @brief Score of the current player */
    int _score;

    /** @brief Checks if the player has met the win condition */
    bool _win;
public:
    /**
     * @brief Creates a Player object
     * @param name name of the player
     * @param score measure of the player's skill
     * @param status character representation of the Player
     * @param coordinates position of the player in the maze
     */
    Player(std::string name, int score, char status, Point coordinates);

    /**
     * @brief Creates a default constructor for a Player object
     */
    Player();

    /**
     * @brief Creates a Player object
     *
     * @param status character representation of the Player
     * @param coordinates position of the player in the maze
     */
    Player(char status, Point coordinates);

    /* 'Getter functions' */
    ID getScore() const             { return _score;    }
    std::string getName() const     { return _name;     }
    bool win()                      { return _win;      }


    /* 'Setter functions' */
    void setScore(int score)        { _score = score;   }
    void setName(std::string name)  { _name = name;     }
    void setWin()                   { _win = true;      }
};