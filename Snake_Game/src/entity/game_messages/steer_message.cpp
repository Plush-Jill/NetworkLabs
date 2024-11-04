//
// Created by plushjill on 04.11.2024.
//

#include "include/entity/game_messages/steer_message.hpp"

MessageType SteerMessage::get_message_type() {
    return MessageType::SteerMsg;
}

Direction SteerMessage::get_direction() const {
    return direction_;
}

void SteerMessage::set_direction(Direction direction) {
    direction_ = direction;
}
