#ifndef AGEOFWAR_AIPLAYER_HPP
#define AGEOFWAR_AIPLAYER_HPP

#include "Player.hpp"

class AIPlayer : public Player {
private:
    void (*m_routine)(Playground &);

public:

    explicit AIPlayer(Player::Side side);
    ~AIPlayer() = default;

    void play(Playground &playground) override;
};

#endif
