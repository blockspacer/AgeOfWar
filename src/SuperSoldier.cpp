#include "SuperSoldier.hpp"

#include "Soldier.hpp"

SuperSoldier::SuperSoldier(const Soldier &other) : Unit(other) {}

SuperSoldier::SuperSoldier(unsigned int hp) : Unit(hp, 4, Range(), AreaOfEffect()) {}

void SuperSoldier::action(unsigned int phase, Playground &playground, Player &owner) {
	switch (phase) {
		case 1:
			attack(playground, owner);
			break;
		case 2:
			moveForward(playground, owner);
			break;
		case 3:
			attack(playground, owner);
			break;
		default:
			break;
	}
}