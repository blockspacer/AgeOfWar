#include "Game.hpp"

#include <fstream>

#include "utils/ANSIColors.hpp"
#include "utils/bitstream.hpp"

#include "AIPlayer.hpp"

#include "Soldier.hpp"
#include "Archer.hpp"
#include "Catapult.hpp"
#include "SuperSoldier.hpp"

Game::Game() : m_save(), m_turnNo(1), m_bluePlayer(*new Player(Player::Side::blue)),
               m_redPlayer(*new Player(Player::Side::red)),
               m_playground(m_bluePlayer.base(), m_redPlayer.base()) {}


Game::Game(const char *save, bool AI) : m_save(save), m_turnNo(1),
                                                m_bluePlayer(*new Player(Player::Side::blue)),
                                                m_redPlayer(AI ? *new AIPlayer(Player::Side::blue): *new Player(Player::Side::red)),
                                                m_playground(m_bluePlayer.base(), m_redPlayer.base()) {
	std::string s = save;
	s += +".sav";
	std::fstream ifs(s);
	ifs.peek();
	if (!ifs.eof())
		deserialize(ifs);
	ifs.close();
}

void Game::serialize(std::ostream &os) const {
	obitstream obs = obitstream(os.rdbuf());
	obs.put(turnNo(), 7);
	/* blue */
	obs.put(static_cast<int>(dynamic_cast<AIPlayer *>(&m_bluePlayer) ? 1 : 0), 1);
	obs.put(bluePlayer().base().hp(), 7);
	obs.put(bluePlayer().gold(), 7);

	/* red */
	obs.put(dynamic_cast<AIPlayer *>(&m_redPlayer) ? 1 : 0, 1);
	obs.put(redPlayer().base().hp(), 7);
	obs.put(redPlayer().gold(), 7);
	/* units */
	for (int i = 0; i < 12; i++) {
		if (playground().field()[i]) {
			obs.put(1, 1);
			obs.put(playground().field()[i]->isOwnedBy(redPlayer()), 1);
			if (dynamic_cast<Soldier *>(playground().field()[i]))
				obs.put(static_cast<int>(Unit::Type::soldier), 3);
			else if (dynamic_cast<Archer *>(playground().field()[i]))
				obs.put(static_cast<int>(Unit::Type::archer), 3);
			else if (dynamic_cast<Catapult *>(playground().field()[i]))
				obs.put(static_cast<int>(Unit::Type::catapult), 3);
			else
				obs.put(static_cast<int>(Unit::Type::super_soldier), 3);
			obs.put(playground().field()[i]->hp(), 4);
		} else
			obs.put(0, 1);
	}
	obs.flush();
}

void Game::deserialize(std::istream &is) {
	ibitstream ibs = ibitstream(is.rdbuf());
	m_turnNo = static_cast<unsigned int>(ibs.get(7));
	/* blue */
	if (ibs.get(1)) {
		delete &m_bluePlayer;
		bluePlayer() = *new AIPlayer(Player::Side::blue);
	}
	bluePlayer().base().hp() = static_cast<unsigned int>(ibs.get(7));
	bluePlayer().gold() = static_cast<unsigned int>(ibs.get(7));
	playground().base(Player::Side::blue) = bluePlayer().base();
	/* red */
	if (ibs.get(1)) {
		delete &m_redPlayer;
		redPlayer() = *new AIPlayer(Player::Side::red);
	}
	redPlayer().base().hp() = static_cast<unsigned int>(ibs.get(7));
	redPlayer().gold() = static_cast<unsigned int>(ibs.get(7));
	playground().base(Player::Side::red) = redPlayer().base();

	/* units */
	for (int i = 0; i < 12; i++) {
		if (ibs.get(1)) {
			bool team = static_cast<bool>(ibs.get(1));
			switch (static_cast<Unit::Type>(ibs.get(3))) {
				case Unit::Type::soldier:
					playground().field()[i] = new Soldier(static_cast<unsigned int>(ibs.get(4)));
					break;
				case Unit::Type::super_soldier:
					playground().field()[i] = new SuperSoldier(static_cast<unsigned int>(ibs.get(4)));
					break;
				case Unit::Type::archer:
					playground().field()[i] = new Archer(static_cast<unsigned int>(ibs.get(4)));
					break;
				case Unit::Type::catapult:
					playground().field()[i] = new Catapult(static_cast<unsigned int>(ibs.get(4)));
					break;
				default:
					std::cout << "Erreur pendant le chargement, sauvegarde corrompu... Aborting..." << std::endl;
			}
			(!team ? bluePlayer() : redPlayer()).units().push_back(playground().field()[i]);
		}
	}
}

