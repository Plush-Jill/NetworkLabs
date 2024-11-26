//
// Created by plushjill on 25.11.2024.
//
#include "exceptions_all.hpp"
#include "include/model/game_field.hpp"

GameField::GameField(const GameConfig& game_config, std::vector<Snake>& snakes) :
    m_game_config(game_config),
    m_snakes(snakes)
    {


}

void GameField::move_snakes() {
    throw IncompleteCodeException();
    for (Snake& snake : m_snakes) {
        CoordPoint shift = get_shift_by_direction(snake.get_head_direction());
        CoordPoint next_head_point = snake.get_head_coord() + shift;

        bool is_contains_food = is_point_contains_food(next_head_point);
        bool is_contains_snake = is_point_contains_snake(next_head_point);

        if (is_contains_food) {
            snake.grow();
        } else if (is_contains_snake) {
            destroy_snake(snake);
        } else {
            for (CoordPoint segment: snake.get_segments()) {
                // сдвинуть голову, затем поменять сдвиг второй клетки,
                // затем поменять сдвиги всех остальных
            }
        }
    }
}

const std::chrono::milliseconds &GameField::get_state_delay_ms() const {
    return m_game_config.get_state_delay_ms();
}

int GameField::get_food_static() const {
    return m_game_config.get_food_static();
}

int GameField::get_field_height() const {
    return m_game_config.get_field_height();
}

int GameField::get_field_width() const {
    return m_game_config.get_field_width();
}

CoordPoint GameField::get_coords_by_field_size_module(const CoordPoint &coord) const {
    return CoordPoint(num_by_size_module(coord.get_x(), get_field_width())
                      , num_by_size_module(coord.get_y(), get_field_height()));
}

int GameField::num_by_size_module(int num, int module) {
    int result = num % module;
    return result < 0 ? result + module : result;
}

CoordPoint GameField::get_shift_by_direction(Direction direction) {
    switch (direction) {

        case Direction::Up:
            return CoordPoint(-1, 0);
        case Direction::Down:
            return CoordPoint(1, 0);
        case Direction::Left:
            return CoordPoint(0, -1);
        case Direction::Right:
            return CoordPoint(0, 1);
        default: throw std::invalid_argument("invalid direction");
    }
}
