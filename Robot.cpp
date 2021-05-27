#include "Robot.h"
#include "constants.h"

Robot::Robot(char status, Point coordinates, ID id, unsigned int state)
         : Entity(status, coordinates)
    {
        _id = id;
        _state = state;
    }

void Robot::setState(unsigned int state) {
    switch (state) {
        case (Robot::ALIVE):
            setState(ALIVE);
            break;
        case (Robot::STUCK):
            _state = STUCK;
            break;
        case (Robot::DEAD):
            _state = DEAD;
            break;
    }
}


void Robot::kill() {
    setStatus(ROBOT_DEAD_CHAR);
    //setState(Robot::DEAD);
}


bool Robot::isAlive() const {
    return getStatus() == ROBOT_ALIVE_CHAR;
}