void Game::run() {
	m_running = true;
	while (m_running) {
		turn();
		if (m_save) {
			std::string s = m_save;
			s += ".sav";
			std::ofstream ofs(s, std::ios_base::trunc);
			serialize(ofs);
			ofs.close();
		}
	}
}

void Game::turn() {
	bluePlayer().turn(playground());
	std::cout << *this << std::endl << ansi::color("waiting blue to play...", ansi::normal_blue_foreground) << std::endl;
	bluePlayer().play(playground());
	if (redPlayer().base().hp() == 0) {
		std::cout << "Congratulation! " << ansi::color("blue", ansi::normal_blue_foreground) << " wins!" << std::endl;
		stop();
	}

	std::cout << *this << std::endl << ansi::color("press enter...", ansi::strong_magenta_foreground) << std::endl;
	std::cin.sync();
	std::cin.get();

	redPlayer().turn(playground());
	std::cout << *this << std::endl << ansi::color("waiting red to play...", ansi::normal_red_foreground) << std::endl;
	redPlayer().play(playground());
	if (bluePlayer().base().hp() == 0) {
		std::cout << "Congratulation! " << ansi::color("red", ansi::normal_red_foreground) << " wins!" << std::endl;
		stop();
	}

	if (99 < m_turnNo++) {
		std::cout << "Draw! Turn limit exceeded." << std::endl;
		stop();
	}
}

