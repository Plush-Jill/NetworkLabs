//
// Created by plushjill on 29.10.2024.
//

#ifndef SNAKE_GAME_GAME_FIELD_CONTROLLER_HPP
#define SNAKE_GAME_GAME_FIELD_CONTROLLER_HPP
#include <cstddef>
#include "include/entity/snake.hpp"
#include <vector>
#include <chrono>


class GameFieldController {
private:
    size_t field_width_;
    size_t field_height_;
    size_t tick_count_;
    std::chrono::milliseconds tick_time_ {1000};
    std::vector<Snake> snakes_;
};


#endif //SNAKE_GAME_GAME_FIELD_CONTROLLER_HPP
