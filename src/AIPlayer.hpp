#ifndef AGEOFWAR_AIPLAYER_HPP
#define AGEOFWAR_AIPLAYER_HPP

#include "Player.hpp"

class AIPlayer : public Player {
public:
    explicit AIPlayer(Player::Side side);
    AIPlayer(const Player &other);
    ~AIPlayer() override = default;

    void play(Playground &playground) override;
};

#endif
