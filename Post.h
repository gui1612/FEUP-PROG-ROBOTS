#pragma once

// File Includes
#include "Utils.h"

class Post {
    Point _coordinates;

    /** @brief Type is 'O' if the post is a leave or '+' if it is a non-electrified post or '*' if it is and electrified post */
    char _symbol;

    public:

        /**
         * @brief
         * @param 'true' if entity is alive, else 'false'
         * @param coordinates position of the robot in the maze
         */
        Post(Point coordinates, char symbol): _coordinates(coordinates), _symbol(symbol) {}


        /* 'Getter functions' */
        Point getCoordinates() const           { return _coordinates;        }
        char getSymbol() const                 { return _symbol;             }


        /* 'Setter functions' */
        void setSymbol(char symbol)            { _symbol =  symbol;          }


        /**
         * @brief Checks if a Post is eletrified
         * @return `true` if the post is eletrified, otherwise `false`
         */
        bool isElectrified() const;


        /**
         * @brief Checks if a Post is eletrified
         * @return `true` if the post is eletrified, otherwise `false`
         */
        bool isNotEletrified() const;


        /**
         * @brief Checks if the post is an Exit
         * @return `true` if the post is an Exit, otherwise `false`
         */
        bool isExit() const;


        /** @brief Deactivates the post (passes from eletrified to non-eletrified) */
        void deactivatePost();
};