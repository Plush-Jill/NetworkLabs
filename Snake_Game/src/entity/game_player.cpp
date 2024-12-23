//
// Created by plushjill on 03.11.2024.
//

#include <utility>
#include "util/protobuf_manager.hpp"
#include "include/entity/game_player.hpp"

const std::string &GamePlayer::get_name() const {
    return m_name;
}

int GamePlayer::get_id() const {
    return m_id;
}

const boost::asio::ip::address &GamePlayer::get_ip_address() const {
    return m_ip_address;
}

void GamePlayer::set_ip_address(const boost::asio::ip::address &ip_address) {
    m_ip_address = ip_address;
}

boost::asio::ip::port_type GamePlayer::get_port() const {
    return m_port;
}

void GamePlayer::set_port(boost::asio::ip::port_type port) {
    m_port = port;
}

NodeRole GamePlayer::get_node_role() const {
    return m_node_role;
}

void GamePlayer::set_node_role(NodeRole node_role) {
    m_node_role = node_role;
}

PlayerType GamePlayer::get_type() const {
    return m_type;
}

void GamePlayer::set_type(PlayerType type) {
    m_type = type;
}

int GamePlayer::get_score() const {
    return m_score;
}

void GamePlayer::set_score(int score) {
    m_score = score;
}

GamePlayer::GamePlayer(
        std::string name,
        int id,
        boost::asio::ip::address  ip_address,
        boost::asio::ip::port_type port,
        NodeRole node_role,
        PlayerType type,
        int score) :
        m_name(std::move(name)),
        m_id(id),
        m_ip_address(std::move(ip_address)),
        m_port(port),
        m_node_role(node_role),
        m_type(type),
        m_score(score)
        {
}

GamePlayer::GamePlayer() :
        m_name("player1"),
        m_id(1),
        m_ip_address(boost::asio::ip::address::from_string("202.2.2.2")),
        m_port(5000),
        m_node_role(NodeRole::Master),
        m_type(PlayerType::Human),
        m_score(1488)
{

}

GamePlayer::GamePlayer(const snakes::GamePlayer& game_player_proto) :
    GamePlayer(
            game_player_proto.name(),
            game_player_proto.id(),
            boost::asio::ip::address::from_string(game_player_proto.ip_address()),
            game_player_proto.port(),
            ProtobufManager::get_node_role(game_player_proto.role()),
            ProtobufManager::get_type(game_player_proto.type()),
            game_player_proto.score()
            ) {
}

bool GamePlayer::operator==(const GamePlayer &other) const {
    bool result =
            m_name == other.m_name &&
            m_id == other.m_id &&
            m_ip_address == other.m_ip_address &&
            m_port == other.m_port &&
            m_node_role == other.m_node_role &&
            m_type == other.m_type &&
            m_score == other.m_score;

    return result;
}
