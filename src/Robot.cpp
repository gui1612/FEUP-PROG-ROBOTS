#include "Robot.h"

Robot::Robot(char status, Point coordinates, ID id, unsigned int state)
         : Entity(status, coordinates)
    {
        _id = id;
        _state = state;
    }

void Robot::setState(unsigned int state) {
    switch (state) {
        case (Robot::ALIVE):
            _state = ALIVE;
            break;
        case (Robot::STUCK):
            _state = STUCK;
            break;
        case (Robot::DEAD):
            _state = DEAD;
            break;
    }
}