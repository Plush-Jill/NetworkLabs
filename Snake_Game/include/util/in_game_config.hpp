//
// Created by plushjill on 03.12.2024.
//

#ifndef SNAKE_GAME_IN_GAME_CONFIG_HPP
#define SNAKE_GAME_IN_GAME_CONFIG_HPP
#include <QObject>
#include <QtCore>
#include <QColor>

class InGameConfig : public QObject {
    Q_OBJECT

private:
    int m_field_width {2};
    int m_field_height {5};


public:
    explicit InGameConfig(QObject *parent = nullptr) : QObject(parent) {};


    Q_INVOKABLE int get_field_width() {
        return m_field_width;
    }

    Q_INVOKABLE int get_field_height() {
        return m_field_height;
    }

    Q_INVOKABLE QColor get_cell_color(int index) {
        if (index == 2) {
            return {"red"};
        }

        return {"blue"};
    }
};


#endif //SNAKE_GAME_IN_GAME_CONFIG_HPP
