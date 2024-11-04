//
// Created by plushjill on 04.11.2024.
//

#ifndef SNAKE_GAME_STATE_MESSAGE_HPP
#define SNAKE_GAME_STATE_MESSAGE_HPP


#include "abstract_message.hpp"
#include "entity/game_state.hpp"

class StateMessage : AbstractMessage{
private:
    GameState game_state_;

public:
    MessageType get_message_type() override;

    [[nodiscard]] const GameState &get_game_state() const;
    void set_game_state(const GameState &game_state);
};


#endif //SNAKE_GAME_STATE_MESSAGE_HPP
