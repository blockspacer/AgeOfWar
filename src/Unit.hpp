#ifndef AGEOFWAR_UNIT_HPP
#define AGEOFWAR_UNIT_HPP

#include "Entity.hpp"

#include "Range.hpp"
#include "AreaOfEffect.hpp"

class Player;
class Playground;

class Unit : public Entity {
public:
	enum class Type {
		soldier, archer, catapult, super_soldier
	};

private:
	/* Stats */
	unsigned int m_atk;
	Range m_range;
	AreaOfEffect m_areaOfEffect;

	/* Behavior */
	/**
	 * Attaque une entité donné en paramètre et retourne true si les points de vie de l'entité tombent à 0, false sinon.
	 * @param entity l'entité visée par l'attaque.
	 * @return retourne true si les points de vie de l'entité tombent à 0, false sinon.
	 */
	bool attack(Entity &entity) const;

protected:
	/**
	 * Constructeur de l'unité qui prend toutes les caractériques d'une unité. Étant donné que Unit est abstrait ce
	 * constructeur sert pour les classes dérivés de Unit.
	 * @param hp point de vie de l'unité.
	 * @param atk attaque de l'unité.
	 * @param range portée de l'unité.
	 * @param areaOfEffect zone d'attaque de l'unité.
	 */
	Unit(unsigned int hp, unsigned int atk, const Range &range, const AreaOfEffect &areaOfEffect);
	Unit(const Unit &other);

	/* Behavior */
	/**
	 * Fonction d'attaque à utiliser dans Unit::action(Playground &, const Player &). Sélectionne le/les ennemi(s) à
	 * attaquer puis attaque. Retourne true si l'unité parvient à attaquer une unité, false sinon.
	 * @param playground contexte dans lequel est effectué l'attaque.
	 * @param owner joueur qui possède l'unité qui effectue l'attaque.
	 * @return vrai si l'unité parvient à attaquer une autre unité, faux sinon.
	 */
	bool attack(Playground &playground, Player &owner);
	/**
	 * Fonction de déplacement à utiliser dans Unit::action(unsigned int, Playground &, const Player &). Ce déplace si
	 * cela est possible. Retourne true si l'unité parvient à se déplacer, false sinon.
	 * @param playground contexte dans lequel est effectué le déplacement.
	 * @param player joueur qui possède l'unité qui effectue le déplacement.
	 * @return true si l'unité parvient à déplacer, false sinon.
	 */
	bool moveForward(Playground &playground, const Player &owner);

	/* Reactive behavior */
	/**
	 * Effectué quand l'unité tué une autre unité.
	 * Par défaut, ajoute seulement la somme convenu au joueur possédant l'unité.
	 */
	virtual void onKill(Unit &killed, Playground &playground, Player &owner);

public:
	~Unit() override = default;

	/* Informations */
	/**
	 * Retourne l'itérateur qui pointe sur this dans le tableau stocké dans le terrain de jeu.
	 * @param playground terrain de jeu.
	 * @return retourne l'itérateur qui pointe sur this.
	 */
	Unit **iterator(Playground &playground) const;
	/**
	 * Retourne si oui ou non this est un unité ennemi du joueur passé en paramètre.
	 * @param player joueur.
	 * @return retourne si oui ou non this est un unité ennemi du joueur passé en paramètre.
	 */
	bool isOwnedBy(const Player &owner) const;

	/* Accessors */
	unsigned int atk() const;
	const Range &range() const;
	const AreaOfEffect &areaOfEffect() const;

	/* Behavior */
	/**
	 * Effectue l'action correspondante à la phase passé en paramètre.
	 * @param phase numéro de la phase à jouer.
	 * @param playground contexte dans lequel est effectué l'action.
	 * @param player joueur qui possède l'unité qui effectue l'action.
	 */
	virtual void action(unsigned int phase, Playground &playground, Player &owner) = 0;

	/* Reactive behavior */
	/**
 * Effectué quand l'unité est tué.
 * Par défaut, suicide l'objet.
 */
	virtual void onKilled(Playground &playground, Player &owner);

	/* Display */
	virtual std::string className() const {
		return "Unit";
	};
};

#include "Unit.inl"

#endif
