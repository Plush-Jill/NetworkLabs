//
// Created by plushjill on 03.11.2024.
//

#ifndef SNAKE_GAME_COORD_POINT_HPP
#define SNAKE_GAME_COORD_POINT_HPP
#include "snakes.pb.h"

class CoordPoint {
private:
    int m_x;
    int m_y;

public:
    explicit CoordPoint(int x, int y);
    explicit CoordPoint(const snakes::GameState_Coord& coord);
    [[nodiscard]] int get_x() const;
    [[nodiscard]] int get_y() const;
    void set_x(int x);
    void set_y(int y);
    CoordPoint get_shift_from(CoordPoint& other) const {
        return CoordPoint(this->m_x - other.m_x, this->m_y - other.m_y);
    }
    bool operator==(const CoordPoint& other) const {
        return this->m_x == other.m_x && this->m_y == other.m_y;
    }
    bool operator!=(const CoordPoint& other) const {
        return this != &other;
    }
    CoordPoint operator+(const CoordPoint& other) const {
        return CoordPoint(m_x + other.m_x, m_y + other.m_y);
    }
};


#endif //SNAKE_GAME_COORD_POINT_HPP
