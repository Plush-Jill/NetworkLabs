//
// Created by plushjill on 04.11.2024.
//

#include "include/entity/game_messages/announcement_message.hpp"

MessageType AnnouncementMessage::get_message_type() {
    return MessageType::AnnouncementMsg;
}

const GameAnnouncement &AnnouncementMessage::get_game_announcement() const {
    return game_announcement_;
}

void AnnouncementMessage::set_game_announcement(const GameAnnouncement &game_announcement) {
    game_announcement_ = game_announcement;
}
