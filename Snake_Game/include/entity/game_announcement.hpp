//
// Created by plushjill on 03.11.2024.
//

#ifndef SNAKE_GAME_GAME_ANNOUNCEMENT_HPP
#define SNAKE_GAME_GAME_ANNOUNCEMENT_HPP

#include "game_player.hpp"
#include "include/entity/game_config.hpp"
#include <vector>

class GameAnnouncement {
private:
    std::vector<GamePlayer> m_players;
    GameConfig m_config;
    bool m_can_join{};
    std::string m_game_name;

public:
    GameAnnouncement(const std::vector<GamePlayer>& players,
                     const GameConfig& config,
                     bool can_join,
                     const std::string& game_name);
    GameAnnouncement();

    [[nodiscard]] const std::vector<GamePlayer> &get_players() const;
    [[nodiscard]] const std::string &get_game_name() const;
    [[nodiscard]] const GameConfig &get_config() const;
    [[nodiscard]] bool is_can_join() const;
};


#endif //SNAKE_GAME_GAME_ANNOUNCEMENT_HPP
