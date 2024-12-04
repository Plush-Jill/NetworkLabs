//
// Created by plushjill on 03.11.2024.
//

#ifndef SNAKE_GAME_COORD_POINT_HPP
#define SNAKE_GAME_COORD_POINT_HPP
#include "snakes.pb.h"
#include "enum/direction.hpp"

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
    CoordPoint get_shift_from(const CoordPoint& other) const {
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
    bool operator<(const CoordPoint& other) const {
        if (m_x == other.m_x && m_y == other.m_y) {
            return false;
        }
        if (m_x < other.m_x || m_y < other.m_y) {
            return true;
        }
        return false;
    }
    [[nodiscard]] Direction get_relative_direction_from(const CoordPoint& other) const {
        CoordPoint shift = this->get_shift_from(other);
        int x = shift.m_x == 0 ? 0 : (shift.m_x > 0 ? 1 : -1);
        int y = shift.m_y == 0 ? 0 : (shift.m_y > 0 ? 1 : -1);

        if (x == 0 && y == 1) {
            return Direction::Down;
        } else if (x == 0 && y == -1) {
            return Direction::Up;
        } else if (x == 1 && y == 0) {
            return Direction::Right;
        } else if (x == -1 && y == 0) {
            return Direction::Left;
        } else {
            throw std::invalid_argument("points do not lie on same axis");
        }
    }
};


#endif //SNAKE_GAME_COORD_POINT_HPP
