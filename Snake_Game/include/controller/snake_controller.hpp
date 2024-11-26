//
// Created by plushjill on 26.11.2024.
//

#ifndef SNAKE_GAME_SNAKE_CONTROLLER_HPP
#define SNAKE_GAME_SNAKE_CONTROLLER_HPP
#include <QtCore>
#include <QtGui>
#include <QObject>
#include "entity/snake.hpp"

class SnakeController : public QObject {
Q_OBJECT

private:
    std::shared_ptr<Snake> m_snake;


public:
    Q_INVOKABLE void turn_head(std::string& direction);

};


#endif //SNAKE_GAME_SNAKE_CONTROLLER_HPP
