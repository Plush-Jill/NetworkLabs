//
// Created by plushjill on 25.11.2024.
//
#include <utility>

#include "exceptions_all.hpp"
#include "include/model/game_field.hpp"

GameField::GameField(std::shared_ptr<GameConfig> game_config, std::shared_ptr<GameState> game_state) :
    m_game_config(std::move(game_config)),
    m_game_state(std::move(game_state))
    {


}

void GameField::move_snakes() {
    throw IncompleteCodeException();
    for (Snake& snake : *m_game_state->get_snakes()) {
        Coord shift = get_shift_by_direction(snake.get_head_direction());
        Coord next_head_point = snake.get_head_coord() + shift;

        bool is_contains_food = is_cell_contains_food(next_head_point);
        bool is_contains_snake = is_point_contains_snake(next_head_point);

        if (is_contains_food) {
            snake.grow();
        } else if (is_contains_snake) {
            destroy_snake(snake);
        } else {
            for (Coord segment: *snake.get_segments()) {
                // сдвинуть голову, затем поменять сдвиг второй клетки,
                // затем поменять сдвиги всех остальных
            }
        }
    }
}

std::chrono::milliseconds GameField::get_state_delay_ms() const {
    return m_game_config->get_state_delay_ms();
}

int GameField::get_food_static() const {
    return m_game_config->get_food_static();
}

int GameField::get_field_height() const {
    return m_game_config->get_field_height();
}

int GameField::get_field_width() const {
    return m_game_config->get_field_width();
}

Coord GameField::get_coords_by_field_size_module(const Coord &coord) const {
    return Coord(num_by_size_module(coord.get_x(), get_field_width())
                      , num_by_size_module(coord.get_y(), get_field_height()));
}

int GameField::num_by_size_module(int num, int module) {
    int result = num % module;
    return result < 0 ? result + module : result;
}

Coord GameField::get_shift_by_direction(Direction direction) {
    switch (direction) {

        case Direction::Up:
            return Coord(-1, 0);
        case Direction::Down:
            return Coord(1, 0);
        case Direction::Left:
            return Coord(0, -1);
        case Direction::Right:
            return Coord(0, 1);
        default: throw std::invalid_argument("invalid direction");
    }
}

bool GameField::is_cell_contains_food(const Coord &cell) const {
    return std::ranges::any_of(*m_game_state->get_foods(), [cell](const Coord& point) {
       return point == cell;
    });
}

std::shared_ptr<GameState> GameField::get_game_state() const {
    return m_game_state;
}

CellContent GameField::get_cell_content(const Coord &coord) const {
    if (is_cell_contains_food(coord)) {
        return CellContent::Food;
    } else if (is_cell_contains_snake(coord)) {
        return CellContent::Snake;
    }

    return CellContent::Empty;
}

bool GameField::is_cell_contains_snake(const Coord &cell) const {
    for (const Snake& snake : *(m_game_state->get_snakes())) {
        Coord previous_cell {snake.get_head_coord()};
        if (cell == previous_cell) {
            return true;
        }

        for (const Coord& segment : *(snake.get_segments())) {
            Coord next_cell = get_coords_by_field_size_module((previous_cell + segment));
            if (cell == next_cell) {
                return true;
            }

            previous_cell = next_cell;
        }
    }

    return false;
}
