//
// Created by plushjill on 04.11.2024.
//

#include "include/entity/game_messages/state_message.hpp"

MessageType StateMessage::get_message_type() {
    return MessageType::StateMsg;
}

const GameState &StateMessage::get_game_state() const {
    return game_state_;
}

void StateMessage::set_game_state(const GameState &game_state) {
    game_state_ = game_state;
}
