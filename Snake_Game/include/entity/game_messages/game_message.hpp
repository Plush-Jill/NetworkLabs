//
// Created by plushjill on 04.11.2024.
//

#ifndef SNAKE_GAME_GAME_MESSAGE_HPP
#define SNAKE_GAME_GAME_MESSAGE_HPP


#include <memory>
#include "abstract_message.hpp"

class GameMessage {
private:
    int msg_seq_;
    int sender_id_;
    int receiver_id_;
    std::shared_ptr<AbstractMessage> message_;

public:
    [[nodiscard]] std::shared_ptr<AbstractMessage> get_message() const;
    [[nodiscard]] int get_msg_seq() const;
    [[nodiscard]] int get_receiver_id() const;
    [[nodiscard]] int get_sender_id() const;
    void set_message(std::shared_ptr<AbstractMessage> &message);
    void set_msg_seq(int msg_seq);
    void set_receiver_id(int receiver_id);
    void set_sender_id(int sender_id);

};


#endif //SNAKE_GAME_GAME_MESSAGE_HPP
