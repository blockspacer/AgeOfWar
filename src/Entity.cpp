#include "Entity.hpp"

Entity::Entity(unsigned int hp) : m_hp(hp) {}

Entity::Entity(const Entity &other) : m_hp(other.m_hp) {}

Entity &Entity::operator=(const Entity &other) {
	hp() = other.hp();
	return *this;
}