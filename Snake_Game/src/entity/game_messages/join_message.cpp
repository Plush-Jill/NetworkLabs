//
// Created by plushjill on 04.11.2024.
//

#include "include/entity/game_messages/join_message.hpp"

MessageType JoinMessage::get_message_type() {
    return MessageType::JoinMsg;
}

const std::string &JoinMessage::get_game_name() const {
    return game_name_;
}

void JoinMessage::set_game_name(const std::string &game_name) {
    game_name_ = game_name;
}

NodeRole JoinMessage::get_node_role() const {
    return node_role_;
}

void JoinMessage::set_node_role(NodeRole node_role) {
    node_role_ = node_role;
}

const std::string &JoinMessage::get_player_name() const {
    return player_name_;
}

void JoinMessage::set_player_name(const std::string &player_name) {
    player_name_ = player_name;
}

PlayerType JoinMessage::get_player_type() const {
    return player_type_;
}

void JoinMessage::set_player_type(PlayerType player_type) {
    player_type_ = player_type;
}
