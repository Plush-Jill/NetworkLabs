//
// Created by plushjill on 04.11.2024.
//

#ifndef SNAKE_GAME_ACK_MESSAGE_HPP
#define SNAKE_GAME_ACK_MESSAGE_HPP


#include "abstract_message.hpp"

class AckMessage : AbstractMessage{
public:
    MessageType get_message_type() override;

};


#endif //SNAKE_GAME_ACK_MESSAGE_HPP
