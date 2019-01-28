#ifndef AGEOFWAR_AREA_OF_EFFECT_HPP
#define AGEOFWAR_AREA_OF_EFFECT_HPP

#include <cstdint>

class AreaOfEffect {
private:
    const unsigned int m_size;

public:
    AreaOfEffect(unsigned int size = 1);
    ~AreaOfEffect() = default;

    const unsigned int &size() const {
        return m_size;
    }

    bool in_area(unsigned int target) const {
        return 1 <= target && target <= size();
    }
};

#endif
