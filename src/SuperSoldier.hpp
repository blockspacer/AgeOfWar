#ifndef AGEOFWAR_SUPERSOLDIER_HPP
#define AGEOFWAR_SUPERSOLDIER_HPP

#include "Unit.hpp"

class Soldier;

class SuperSoldier : public Unit {
public:
	SuperSoldier(const Soldier &soldier);
	explicit SuperSoldier(unsigned int hp);
	~SuperSoldier() override = default;

	/* Behavior */
	/**
	 * Effectue l'action correspondante à la phase passé en paramètre.
	 * @param phase numéro de la phase à jouer.
	 * @param playground contexte dans lequel est effectué l'action.
	 * @param player joueur qui possède l'unité qui effectue l'action.
	 */
	void action(unsigned int phase, Playground &playground, Player &owner) override;

	/* Display */
	std::string className() const override {
		return "SuperSoldier";
	};
};


#endif