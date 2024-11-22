//
// Created by plushjill on 03.11.2024.
//

#include <utility>

#include "include/entity/snake.hpp"

const std::vector<CoordPoint> &Snake::get_segments() const {
    return m_segments;
}

void Snake::set_segments(const std::vector<CoordPoint> &segments) {
    m_segments = segments;
}

SnakeState Snake::get_snake_state() const {
    return m_snake_state;
}

void Snake::set_snake_state(SnakeState snake_state) {
    m_snake_state = snake_state;
}

int Snake::get_id() const {
    return m_id;
}

void Snake::set_id(int id) {
    m_id = id;
}

Direction Snake::get_head_direction() const {
    return m_head_direction;
}

void Snake::set_head_direction(Direction head_direction) {
    m_head_direction = head_direction;
}

Snake::Snake(
        int id,
        std::vector<CoordPoint> segments,
        SnakeState snake_state,
        Direction head_direction) :
            m_id (id),
            m_segments (std::move(segments)),
            m_snake_state (snake_state),
            m_head_direction (head_direction)
         {

}
