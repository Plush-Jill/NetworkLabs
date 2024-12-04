//
// Created by plushjill on 29.10.2024.
//

#ifndef SNAKE_GAME_GAME_FIELD_CONTROLLER_HPP
#define SNAKE_GAME_GAME_FIELD_CONTROLLER_HPP
#include <cstddef>
#include "include/entity/snake.hpp"
#include "model/game_field.hpp"
#include <vector>
#include <chrono>


class GameFieldController {
private:
    std::shared_ptr<GameField> m_game_field;
};


#endif //SNAKE_GAME_GAME_FIELD_CONTROLLER_HPP
