#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "Base.hpp"

class Unit;

class RecruitableUnit;

class Playground;

class Player {
public:
	enum class Side : int {
		blue = 1, red = -1
	};

private:
	Side m_side;
	unsigned int m_gold;
	Base m_base;
	std::vector<Unit *> m_units;

	/* Behavior */
	/**
	 * Recrute une nouvelle unité recrutable passé en paramètre.
	 * @param unit unité à recruté.
	 */
	void recruit(RecruitableUnit &unit);

public:
	/**
	 * Constructeur de la classe.
	 * @param side désigne le côté du joueur.
	 */
	Player(Side side);
	Player(Side side, unsigned int gold);
	~Player() = default;

	/* Accessors & Mutators */
	Side side() const;

	unsigned int &gold();
	unsigned int const &gold() const;

	Base &base();
	Base const &base() const;

	std::vector<Unit *> &units();
	std::vector<Unit *> const &units() const;

	/* Behavior */
	void turn(Playground &playground);
	/**
	 * Routine de jeu pour le joueur.
	 * @param playground est le contexte qui permet au joueur de 'connaître' son environnement.
	 */
	virtual void play(Playground &playground);
};

/**
 * Renvoie l'adversaire.
 * @param rhs
 * @return l'adversaire.
 */
Player::Side operator!(Player::Side rhs);

/**
 * Calcule la position de la base en fonction de la valeur de l'énumration.
 * On applique un bitmask 0b10110 (22 en décimal) et on décale vers la droite une fois.
 * (22 car l'on veut pouvoir avoir soit 0 soit un multiple de 11 or 11 ne le permet pas puis on shift).
 * @param rhs
 * @return renvoie 0 si rhs est égale à Player::Side::blue et 11 si rhs est égale Player::Side::red.
 */
unsigned int operator~(Player::Side rhs);

/**
 * Surcharge de l'opérator de dérérencement sur le type enum class Player::Side.
 * Renvoie la valeur numérique de l'enum directement statiquement caster en entier (std::size_t).
 * @param rhs valeur à 'opérer'
 * @return renvoie la valeur numérique de l'enum directement statiquement caster en entier (std::size_t).
 */
std::size_t operator*(Player::Side rhs);

#include "Player.inl"

#endif
