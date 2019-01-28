/* Player.hpp inline implementation.*/

inline Player::Side Player::side() const {
    return m_side;
}

inline unsigned int &Player::gold() {
    return m_gold;
}

inline unsigned int const &Player::gold() const {
    return m_gold;
}

inline Base &Player::base() {
    return m_base;
}

inline Base const &Player::base() const {
    return m_base;
}

inline std::vector<Unit *> &Player::units() {
    return m_units;
}

inline std::vector<Unit *> const &Player::units() const {
    return m_units;
}

#include "RecruitableUnit.hpp"

inline void Player::recruit(RecruitableUnit& unit) {
    m_units.push_back(&unit);
}

inline Player::Side operator!(Player::Side rhs) {
    return (rhs == Player::Side::blue ? Player::Side::red : Player::Side::blue);
}

inline unsigned int operator~(Player::Side rhs) {
    return static_cast<unsigned int>((static_cast<int>(rhs) & 0b10110) >> 1);
}

inline std::size_t operator*(Player::Side rhs) {
    return static_cast<std::size_t>(rhs);
}