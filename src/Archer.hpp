#ifndef AGEOFWAR_ARCHER_HPP
#define AGEOFWAR_ARCHER_HPP

#include "Unit.hpp"
#include "RecruitableUnit.hpp"

class Archer : public RecruitableUnit {
public:
	Archer();
	explicit Archer(unsigned int hp);
	~Archer() override = default;

	/* Behavior */
	/**
	 * Effectue l'action correspondante à la phase passé en paramètre.
	 * @param phase numéro de la phase à jouer.
	 * @param playground contexte dans lequel est effectué l'action.
	 * @param player joueur qui possède l'unité qui effectue l'action.
	 */
	void action(unsigned int phase, Playground &playground, Player &owner);

	std::string className() const override {
		return "Archer";
	};
};


#endif
