#include "Robot.h"
#include "constants.h"

// Static variables initialization
//int Robot::_robotCount  = 0;


Robot::Robot(char status, Point coordinates, unsigned int id, unsigned int state)
         : Entity(status, coordinates)
    {
        _state = state;
        _id = id;
        //_robotCount++;                                   // Increments the Robot count by one (Robot instance is created)
    }


void Robot::setState(const unsigned int state) {
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
}


bool Robot::isAlive() const {
    return getStatus() == ROBOT_ALIVE_CHAR;
}
