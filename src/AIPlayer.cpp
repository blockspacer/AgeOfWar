#include <algorithm>
#include "AIPlayer.hpp"

AIPlayer::AIPlayer(Player::Side side) : Player(side) {}

void AIPlayer::play(Playground &playground) {
    m_routine(playground);
}

