//
// Created by plushjill on 03.11.2024.
//

#include "include/entity/coord_point.hpp"

int Coord::get_x() const {
    return m_x;
}

void Coord::set_x(int x) {
    m_x = x;
}

int Coord::get_y() const {
    return m_y;
}

void Coord::set_y(int y) {
    m_y = y;
}

Coord::Coord(int x, int y) :
        m_x(x), m_y(y) {}

Coord::Coord(const snakes::GameState_Coord& coord)
    : Coord(coord.x(), coord.y()) {
}
