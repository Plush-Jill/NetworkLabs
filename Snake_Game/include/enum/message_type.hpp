//
// Created by plushjill on 04.11.2024.
//

#ifndef SNAKE_GAME_MESSAGE_TYPE_HPP
#define SNAKE_GAME_MESSAGE_TYPE_HPP

enum class MessageType {
    PingMsg,
    SteerMsg,
    AckMsg,
    StateMsg,
    AnnouncementMsg,
    JoinMsg,
    ErrorMsg,
    RoleChangeMsg,
    DiscoverMsg
};

#endif //SNAKE_GAME_MESSAGE_TYPE_HPP
