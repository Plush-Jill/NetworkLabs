//
// Created by plushjill on 03.11.2024.
//

#ifndef SNAKE_GAME_GAME_CONFIG_HPP
#define SNAKE_GAME_GAME_CONFIG_HPP

#include <chrono>


class GameConfig {
private:
    int field_width_ = 40;
    int field_height_ = 30;
    int food_static_ = 1;
    std::chrono::milliseconds state_delay_ms_ = std::chrono::milliseconds(1000);
    
public:
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
