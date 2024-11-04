//
// Created by plushjill on 03.11.2024.
//

#ifndef SNAKE_GAME_COORD_POINT_HPP
#define SNAKE_GAME_COORD_POINT_HPP


class CoordPoint {
private:
    int x_;
    int y_;

public:
    explicit CoordPoint(int x, int y);
    [[nodiscard]] int get_x() const;
    [[nodiscard]] int get_y() const;
    void set_x(int x);
    void set_y(int y);
    CoordPoint get_shift_from(CoordPoint& other) const {
        return CoordPoint(this->x_ - other.x_, this->y_ - other.y_);
    }
    bool operator==(const CoordPoint& other) const {
        return this->x_ == other.x_ && this->y_ == other.y_;
    }
    bool operator!=(const CoordPoint& other) const {
        return this != &other;
    }
};


#endif //SNAKE_GAME_COORD_POINT_HPP
