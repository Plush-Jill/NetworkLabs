//
// Created by plushjill on 03.11.2024.
//

#ifndef SNAKE_GAME_GAME_CONFIG_HPP
#define SNAKE_GAME_GAME_CONFIG_HPP

#include <chrono>
#include "snakes.pb.h"

class GameConfig {
private:
    int m_field_width = 40;
    int m_field_height = 30;
    int m_food_static = 1;
    std::chrono::milliseconds m_state_delay_ms = std::chrono::milliseconds(1000);
    
public:
    explicit GameConfig() = default;
    GameConfig(const GameConfig& other);
    GameConfig& operator=(const GameConfig& right);
    GameConfig(const snakes::GameConfig& game_config);

    bool operator==(GameConfig &other);

    [[nodiscard]] const std::chrono::milliseconds &get_state_delay_ms() const;
    [[nodiscard]] int get_food_static() const;
    [[nodiscard]] int get_field_height() const;
    [[nodiscard]] int get_field_width() const;
    void set_state_delay_ms(const std::chrono::milliseconds &state_delay_ms);
    void set_food_static(int food_static);
    void set_field_height(int height);
    void set_field_width(int width);


};


#endif //SNAKE_GAME_GAME_CONFIG_HPP
