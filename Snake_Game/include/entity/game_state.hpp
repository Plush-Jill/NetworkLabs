//
// Created by plushjill on 03.11.2024.
//

#ifndef SNAKE_GAME_GAME_STATE_HPP
#define SNAKE_GAME_GAME_STATE_HPP

#include "snake.hpp"
#include "game_player.hpp"
#include "enum/cell_content.hpp"

class GameState {
private:
    int m_state_order = 0;
    std::shared_ptr<std::vector<Snake>> m_snakes = {};
    std::shared_ptr<std::vector<CoordPoint>> m_foods = {};
    std::shared_ptr<std::vector<GamePlayer>> m_game_players = {};

public:
    GameState(
            int state_order,
            std::shared_ptr<std::vector<Snake>> snakes,
            std::shared_ptr<std::vector<CoordPoint>> foods,
            std::shared_ptr<std::vector<GamePlayer>> game_players
            );
    [[nodiscard]] std::shared_ptr<std::vector<GamePlayer>> get_game_players() const;
    [[nodiscard]] std::shared_ptr<std::vector<CoordPoint>> get_foods() const;
    [[nodiscard]] std::shared_ptr<std::vector<Snake>> get_snakes() const;
    [[nodiscard]] int get_state_order() const;
    [[nodiscard]] std::shared_ptr<Snake> get_snake(int snake_id);
    void set_game_players(std::shared_ptr<std::vector<GamePlayer>> game_players);
    void set_foods(std::shared_ptr<std::vector<CoordPoint>> foods);
    void set_snakes(std::shared_ptr<std::vector<Snake>> snakes);
    void set_state_order(int state_order);
};


#endif //SNAKE_GAME_GAME_STATE_HPP
