/* Unit.hpp inline implementation.*/

inline unsigned int Unit::atk() const {
	return m_atk;
}

inline const Range &Unit::range() const {
	return m_range;
}

inline const AreaOfEffect &Unit::areaOfEffect() const {
	return m_areaOfEffect;
}