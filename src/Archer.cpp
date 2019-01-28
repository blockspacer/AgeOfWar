#include "Archer.hpp"

Archer::Archer() : RecruitableUnit(8, 3, Range(1, 3), AreaOfEffect(), 12) {}

Archer::Archer(unsigned int hp) : RecruitableUnit(hp, 3, Range(1, 3), AreaOfEffect(), 12) {}

void Archer::action(unsigned int phase, Playground &playground, Player &owner) {
	switch (phase) {
		case 1:
			attack(playground, owner);
			break;
		case 2:
			moveForward(playground, owner);
			break;
		default:
			break;
	}
}

