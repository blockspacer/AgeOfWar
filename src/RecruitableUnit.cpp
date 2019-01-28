#include "RecruitableUnit.hpp"

RecruitableUnit::RecruitableUnit(unsigned int hp, unsigned int atk, const Range &range,
                                 const AreaOfEffect &areaOfEffect, unsigned int price) : Unit(hp, atk, range,
                                                                                              areaOfEffect),
                                                                                         m_price(price) {}

RecruitableUnit::~RecruitableUnit() {}

