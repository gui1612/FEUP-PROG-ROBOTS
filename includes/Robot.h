#pragma once

// File includes
#include "Utils.h"
#include "Entity.h"

/** @brief Store a Robot (Position, ID, status and their coordinates) */
class Robot : public Entity {
    /** @brief ID of the robot (unique for each robot) */
    ID _id;

    /**
     * @brief Represents the state of the Robot (alive, dead or stuck)
     * @note This is an internal attribute which is not used for the game logics
     */
    unsigned int _state;

public:
    // Possible states for a Robot
    enum State{ ALIVE = 0, STUCK, DEAD };


    /**
     * @brief Constructor for Robot
     *
     * @param alive 'true' if robot is alive, else 'false'
     * @param id unique identification for each robot
     * @param coordinates position of the robot in the maze
     * @param robotNum number of Robots in the game
     */
    Robot(char status, Point coordinates, unsigned int id, unsigned int state);


    /* 'Getter functions' */
    ID getID() const                       { return _id;          }


    /**
     * @brief Boolean function used to check if the robot is alive (true)
     * 
     * @notes Override of method declared in Entity
     */
    virtual bool isAlive() const;


    /* 'Setter functions' */
    void setState(unsigned int state);



    /** @brief Kills the Entity */
    virtual void kill();


    /** @overload
     *  @param r1 Robot instance
     *  @param r2 Robot instance
     *  @return `true` if the robots are the same, otherwise `false`
     */
    friend inline bool operator==(const Robot &r1, const Robot &r2) { return r1.getID() == r2.getID(); }
};