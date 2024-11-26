//
// Created by plushjill on 03.11.2024.
//

#ifndef SNAKE_GAME_GAME_STATE_HPP
#define SNAKE_GAME_GAME_STATE_HPP

#include "snake.hpp"
#include "game_player.hpp"

class GameState {
private:
    int m_state_order = 0;
    std::vector<Snake> m_snakes = {};
    std::vector<CoordPoint> m_foods = {};
    std::vector<GamePlayer> m_game_players = {};

public:
    GameState(
            int state_order,
            const std::vector<Snake>& snakes,
            const std::vector<CoordPoint>& foods,
            const std::vector<GamePlayer>& game_players
            );
    [[nodiscard]] const std::vector<GamePlayer> &get_game_players() const;
    [[nodiscard]] const std::vector<CoordPoint> &get_foods() const;
    [[nodiscard]] const std::vector<Snake> &get_snakes() const;
    [[nodiscard]] int get_state_order() const;
    [[nodiscard]] std::shared_ptr<Snake> get_snake(int snake_id);
    void set_game_players(const std::vector<GamePlayer> &game_players);
    void set_foods(const std::vector<CoordPoint> &foods);
    void set_snakes(const std::vector<Snake> &snakes);
    void set_state_order(int state_order);
};


#endif //SNAKE_GAME_GAME_STATE_HPP
