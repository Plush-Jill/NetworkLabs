//
// Created by plushjill on 26.11.2024.
//

#include "include/controller/snake_controller.hpp"

void SnakeController::turn_head(SnakeController::HeadDirection direction) {
    if (m_snake == nullptr) {
        return;
    }
    Direction direction_to_turn;
    switch (direction) {

        case HeadDirection::Up:
            direction_to_turn = Direction::Up;
            break;
        case HeadDirection::Down:
            direction_to_turn = Direction::Down;
            break;
        case HeadDirection::Left:
            direction_to_turn = Direction::Left;
            break;
        case HeadDirection::Right:
            direction_to_turn = Direction::Right;
            break;
    }

    Coord second_snake_segment {m_snake->get_head_coord() + m_snake->get_segments()->at(1)};
    Direction back_direction {second_snake_segment.get_relative_direction_from(
            m_snake->get_head_coord())};

    if (m_snake->get_head_direction() != back_direction) {
        m_snake->set_head_direction(direction_to_turn);
    }

}

SnakeController::SnakeController(
        std::shared_ptr<Snake> snake,
        QObject *parent)
        : QObject(parent), m_snake(std::move(snake)) {}

int SnakeController::get_snake_id() {
    return m_snake->get_id();
}
