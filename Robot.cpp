#include "Robot.h"
#include "constants.h"


Robot::Robot(char status, Point coordinates, unsigned int id, unsigned int state)
         : Entity(status, coordinates)
    {
        _state = state;
        _id = id;
    }


void Robot::setState(const unsigned int state) {
    // Note: If `state` is not ALIVE, DEAD or STUCK nothing is done (invalid state)
    switch (state) {
        case (ALIVE):               // Robot is alive
            _state = ALIVE;
            break;
        case (STUCK):               // Robot is stuck
            _state = STUCK;
            break;
        case (DEAD):                // Robot is dead
            _state = DEAD;
            break;
    }
}


void Robot::kill() {
    setStatus(ROBOT_DEAD_CHAR);
}


bool Robot::isAlive() const {
    return getStatus() == ROBOT_ALIVE_CHAR;
}
