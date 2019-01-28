#include "Base.hpp"

Base::Base() : Entity(100) {}

std::ostream &operator<<(std::ostream &os, const Base &e) {
    return os << "Base " << e.hp() << "/100";
}