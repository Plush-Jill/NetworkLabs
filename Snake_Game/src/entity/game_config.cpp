//
// Created by plushjill on 03.11.2024.
//

#include "include/entity/game_config.hpp"

const std::chrono::milliseconds &GameConfig::get_state_delay_ms() const {
    return m_state_delay_ms;
}

void GameConfig::set_state_delay_ms(const std::chrono::milliseconds &state_delay_ms) {
    GameConfig::m_state_delay_ms = state_delay_ms;
}

int GameConfig::get_food_static() const {
    return m_food_static;
}

void GameConfig::set_food_static(int food_static) {
    GameConfig::m_food_static = food_static;
}

int GameConfig::get_field_height() const {
    return m_field_height;
}

void GameConfig::set_field_height(int height) {
    GameConfig::m_field_height = height;
}

int GameConfig::get_field_width() const {
    return m_field_width;
}

void GameConfig::set_field_width(int width) {
    GameConfig::m_field_width = width;
}

GameConfig::GameConfig(const GameConfig &other)
        : m_field_width(other.m_field_width),
          m_field_height(other.m_field_height),
          m_food_static(other.m_food_static),
          m_state_delay_ms(other.m_state_delay_ms) {

}

GameConfig &GameConfig::operator=(const GameConfig &right) {
    if (this != &right) {
        m_field_width = right.m_field_width;
        m_field_height = right.m_field_height;
        m_food_static = right.m_food_static;
        m_state_delay_ms = right.m_state_delay_ms;
    }
    return *this;
}
