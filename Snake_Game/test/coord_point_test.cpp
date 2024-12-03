//
// Created by plushjill on 26.11.2024.
//

#include <gtest/gtest.h>
#include "entity/coord_point.hpp"



TEST (CoordPointTest, get_relative_direction_from) {
    CoordPoint p1 {10, 10};
    CoordPoint p2 {9, 10};
    CoordPoint p3 {4, 10};
    CoordPoint p4 {11, 10};
    CoordPoint p5 {10, 11};
    CoordPoint p6 {10, 8};

    CoordPoint p7 {3, 3};

    EXPECT_TRUE(p2.get_relative_direction_from(p1) == Direction::Left);
    EXPECT_EQ(p3.get_relative_direction_from(p1), Direction::Left);
    EXPECT_EQ(p4.get_relative_direction_from(p1), Direction::Right);
    EXPECT_EQ(p5.get_relative_direction_from(p1), Direction::Down);
    EXPECT_EQ(p6.get_relative_direction_from(p1), Direction::Up);


    EXPECT_ANY_THROW(p7.get_relative_direction_from(p1) == Direction::Up);

}