//
// Created by plushjill on 03.11.2024.
//

#include "include/entity/coord_point.hpp"

int CoordPoint::get_x() const {
    return m_x;
}

void CoordPoint::set_x(int x) {
    m_x = x;
}

int CoordPoint::get_y() const {
    return m_y;
}

void CoordPoint::set_y(int y) {
    m_y = y;
}

CoordPoint::CoordPoint(int x, int y) :
        m_x(x), m_y(y) {}
