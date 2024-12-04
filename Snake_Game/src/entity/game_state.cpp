//
// Created by plushjill on 03.11.2024.
//

#include <utility>

#include "include/entity/game_state.hpp"

std::shared_ptr<std::vector<GamePlayer>> GameState::get_game_players() const {
    return m_game_players;
}

void GameState::set_game_players(std::shared_ptr<std::vector<GamePlayer>> game_players) {
    m_game_players = std::move(game_players);
}

std::shared_ptr<std::vector<CoordPoint>> GameState::get_foods() const {
    return m_foods;
}

void GameState::set_foods(std::shared_ptr<std::vector<CoordPoint>> foods) {
    m_foods = std::move(foods);
}

std::shared_ptr<std::vector<Snake>> GameState::get_snakes() const {
    return m_snakes;
}

void GameState::set_snakes(std::shared_ptr<std::vector<Snake>> snakes) {
    m_snakes = std::move(snakes);
}

int GameState::get_state_order() const {
    return m_state_order;
}

void GameState::set_state_order(int state_order) {
    m_state_order = state_order;
}

GameState::GameState(
        int state_order,
        std::shared_ptr<std::vector<Snake>> snakes,
        std::shared_ptr<std::vector<CoordPoint>> foods,
        std::shared_ptr<std::vector<GamePlayer>> game_players) :
        m_state_order (state_order),
        m_snakes (std::move(snakes)),
        m_foods (std::move(foods)),
        m_game_players (std::move(game_players))
        {

}
