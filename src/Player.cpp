#include "Player.hpp"

#include <algorithm>

#include "Playground.hpp"

#include "Soldier.hpp"
#include "Archer.hpp"
#include "Catapult.hpp"

Player::Player(Player::Side s) : m_side(s), m_gold(10), m_base(), m_units() {}

Player::Player(Player::Side side, unsigned int gold) : m_side(side), m_gold(gold), m_base(), m_units() {}

Player::Player(const Player &other) : m_side(other.m_side), m_gold(other.m_gold), m_base(other.m_base), m_units(other.m_units) {}

/* Behavior */
void Player::turn(Playground &playground) {
    std::for_each(std::begin(units()), std::end(units()), [&](Unit *u) {
        if (u->hp() == 0)
	        u->onKilled(playground, *this);
    });
    /* On déroule les actions de chaque unités du plus avancer au moins avancer pour la phase 1... */
    std::for_each(std::begin(units()), std::end(units()), [&](Unit *u) { u->action(1, playground, *this); });
    /* On déroule les actions de chaque unités du plus avancer au moins avancer pour la phase 2 & 3... */
    std::for_each(std::rbegin(units()), std::rend(units()), [&](Unit *u) { u->action(2, playground, *this); });
	std::for_each(std::rbegin(units()), std::rend(units()), [&](Unit *u) { u->action(3, playground, *this); });
}

void Player::play(Playground &playground) {
    std::cin.sync();
    if (playground.field()[~side()] == nullptr) {
        switch (std::cin.get()) {
            case '1':
	            playground.field()[~side()] = new Soldier();
	            break;
            case '2':
	            playground.field()[~side()] = new Archer();
	            break;
            case '3':
	            playground.field()[~side()] = new Catapult();
	            break;
	        case 'q':
	        	break;
            default:
	            break;
        }
        if (playground.field()[~side()]) {
        	unsigned int price = dynamic_cast<RecruitableUnit*>(playground.field()[~side()])->price();
	        if (price <= gold()) {
	        	gold() -= price;
		        recruit(*reinterpret_cast<RecruitableUnit*>(playground.field()[~side()]));
	        } else
		        playground.field()[~side()] = nullptr;
        }
    }
    gold() += 8;
}



