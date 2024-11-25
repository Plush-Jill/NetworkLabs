//
// Created by plushjill on 03.11.2024.
//

#include "include/entity/game_announcement.hpp"

GameAnnouncement::GameAnnouncement(
        const std::vector<GamePlayer>& players,
        const GameConfig& config,
        bool can_join,
        const std::string& game_name) {
    m_game_name = game_name;
    m_can_join = can_join;
    m_config = config;
    m_players = players;
}

const std::vector<GamePlayer> &GameAnnouncement::get_players() const {
    return m_players;
}

const std::string &GameAnnouncement::get_game_name() const {
    return m_game_name;
}

const GameConfig &GameAnnouncement::get_config() const {
    return m_config;
}

bool GameAnnouncement::is_can_join() const {
    return m_can_join;
}

GameAnnouncement::GameAnnouncement() {
    m_players = std::vector<GamePlayer>(0);
    m_config = GameConfig();
    m_can_join = false;
    m_game_name = "unnamed";
}
