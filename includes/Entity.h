//#ifndef FEUP_PROG_PROJ1_ENTITY_H
//#define FEUP_PROG_PROJ1_ENTITY_H
#pragma once

#include "globaldefs.h"
#include <cctype>

class Entity {

public:
    /**
     * @brief Constructor for Entity
     *
     * @param status The char representation of the entity
     * @param coordinates The coordinates (x, y) of the Entity
     */
    Entity(char status, Point coordinates): _status(status), _coordinates(coordinates) {};

    /**
     * @brief Creates a default constructor for an Entity object
     */
    Entity(): _status(), _coordinates() {};

    /* 'Getter functions' */
    Point getCoordinates() const                    { return _coordinates;          }
    char getStatus() const                          { return _status;               }
    bool isAlive() const                            { return std::isupper(_status); }


    /* 'Setter functions' */

    /** @brief Sets the status (character representation) of the Entity */
    void setStatus(char status)                     { _status = status;                        }

    /** @brief Moves the Entity to a new Point */
    void moveTo(Point coordinates)                  { _coordinates = coordinates;              }

    /** @brief Kills the Entity
     * @details In order to kill the Entity we simply change
     * */
    void kill()                                     { setStatus(static_cast<char>(std::tolower(_status))); }

protected:
    /**
     * @brief The representation of the Entity
     *
     * @note Possible representations ()
     * 'H'/'h' - alive/ dead Player
     * 'R'/'r' - alive/ dead Robot
     *
     * Note that Entity is only supposed to support Robot or Player objects
     */
    char  _status;

    Point _coordinates;       /** @brief Coordinates of the player in the `Maze` */
};


//#endif //FEUP_PROG_PROJ1_ENTITY_H