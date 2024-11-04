//
// Created by plushjill on 04.11.2024.
//

#ifndef SNAKE_GAME_ERROR_MESSAGE_HPP
#define SNAKE_GAME_ERROR_MESSAGE_HPP


#include <string>
#include "abstract_message.hpp"

class ErrorMessage : AbstractMessage{
private:
    std::string error_message_;

public:
    MessageType get_message_type() override;
    [[nodiscard]] const std::string &get_error_message() const;
    void set_error_message(const std::string &error_message);
};


#endif //SNAKE_GAME_ERROR_MESSAGE_HPP
