//
// Created by plushjill on 03.11.2024.
//

#include "include/entity/game_state.hpp"

const std::vector<GamePlayer> &GameState::get_game_players() const {
    return m_game_players;
}

void GameState::set_game_players(const std::vector<GamePlayer> &game_players) {
    m_game_players = game_players;
}

const std::vector<CoordPoint> &GameState::get_foods() const {
    return m_foods;
}

void GameState::set_foods(const std::vector<CoordPoint> &foods) {
    m_foods = foods;
}

const std::vector<Snake> &GameState::get_snakes() const {
    return m_snakes;
}

void GameState::set_snakes(const std::vector<Snake> &snakes) {
    m_snakes = snakes;
}

int GameState::get_state_order() const {
    return m_state_order;
}

void GameState::set_state_order(int state_order) {
    m_state_order = state_order;
}

GameState::GameState(
        int state_order,
        const std::vector<Snake>& snakes,
        const std::vector<CoordPoint>& foods,
        const std::vector<GamePlayer>& game_players) :
        m_state_order (state_order),
        m_snakes (snakes),
        m_foods (foods),
        m_game_players (game_players)
        {

}

std::shared_ptr<Snake> GameState::get_snake(int snake_id) {
    for (Snake& snake : m_snakes) {
        if (snake.get_id() == snake_id) {
            return std::shared_ptr<Snake>(&snake);
        }
    }

    return nullptr;
}
