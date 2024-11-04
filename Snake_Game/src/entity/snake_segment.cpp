//
// Created by plushjill on 03.11.2024.
//

#include "include/entity/snake_segment.hpp"


void SnakeSegment::set_coord_point(const CoordPoint &coordPoint) {
    coord_point_ = coordPoint;
}

SnakeSegment::SnakeSegment(CoordPoint coord_point) :
coord_point_(coord_point){}

const CoordPoint &SnakeSegment::get_coord_point() const {
    return coord_point_;
}
