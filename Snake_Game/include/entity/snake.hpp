//
// Created by plushjill on 03.11.2024.
//

#ifndef SNAKE_GAME_SNAKE_HPP
#define SNAKE_GAME_SNAKE_HPP
#include <vector>
#include <set>
#include "snake_segment.hpp"
#include "include/enum/snake_state.hpp"
#include "include/enum/direction.hpp"

class Snake {
private:
    int id_;
    SnakeSegment head_;
    std::vector<SnakeSegment> segments_;
    SnakeState snake_state_ = SnakeState::Alive;
    Direction head_direction_;

public:
    [[nodiscard]] int get_id() const;
    [[nodiscard]] const SnakeSegment &get_head() const;
    [[nodiscard]] const std::vector<SnakeSegment> &get_segments() const;
    [[nodiscard]] SnakeState get_snake_state() const;
    [[nodiscard]] Direction get_head_direction() const;
    void set_id(int id);
    void set_head(const SnakeSegment &head);
    void set_segments(const std::vector<SnakeSegment> &segments);
    void set_snake_state(SnakeState snake_state);
    void set_head_direction(Direction head_direction);
};


#endif //SNAKE_GAME_SNAKE_HPP
