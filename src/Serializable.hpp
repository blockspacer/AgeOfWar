#ifndef AGEOFWAR_SERIALIZABLE_HPP
#define AGEOFWAR_SERIALIZABLE_HPP

#include <iostream>

class Serializable {
protected:
    virtual void serialize(std::ostream &os) const = 0;
    virtual void deserialize(std::istream &is) = 0;

public:
    virtual ~Serializable() = default;
};

#endif
