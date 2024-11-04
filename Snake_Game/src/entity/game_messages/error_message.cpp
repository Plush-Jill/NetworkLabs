//
// Created by plushjill on 04.11.2024.
//

#include "include/entity/game_messages/error_message.hpp"

MessageType ErrorMessage::get_message_type() {
    return MessageType::ErrorMsg;
}

const std::string &ErrorMessage::get_error_message() const {
    return error_message_;
}

void ErrorMessage::set_error_message(const std::string &error_message) {
    error_message_ = error_message;
}
