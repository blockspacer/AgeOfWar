#include "Player.hpp"

#include <algorithm>
#include <iostream>

#include "Playground.hpp"

#include "Soldier.hpp"
#include "Archer.hpp"
#include "Catapult.hpp"

Player::Player(Player::Side s) : m_side(s), m_gold(10), m_base(), m_units() {}

Player::Player(Player::Side side, unsigned int gold) : m_side(side), m_gold(gold), m_base(), m_units() {}

/*
void Player::deserialize(std::istream &is) {
    gold() = static_cast<std::uint8_t>(is.get());
    base().hp() = static_cast<std::uint8_t>(is.get());
    auto unitno = static_cast<std::uint8_t>(is.get());
    for (std::uint8_t i = 0; i < unitno; i++) {
        auto p = static_cast<std::uint8_t>(is.get() & 0b00001111);
        Unit *u = nullptr;
        switch (static_cast<Unit::Type>(is.peek() >> 4)) {
            case Unit::Type::infantryman:
                u = new Soldier();
                break;
            case Unit::Type::archer:
                u = new Soldier();
                break;
            case Unit::Type::catapult:
                u = new Soldier();
                break;
            case Unit::Type::super_soldier:
                break;
        }
    }
}
*/

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
    /* On traduit en -1 en 11 et 1 en 0 (car -1 (11...11) & 0b10110 = 22 et 22 >> 1 = 11, 0 & 0b10110 = 0 et 0 >> 1 = 0). */
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



