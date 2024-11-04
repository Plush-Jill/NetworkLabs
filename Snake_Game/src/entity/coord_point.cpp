//
// Created by plushjill on 03.11.2024.
//

#include "include/entity/coord_point.hpp"

int CoordPoint::get_x() const {
    return x_;
}

void CoordPoint::set_x(int x) {
    x_ = x;
}

int CoordPoint::get_y() const {
    return y_;
}

void CoordPoint::set_y(int y) {
    y_ = y;
}

CoordPoint::CoordPoint(int x, int y) :
x_(x), y_(y) {}
