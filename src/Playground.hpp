#ifndef AGEOFWAR_PLAYGROUND_HPP
#define AGEOFWAR_PLAYGROUND_HPP

#include <array>
#include <iostream>

#include "Player.hpp"

class Base;
class Unit;

class Playground {
private:
    Base &m_blueBase, &m_redBase;
    std::array<Unit *, 12> m_field;

public:
    Playground(Base &blueBase, Base &redBase);
    Playground(const Playground &other);
    ~Playground() = default;

    Base &base(Player::Side side) {
        if (side == Player::Side::blue)
            return m_blueBase;
        else
            return m_redBase;
    }
    const Base &base(Player::Side side) const {
        if (side == Player::Side::blue)
            return m_blueBase;
        else
            return m_redBase;
    }

    std::array<Unit *, 12> &field() {
        return m_field;
    }
    std::array<Unit *, 12> const &field() const {
        return m_field;
    }

};

#endif