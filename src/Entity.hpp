#ifndef AGEOFWAR_ENTITY_HPP
#define AGEOFWAR_ENTITY_HPP

#include <iostream>

class Entity {
private:
    unsigned int m_hp;

protected:
    explicit Entity(unsigned int hp);
    Entity(const Entity& other);
    Entity &operator=(const Entity& other);

public:
    virtual ~Entity() = default;

    unsigned int &hp();
    unsigned int hp() const;
};

#include "Entity.inl"

#endif
