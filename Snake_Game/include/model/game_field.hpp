//
// Created by plushjill on 25.11.2024.
//

#ifndef SNAKE_GAME_GAME_FIELD_HPP
#define SNAKE_GAME_GAME_FIELD_HPP


#include "entity/game_config.hpp"
#include "entity/snake.hpp"
#include "entity/game_state.hpp"

class GameField {
private:

    std::shared_ptr<GameConfig> m_game_config;
    std::shared_ptr<GameState> m_game_state;

    static CoordPoint get_shift_by_direction(Direction direction);
    static int num_by_size_module(int num, int module);
    [[nodiscard]] CoordPoint get_coords_by_field_size_module(
            const CoordPoint& coord) const;

    void destroy_snake(Snake snake);
    bool is_point_contains_snake(const CoordPoint& coord);

public:

    GameField() = default;
    GameField(std::shared_ptr<GameConfig> game_config, std::shared_ptr<GameState> game_state);

    bool is_cell_contains_food(const CoordPoint& cell);
    [[nodiscard]] std::chrono::milliseconds get_state_delay_ms() const;
    [[nodiscard]] int get_food_static() const;
    [[nodiscard]] int get_field_height() const;
    [[nodiscard]] int get_field_width() const;
    [[nodiscard]] std::shared_ptr<GameState> get_game_state() const;

    void move_snakes();
};


#endif //SNAKE_GAME_GAME_FIELD_HPP
