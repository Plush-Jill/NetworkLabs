//
// Created by plushjill on 04.11.2024.
//

#include "include/entity/game_messages/role_change_message.hpp"

MessageType RoleChangeMessage::get_message_type() {
    return MessageType::RoleChangeMsg;
}

NodeRole RoleChangeMessage::get_sender_role() const {
    return sender_role_;
}

void RoleChangeMessage::set_sender_role(NodeRole sender_role) {
    sender_role_ = sender_role;
}

NodeRole RoleChangeMessage::get_receiver_role() const {
    return receiver_role_;
}

void RoleChangeMessage::set_receiver_role(NodeRole receiver_role) {
    receiver_role_ = receiver_role;
}
