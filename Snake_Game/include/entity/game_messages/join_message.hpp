//
// Created by plushjill on 04.11.2024.
//

#ifndef SNAKE_GAME_JOIN_MESSAGE_HPP
#define SNAKE_GAME_JOIN_MESSAGE_HPP


#include <string>
#include "abstract_message.hpp"
#include "enum/player_type.hpp"
#include "enum/node_role.hpp"

class JoinMessage : AbstractMessage{
private:
    PlayerType player_type_;
    std::string player_name_;
    std::string game_name_;
    NodeRole node_role_;

public:
    [[nodiscard]] const std::string &get_game_name() const;
    [[nodiscard]] NodeRole get_node_role() const;
    [[nodiscard]] const std::string &get_player_name() const;
    [[nodiscard]] PlayerType get_player_type() const;
    MessageType get_message_type() override;
    void set_game_name(const std::string &game_name);
    void set_node_role(NodeRole node_role);
    void set_player_name(const std::string &player_name);
    void set_player_type(PlayerType player_type);
};


#endif //SNAKE_GAME_JOIN_MESSAGE_HPP
