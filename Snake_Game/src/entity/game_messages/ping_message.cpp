//
// Created by plushjill on 04.11.2024.
//

#include "include/entity/game_messages/ping_message.hpp"

MessageType PingMessage::get_message_type() {
    return MessageType::PingMsg;
}
