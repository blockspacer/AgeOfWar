#ifndef AGEOFWAR_CATAPULT_HPP
#define AGEOFWAR_CATAPULT_HPP

#include "RecruitableUnit.hpp"

class Catapult : public RecruitableUnit {
private:
	bool m_canMove;

public:
    Catapult();
	explicit Catapult(unsigned int hp);
    ~Catapult() override = default;

	/* Behavior */
	/**
	 * Effectue l'action correspondante à la phase passé en paramètre.
	 * @param phase numéro de la phase à jouer.
	 * @param playground contexte dans lequel est effectué l'action.
	 * @param player joueur qui possède l'unité qui effectue l'action.
	 */
	void action(unsigned int phase, Playground &playground, Player &owner) override;

	std::string className() const override {
		return "Catapult";
	};
};


#endif
