//Join
// Created by plushjill on 04.11.2024.
//

#ifndef SNAKE_GAME_DISCOVER_MESSAGE_HPP
#define SNAKE_GAME_DISCOVER_MESSAGE_HPP


#include "abstract_message.hpp"

class DiscoverMessage : AbstractMessage {


public:
    MessageType get_message_type() override;

};


#endif //SNAKE_GAME_DISCOVER_MESSAGE_HPP
