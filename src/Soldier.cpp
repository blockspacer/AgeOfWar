#include "Soldier.hpp"

#include "Player.hpp"
#include "SuperSoldier.hpp"

#include <algorithm>

Soldier::Soldier() : RecruitableUnit(10, 4, Range(), AreaOfEffect(), 10) {}

Soldier::Soldier(unsigned int hp) : RecruitableUnit(hp, 4, Range(), AreaOfEffect(), 10), m_retryAttack(false) {}

void Soldier::action(unsigned int phase, Playground &playground, Player &owner) {
	switch (phase) {
		case 1:
			m_retryAttack = !attack(playground, owner);
			break;
		case 2:
			moveForward(playground, owner);
			break;
		case 3:
			if (m_retryAttack)
				attack(playground, owner);
			break;
		default:
			break;
	}
}

void Soldier::onKill(Unit &killed, Playground &playground, Player &owner) {
	Unit::onKill(killed, playground, owner);
	if (hp() <= 4 && dynamic_cast<Soldier *>(&killed) != nullptr) {
		Unit *superSoldier = new SuperSoldier(*this);
		std::replace(owner.units().begin(), owner.units().end(), reinterpret_cast<Unit *>(this), superSoldier);
		*iterator(playground) = superSoldier;
		delete this;
	}
}