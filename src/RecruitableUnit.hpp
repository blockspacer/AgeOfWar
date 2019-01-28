#ifndef AGEOFWAR_RECRUITABLE_HPP
#define AGEOFWAR_RECRUITABLE_HPP

#include "Unit.hpp"

class RecruitableUnit : public Unit {
private:
	unsigned int m_price;

protected:
	RecruitableUnit(unsigned int hp, unsigned int atk, const Range &range, const AreaOfEffect &areaOfEffect,
	                unsigned int price);
	~RecruitableUnit() override;

public:
	unsigned int price() const {
		return m_price;
	}
};

#endif