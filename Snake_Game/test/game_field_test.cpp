//
// Created by plushjill on 04.12.2024.
//

#include <gtest/gtest.h>
#include "model/game_field.hpp"


TEST (GameFieldTest, is_cell_contains_food) {
    GameField game_field {};
    std::shared_ptr<std::vector<Coord>> foods =
            game_field.get_game_state()->get_foods();


    foods->insert(foods->end(), Coord(1, 2));

    EXPECT_TRUE(game_field.is_cell_contains_food(Coord(1, 2)));
    EXPECT_FALSE(game_field.is_cell_contains_food(Coord(1, 4)));
}