//
// Created by plushjill on 03.11.2024.
//

#include "include/entity/game_state.hpp"

const std::vector<GamePlayer> &GameState::get_game_players() const {
    return game_players_;
}

void GameState::set_game_players(const std::vector<GamePlayer> &game_players) {
    game_players_ = game_players;
}

const std::set<CoordPoint> &GameState::get_foods() const {
    return foods_;
}

void GameState::set_foods(const std::set<CoordPoint> &foods) {
    foods_ = foods;
}

const std::vector<Snake> &GameState::get_snakes() const {
    return snakes_;
}

void GameState::set_snakes(const std::vector<Snake> &snakes) {
    snakes_ = snakes;
}

int GameState::get_state_order() const {
    return state_order_;
}

void GameState::set_state_order(int state_order) {
    state_order_ = state_order;
}
