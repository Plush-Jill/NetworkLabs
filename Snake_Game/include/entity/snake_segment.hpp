//
// Created by plushjill on 03.11.2024.
//

#ifndef SNAKE_GAME_SNAKE_SEGMENT_HPP
#define SNAKE_GAME_SNAKE_SEGMENT_HPP
#include "include/entity/coord_point.hpp"

class SnakeSegment {
private:
    CoordPoint coord_point_;

public:
    explicit SnakeSegment(CoordPoint coord_point);
    void set_coord_point(const CoordPoint &coordPoint);
    [[nodiscard]] const CoordPoint &get_coord_point() const;
    bool operator<(const SnakeSegment& other) const {
         return coord_point_ != other.coord_point_;
    }
};


#endif //SNAKE_GAME_SNAKE_SEGMENT_HPP
