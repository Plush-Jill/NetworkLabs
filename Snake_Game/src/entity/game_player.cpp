//
// Created by plushjill on 03.11.2024.
//

#include "include/entity/game_player.hpp"

const std::string &GamePlayer::get_name() const {
    return name_;
}

int GamePlayer::get_id() const {
    return id_;
}

const boost::asio::ip::address &GamePlayer::get_ip_address() const {
    return ip_address_;
}

void GamePlayer::set_ip_address(const boost::asio::ip::address &ip_address) {
    ip_address_ = ip_address;
}

boost::asio::ip::port_type GamePlayer::get_port() const {
    return port_;
}

void GamePlayer::set_port(boost::asio::ip::port_type port) {
    port_ = port;
}

NodeRole GamePlayer::get_node_role() const {
    return node_role_;
}

void GamePlayer::set_node_role(NodeRole node_role) {
    node_role_ = node_role;
}

PlayerType GamePlayer::get_type() const {
    return type_;
}

void GamePlayer::set_type(PlayerType type) {
    type_ = type;
}

int GamePlayer::get_score() const {
    return score_;
}

void GamePlayer::set_score(int score) {
    score_ = score;
}
