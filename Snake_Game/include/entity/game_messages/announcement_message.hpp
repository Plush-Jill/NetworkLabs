//
// Created by plushjill on 04.11.2024.
//

#ifndef SNAKE_GAME_ANNOUNCEMENT_MESSAGE_HPP
#define SNAKE_GAME_ANNOUNCEMENT_MESSAGE_HPP


#include "abstract_message.hpp"
#include "entity/game_announcement.hpp"

class AnnouncementMessage : AbstractMessage{
private:
    GameAnnouncement game_announcement_;

public:
    MessageType get_message_type() override;
    [[nodiscard]] const GameAnnouncement &get_game_announcement() const;
    void set_game_announcement(const GameAnnouncement &game_announcement);

};


#endif //SNAKE_GAME_ANNOUNCEMENT_MESSAGE_HPP
