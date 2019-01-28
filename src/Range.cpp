#include "Range.hpp"

#include <cassert>

Range::Range(unsigned int min, unsigned int max) : m_min(min), m_max(max) {
        assert(0 < min && min <= max);
    }

