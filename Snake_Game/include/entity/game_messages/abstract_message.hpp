//
// Created by plushjill on 04.11.2024.
//

#ifndef SNAKE_GAME_ABSTRACT_MESSAGE_HPP
#define SNAKE_GAME_ABSTRACT_MESSAGE_HPP


#include "enum/message_type.hpp"

class AbstractMessage {
private:

public:
    virtual MessageType get_message_type() = 0;
};


#endif //SNAKE_GAME_ABSTRACT_MESSAGE_HPP
