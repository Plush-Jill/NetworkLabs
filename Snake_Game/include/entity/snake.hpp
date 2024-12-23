//
// Created by plushjill on 03.11.2024.
//

#ifndef SNAKE_GAME_SNAKE_HPP
#define SNAKE_GAME_SNAKE_HPP
#include <vector>
#include <set>
#include "include/enum/snake_state.hpp"
#include "include/enum/direction.hpp"
#include "coord_point.hpp"
#include <stack>


class Snake {
private:
    int m_id = 0;
    std::shared_ptr<std::deque<Coord>> m_segments = {};
    SnakeState m_snake_state = SnakeState::Alive;
    Direction m_head_direction = Direction::Up;

public:
    Snake() = default;
    Snake (
            int id,
            std::shared_ptr<std::deque<Coord>> segments,
            SnakeState snake_state,
            Direction head_direction
    );
    [[nodiscard]] int get_id() const;
    [[nodiscard]] std::shared_ptr<std::deque<Coord>> get_segments() const;
    [[nodiscard]] SnakeState get_snake_state() const;
    [[nodiscard]] Direction get_head_direction() const;
    [[nodiscard]] Coord get_head_coord() const;
    void set_id(int id);
    void set_segments(const std::shared_ptr<std::deque<Coord>> segments);
    void set_snake_state(SnakeState snake_state);
    void set_head_direction(Direction head_direction);
    void grow();
};


#endif //SNAKE_GAME_SNAKE_HPP