std::ostream &operator<<(std::ostream &os, const Game &game) {
	/* TITLE & TURN */
	os << "  " << ansi::color("Age Of War", ansi::inverse) << std::endl << std::endl
	   << ansi::color("Turn", ansi::inverse) << ": " << game.turnNo() << std::endl << std::endl;
	/* BASE */
	os << ansi::color(" __    __     __     __    __", ansi::normal_blue_foreground);
	for (int i = 0; i < 50; i++) os << ' ';
	os << ansi::color(" __    __     __     __    __", ansi::normal_red_foreground) << std::endl;
	os << ansi::color("|__|__|__|___|__|___|__|__|__|", ansi::normal_blue_foreground);
	for (int i = 0; i < 49; i++) os << ' ';
	os << ansi::color("|__|__|__|___|__|___|__|__|__|", ansi::normal_red_foreground) << std::endl;
	os << ansi::color(" \\_|__|__|__|__|__|__|__|_|_/", ansi::normal_blue_foreground);
	for (int i = 0; i < 50; i++) os << ' ';
	os << ansi::color(" \\_|__|__|__|__|__|__|__|_|_/", ansi::normal_red_foreground) << std::endl;
	os << ansi::color("  \\__|____|___|___|____|__/", ansi::normal_blue_foreground);
	for (int i = 0; i < 52; i++) os << ' ';
	os << ansi::color("  \\__|____|___|___|____|__/", ansi::normal_red_foreground) << std::endl;
	os << ansi::color("   |_|||_|__|_|_|__|_|_|_|", ansi::normal_blue_foreground);
	for (int i = 0; i < 53; i++) os << ' ';
	os << ansi::color("   |_|||_|__|_|_|__|_|_|_|", ansi::normal_red_foreground) << std::endl;
	os << ansi::color("   ||_|_|_/| | | |\\|_|__||", ansi::normal_blue_foreground);
	for (int i = 0; i < 53; i++) os << ' ';
	os << ansi::color("   ||_|_|_/| | | |\\|_|__||", ansi::normal_red_foreground) << std::endl;
	os << ansi::color("   |_|_|_/ | | | | \\|_|_||", ansi::normal_blue_foreground);
	for (int i = 0; i < 53; i++) os << ' ';
	os << ansi::color("   |_|_|_/ | | | | \\|_|_||", ansi::normal_red_foreground) << std::endl;
	os << ansi::color("   |_|_||| | | | | ||_|_||", ansi::normal_blue_foreground);
	for (int i = 0; i < 53; i++) os << ' ';
	os << ansi::color("   |_|_||| | | | | ||_|_||", ansi::normal_red_foreground) << std::endl;
	os << ansi::color("  /___|_|| | | | | ||__|__\\", ansi::normal_blue_foreground);
	for (int i = 0; i < 52; i++) os << ' ';
	os << ansi::color("  /___|_|| | | | | ||__|__\\", ansi::normal_red_foreground) << std::endl;
	os << ansi::color(" |_|_|_||| | | | | ||_|_|__|", ansi::normal_blue_foreground);
	for (int i = 0; i < 51; i++) os << ' ';
	os << ansi::color(" |_|_|_||| | | | | ||_|_|__|", ansi::normal_red_foreground) << std::endl;
	os << ansi::color(" ||_|_|_|| | | | | ||_|_|_||", ansi::normal_blue_foreground);
	for (int i = 0; i < 51; i++) os << ' ';
	os << ansi::color(" ||_|_|_|| | | | | ||_|_|_||", ansi::normal_red_foreground) << std::endl << std::endl;

	std::string blueHp = std::to_string(game.bluePlayer().base().hp()) + "hp",
			redHp = std::to_string(game.redPlayer().base().hp()) + "hp";
	os << "            " << ansi::color(blueHp, ansi::normal_blue_foreground);
	for (int i = 0; i < 72 - blueHp.size() - redHp.size(); i++)
		std::cout << ' ';
	os << "            " << ansi::color(redHp, ansi::normal_red_foreground) << std::endl;

	/* GOLD */
	std::string blueGold = std::to_string(game.bluePlayer().gold()) + 'g', redGold =
			std::to_string(game.redPlayer().gold()) + 'g';
	os << "Gold: " << ansi::color(blueGold, ansi::normal_yellow_foreground);
	for (int i = 0; i < 97 - blueGold.size() - redGold.size(); i++)
		std::cout << ' ';
	os << "Gold: " << ansi::color(redGold, ansi::normal_yellow_foreground) << std::endl;

	/* PLAYGROUND */
	/* top */
	os << (char) 218;
	for (int i = 1; i < 108; i++)
		os << (char) (i % 9 ? 196 : 194);
	os << (char) 191 << std::endl;
	/* line 1 */
	os << '|';
	for (int i = 0; i < 12; i++) {
		os << ' ';
		if (game.playground().field()[i] != nullptr) {
			std::string name = game.playground().field()[i]->className();
			name.erase(name.begin() + 5, name.end());
			name += '.';
			if (game.playground().field()[i]->isOwnedBy(game.bluePlayer()))
				os << ansi::color(name, ansi::normal_blue_foreground);
			else
				os << ansi::color(name, ansi::normal_red_foreground);
		} else
			os << "      ";
		os << ' ' << '|';
	}
	os << std::endl;
	/* line 2 */
	os << '|';
	for (int i = 0; i < 12; i++) {
		os << ' ';
		if (game.playground().field()[i] != nullptr) {
			std::string hp = std::to_string(game.playground().field()[i]->hp());
			for (int j = 0; j < (4 - hp.size()) / 2; j++) os << ' ';
			os << hp << "hp";
			for (int j = 0; j < (4 - hp.size()) / 2.; j++) os << ' ';
		} else
			os << "      ";
		os << ' ' << '|';
	}
	os << std::endl;
	/* bottom */
	os << (char) 192;
	for (int i = 1; i < 108; i++)
		os << (char) (i % 9 ? 196 : 193);
	os << (char) 217 << std::endl;

	/* UNITS */
	os << "      | 1: Soldier | 2: Archer | 3: Catapult |" << std::endl
	   << "price |     10     |     12    |      20     |" << std::endl
	   << "   hp |     10     |      8    |      12     |" << std::endl
	   << "  atk |      4     |      3    |       6     |" << std::endl
	   << "range |      1     |   2 to 4  |   2-3 & 3-4 |" << std::endl;
	return os;
}