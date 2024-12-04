//
// Created by plushjill on 26.11.2024.
//

#ifndef SNAKE_GAME_GAME_MODEL_HPP
#define SNAKE_GAME_GAME_MODEL_HPP
#include "game_field.hpp"
#include "entity/game_config.hpp"
#include "entity/game_state.hpp"


class GameModel {
private:
    std::shared_ptr<GameConfig> m_game_config;
    std::shared_ptr<GameField> m_game_field;


public:

};


#endif //SNAKE_GAME_GAME_MODEL_HPP
