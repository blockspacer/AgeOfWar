#ifndef AGEOFWAR_RANGE_HPP
#define AGEOFWAR_RANGE_HPP

#include <cstdint>

class Range {
private:
    const unsigned int m_min, m_max;

public:
    explicit Range(unsigned int min = 1, unsigned int max = 1);
    Range(const Range &other) = default;
    ~Range() = default;

    const unsigned int &min() const {
        return m_min;
    }
    const unsigned int &max() const {
        return m_max;
    }

    bool in_range(unsigned int target) const {
        return min() <= target && target <= max();
    }
};

#endif
