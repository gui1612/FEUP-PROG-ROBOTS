#include "Robot.h"

Robot::Robot(char status, Point coordinates, ID id)
         : Entity(status, coordinates)
    {
        _id = id;
    }

void Robot::setState(unsigned int state) {
    switch (state) {
        case (0):
            _state = ALIVE;
            break;
        case (1):
            _state = STUCK;
            break;
        case (2):
            _state = DEAD;
            break;
    }
}