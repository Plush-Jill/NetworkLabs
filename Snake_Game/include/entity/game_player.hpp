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
    std::string name_;
    int id_;
    boost::asio::ip::address ip_address_;
    boost::asio::ip::port_type port_;
    NodeRole node_role_;
    PlayerType type_;
    int score_;

public:
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
};


#endif //SNAKE_GAME_GAME_PLAYER_HPP
