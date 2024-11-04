//
// Created by plushjill on 03.11.2024.
//

#ifndef SNAKE_GAME_SNAKE_STATE_HPP
#define SNAKE_GAME_SNAKE_STATE_HPP

enum class SnakeState {
    Alive,  // Змея управляется игроком
    Zombie // Змея принадлежала игроку, который вышел из игры, она продолжает движение куда глаза глядят
};

#endif //SNAKE_GAME_SNAKE_STATE_HPP
