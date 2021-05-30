// File includes
#include "Entity.h"

void Entity::kill() {
    char deathRepr = static_cast<char>(std::tolower(_status));
    setStatus(deathRepr);
}