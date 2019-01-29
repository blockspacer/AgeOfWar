#include "AIPlayer.hpp"

#include <algorithm>

#include "Playground.hpp"

#include "Soldier.hpp"
#include "Archer.hpp"
#include "Catapult.hpp"

AIPlayer::AIPlayer(Player::Side side) : Player(side) {}

AIPlayer::AIPlayer(const Player &other) : Player(other) {}

void AIPlayer::play(Playground &playground) {
	if (playground.field()[~side()] == nullptr) {
		if (Catapult().price() <= gold()) {
			gold() -= Catapult().price();
			playground.field()[~side()] = new Catapult();
		} else if (Archer().price() <= gold()) {
			gold() -= Archer().price();
			playground.field()[~side()] = new Archer();
		} else if (Soldier().price() <= gold()) {
			gold() -= Soldier().price();
			playground.field()[~side()] = new Soldier();
		}
		if (playground.field()[~side()])
			recruit(*reinterpret_cast<RecruitableUnit *>(playground.field()[~side()]));
	}
	gold() += 8;
}

