//
// Created by plushjill on 04.11.2024.
//

#include "include/entity/game_messages/game_message.hpp"

std::shared_ptr<AbstractMessage> GameMessage::get_message() const {
    return message_;
}

void GameMessage::set_message(std::shared_ptr<AbstractMessage> &message) {
    message_ = message;
}

int GameMessage::get_msg_seq() const {
    return msg_seq_;
}

void GameMessage::set_msg_seq(int msg_seq) {
    msg_seq_ = msg_seq;
}

int GameMessage::get_receiver_id() const {
    return receiver_id_;
}

void GameMessage::set_receiver_id(int receiver_id) {
    receiver_id_ = receiver_id;
}

int GameMessage::get_sender_id() const {
    return sender_id_;
}

void GameMessage::set_sender_id(int sender_id) {
    sender_id_ = sender_id;
}
