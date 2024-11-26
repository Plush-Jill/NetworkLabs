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
    explicit SnakeController(
            std::shared_ptr<Snake> snake,
            QObject* parent = nullptr);

    [[nodiscard]] int get_snake_id();

    enum class HeadDirection {
        Up,
        Down,
        Left,
        Right
    };

    Q_ENUM(HeadDirection) // Указывает, что enum будет доступен в QML
    Q_INVOKABLE void turn_head(SnakeController::HeadDirection direction);

};


#endif //SNAKE_GAME_SNAKE_CONTROLLER_HPP
