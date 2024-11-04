//
// Created by plushjill on 03.11.2024.
//

#include "include/entity/game_config.hpp"

const std::chrono::milliseconds &GameConfig::get_state_delay_ms() const {
    return state_delay_ms_;
}

void GameConfig::set_state_delay_ms(const std::chrono::milliseconds &state_delay_ms) {
    GameConfig::state_delay_ms_ = state_delay_ms;
}

int GameConfig::get_food_static() const {
    return food_static_;
}

void GameConfig::set_food_static(int food_static) {
    GameConfig::food_static_ = food_static;
}

int GameConfig::get_field_height() const {
    return field_height_;
}

void GameConfig::set_field_height(int height) {
    GameConfig::field_height_ = height;
}

int GameConfig::get_field_width() const {
    return field_width_;
}

void GameConfig::set_field_width(int width) {
    GameConfig::field_width_ = width;
}
