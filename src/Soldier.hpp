#ifndef AGEOFWAR_INFANTRYMAN_HPP
#define AGEOFWAR_INFANTRYMAN_HPP

#include "RecruitableUnit.hpp"

class Soldier : public RecruitableUnit {
private:
    bool m_retryAttack;

public:
    Soldier();
    explicit Soldier(unsigned int hp);
    ~Soldier() override = default;

    /* Behavior */
    /**
	 * Effectue l'action correspondante à la phase passé en paramètre.
	 * @param phase numéro de la phase à jouer.
	 * @param playground contexte dans lequel est effectué l'action.
	 * @param player joueur qui possède l'unité qui effectue l'action.
	 */
    void action(unsigned int phase, Playground &playground, Player &owner) override;

    /**
	 * Effectué quand l'unité tué une autre unité.
     * Si l'unité tué est un Soldier alors this se transforme en SuperSoldier.
	 * Par défaut, ajoute seulement la somme convenu au joueur possédant l'unité.
	 */
    void onKill(Unit &killed, Playground &playground, Player &owner) override;

    /* Display */
    std::string className() const override {
        return "Soldier";
    };
    
};

#endif
