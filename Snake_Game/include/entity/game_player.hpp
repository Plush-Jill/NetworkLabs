//
// Created by plushjill on 03.11.2024.
//

#ifndef SNAKE_GAME_GAME_PLAYER_HPP
#define SNAKE_GAME_GAME_PLAYER_HPP

#include <string>
#include "include/enum/node_role.hpp"
#include "include/enum/player_type.hpp"
#include <boost/asio.hpp>


class GamePlayer {
private:
    std::string m_name;
    int m_id;
    boost::asio::ip::address m_ip_address;
    boost::asio::ip::port_type m_port;
    NodeRole m_node_role;
    PlayerType m_type;
    int m_score;

public:
    explicit GamePlayer(
        std::string name,
        int id,
        boost::asio::ip::address  ip_address,
        boost::asio::ip::port_type port,
        NodeRole node_role,
        PlayerType type,
        int score
        );

    GamePlayer();
    [[nodiscard]] const std::string &get_name() const;
    [[nodiscard]] int get_id() const;
    [[nodiscard]] const boost::asio::ip::address &get_ip_address() const;
    [[nodiscard]] boost::asio::ip::port_type get_port() const;
    [[nodiscard]] NodeRole get_node_role() const;
    [[nodiscard]] PlayerType get_type() const;
    [[nodiscard]] int get_score() const;
    void set_ip_address(const boost::asio::ip::address &ip_address);
    void set_port(boost::asio::ip::port_type port);
    void set_node_role(NodeRole node_role);
    void set_type(PlayerType type);
    void set_score(int score);

    bool operator==(const GamePlayer& other) {
        return true;
    }
};


#endif //SNAKE_GAME_GAME_PLAYER_HPP
