//
// Created by plushjill on 04.11.2024.
//

#include "include/entity/game_messages/ack_message.hpp"

MessageType AckMessage::get_message_type() {
    return MessageType::AckMsg;
}
