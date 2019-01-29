#include "Unit.hpp"

#include <algorithm>

#include "Playground.hpp"

Unit::Unit(unsigned int hp, unsigned int atk, const Range &range,
           const AreaOfEffect &areaOfEffect) : Entity(hp), m_atk(atk), m_range(range), m_areaOfEffect(areaOfEffect) {}

Unit::Unit(const Unit &other) : Entity(other), m_atk(other.m_atk), m_range(other.m_range),
                                m_areaOfEffect(other.m_areaOfEffect) {}

/* Informations */
Unit **Unit::iterator(Playground &playground) const {
	for (Unit **it = playground.field().begin(); it != playground.field().end(); it++)
		if (*it == this)
			return it;
	return nullptr;
}

bool Unit::isOwnedBy(const Player &owner) const {
	return std::find(owner.units().begin(), owner.units().end(), this) != owner.units().end();
}

/* Behavior */
inline bool Unit::attack(Entity &entity) const {
	if (entity.hp() <= atk()) {
		entity.hp() = 0;
		return true;
	}
	entity.hp() -= atk();
	return false;
}

bool Unit::attack(Playground &playground, Player &owner) {
	Unit **it = iterator(playground);
	if (it == nullptr)
		return false;
	/* On vérifie via chaque portée de l'unité. */
	for (unsigned int r = range().min(); range().in_range(r); r++) {
		/* Pour chaque portée on vérfie la zone d'effet. */
		for (unsigned int aoe = 0; areaOfEffect().in_area(aoe + 1); aoe++) {
			Unit **targets = it + r * *owner.side() + aoe * *owner.side();
			/* Si une cible ennemi est touchable on attaque. */
			if (*targets != nullptr && !(*targets)->isOwnedBy(owner)) {
				/* On repart du début de la zone d'attaque et on attaque tout les unités concerné. */
				targets = targets - *owner.side() * aoe;
				for (unsigned int aoe = 0; areaOfEffect().in_area(aoe + 1); aoe++) {
					Unit *target = *(targets + *owner.side() * aoe);
					if (target != nullptr) {
						if (attack(*target)) {
							onKill(*target, playground, owner);
							*target->iterator(playground) = nullptr;
						}
					}
				}
				return true;
			}
			/* Si il n'y a aucune cibles. On visera donc les bases en dernier ressort. */
			if (targets == playground.field().begin()) {
				attack(playground.base(Player::Side::blue));
				return true;
			}
			if (targets == playground.field().end() - 1) {
				attack(playground.base(Player::Side::red));
				return true;
			}
		}
	}
	return false;
}

bool Unit::moveForward(Playground &playground, const Player &player) {
	auto it = iterator(playground);
	if (it == nullptr)
		return false;
	auto it_next = it + *player.side();
	if (it_next == playground.field().begin() || it_next == playground.field().end() - 1 || *it_next != nullptr)
		return false;
	std::swap(*it, *it_next);
	return true;
}

/* Reactive behavior */
inline void Unit::onKill(Unit &killed, Playground &playground, Player &owner) {
	RecruitableUnit *ptr_killed = dynamic_cast<RecruitableUnit *>(&killed);
	if (ptr_killed != nullptr)
		owner.gold() += ptr_killed->price() / 2;
}

inline void Unit::onKilled(Playground &playground, Player &owner) {
	/* On se suicide. */
	owner.units().erase(std::remove(owner.units().begin(), owner.units().end(), this), owner.units().end());
	delete this;
}
