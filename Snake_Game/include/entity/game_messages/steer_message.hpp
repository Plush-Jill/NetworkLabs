//
// Created by plushjill on 04.11.2024.
//

#ifndef SNAKE_GAME_STEER_MESSAGE_HPP
#define SNAKE_GAME_STEER_MESSAGE_HPP


#include "abstract_message.hpp"
#include "enum/direction.hpp"

class SteerMessage : AbstractMessage{
private:
    Direction direction_;

public:
    MessageType get_message_type() override;
    [[nodiscard]] Direction get_direction() const;
    void set_direction(Direction direction);
};


#endif //SNAKE_GAME_STEER_MESSAGE_HPP
