#ifndef AGEOFWAR_NEXUS_HPP
#define AGEOFWAR_NEXUS_HPP

#include <iomanip>
#include "Entity.hpp"
#include "Serializable.hpp"

class Base : public Entity {
public:
    Base();
    ~Base() override = default;

};

std::ostream &operator<<(std::ostream &os, const Base &e);

#endif
