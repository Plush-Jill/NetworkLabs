//
// Created by plushjill on 03.11.2024.
//

#include "include/entity/snake.hpp"

const SnakeSegment &Snake::get_head() const {
    return head_;
}

void Snake::set_head(const SnakeSegment &head) {
    head_ = head;
}

const std::vector<SnakeSegment> &Snake::get_segments() const {
    return segments_;
}

void Snake::set_segments(const std::vector<SnakeSegment> &segments) {
    segments_ = segments;
}

SnakeState Snake::get_snake_state() const {
    return snake_state_;
}

void Snake::set_snake_state(SnakeState snake_state) {
    snake_state_ = snake_state;
}

int Snake::get_id() const {
    return id_;
}

void Snake::set_id(int id) {
    id_ = id;
}

Direction Snake::get_head_direction() const {
    return head_direction_;
}

void Snake::set_head_direction(Direction head_direction) {
    head_direction_ = head_direction;
}
