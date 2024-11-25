//
// Created by plushjill on 25.11.2024.
//

#ifndef SNAKE_GAME_GAME_FIELD_HPP
#define SNAKE_GAME_GAME_FIELD_HPP


#include "entity/game_config.hpp"
#include "entity/snake.hpp"

class GameField {
private:

    const GameConfig m_game_config;
    std::vector<Snake> m_snakes;
    std::set<CoordPoint> m_food_points;

    static CoordPoint get_shift_by_direction(Direction direction);
    static int num_by_size_module(int num, int module);
    [[nodiscard]] CoordPoint get_coords_by_field_size_module(
            const CoordPoint& coord) const;

    void destroy_snake(Snake snake);
    bool is_point_contains_food(const CoordPoint& coord);
    bool is_point_contains_snake(const CoordPoint& coord);

public:

    GameField() = default;
    GameField(const GameConfig& game_config, std::vector<Snake> &snakes);

    [[nodiscard]] const std::chrono::milliseconds &get_state_delay_ms() const;
    [[nodiscard]] int get_food_static() const;
    [[nodiscard]] int get_field_height() const;
    [[nodiscard]] int get_field_width() const;

    void move_snakes();
};


#endif //SNAKE_GAME_GAME_FIELD_HPP
