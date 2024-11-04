//
// Created by plushjill on 04.11.2024.
//

#ifndef SNAKE_GAME_ROLE_CHANGE_MESSAGE_HPP
#define SNAKE_GAME_ROLE_CHANGE_MESSAGE_HPP


#include "abstract_message.hpp"
#include "enum/node_role.hpp"

class RoleChangeMessage : AbstractMessage{
private:
    NodeRole sender_role_;
    NodeRole receiver_role_;

public:
    MessageType get_message_type() override;

    [[nodiscard]] NodeRole get_sender_role() const;
    [[nodiscard]] NodeRole get_receiver_role() const;
    void set_sender_role(NodeRole sender_role);
    void set_receiver_role(NodeRole receiver_role);
};


#endif //SNAKE_GAME_ROLE_CHANGE_MESSAGE_HPP
