#ifndef AGEOFWAR_GAME_HPP
#define AGEOFWAR_GAME_HPP

#include "Playground.hpp"
#include "Player.hpp"
#include "Serializable.hpp"

class Player;

class Game : public Serializable {
private:
    const char *m_save;
    bool m_running;

    unsigned int m_turnNo;
    Player &m_bluePlayer, &m_redPlayer;
    Playground m_playground;

public:
    Game();
	Game(const char *m_save, bool AI = false);
    ~Game() override = default;

    unsigned int turnNo() const {
        return m_turnNo;
    }

    Player &bluePlayer() {
        return m_bluePlayer;
    }
    const Player &bluePlayer() const {
        return m_bluePlayer;
    }

    Playground &playground() {
        return m_playground;
    }
    const Playground &playground() const {
        return m_playground;
    }

    Player &redPlayer() {
        return m_redPlayer;
    }
    const Player &redPlayer() const {
        return m_redPlayer;
    }

    void run();
    void turn();

    void stop() {
        m_running = false;
    }

    /* Serializable */
    void serialize(std::ostream &os) const override;
    void deserialize(std::istream &is) override;
};

std::ostream &operator<<(std::ostream& os, const Game &g);

#endif
