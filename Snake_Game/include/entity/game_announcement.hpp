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
    std::vector<GamePlayer> players_;
    GameConfig config_;
    bool can_join_;
    std::string game_name_;
};


#endif //SNAKE_GAME_GAME_ANNOUNCEMENT_HPP
