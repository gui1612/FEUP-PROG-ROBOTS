//#ifndef FEUP_PROG_PROJ1_POST_H
//#define FEUP_PROG_PROJ1_POST_H
#pragma once

#include "globaldefs.h"

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
        Post(Point coordinates, char symbol): _coordinates(coordinates), _symbol(symbol) {};


        /* 'Getter functions' */
        Point getCoordinates() const           { return _coordinates;        };
        char getSymbol() const                 { return _symbol;             };


        /* 'Setter functions' */
        void setCoordinates(Point coordinates) { _coordinates = coordinates; };
        void setSymbol(char symbol)            { _symbol =  symbol;          };

        /**
         * @brief Checks if a Post is eletrified
         * @return `true` if the post is eletrified, otherwise `false`
         */
        bool isElectrified() const;

        /**
         * @brief Checks if the post is an Exit
         * @return `true` if the post is an Exit, otherwise `false`
         */
        bool isExit() const;

        void deactivatePost();
};

//#endif //FEUP_PROG_PROJ1_POST_H