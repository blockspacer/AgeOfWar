#include "Catapult.hpp"

Catapult::Catapult() : RecruitableUnit(12, 6, Range(2, 3), AreaOfEffect(2), 20) {}

Catapult::Catapult(unsigned int hp) : RecruitableUnit(12, 6, Range(2, 3), AreaOfEffect(2), 20) {}

void Catapult::action(unsigned int phase, Playground &playground, Player &owner) {
	switch (phase) {
		case 1:
			m_canMove = !attack(playground, owner);
			break;
		case 2:
			if (m_canMove)
				moveForward(playground, owner);
			break;
		default:
			break;
	}
}
