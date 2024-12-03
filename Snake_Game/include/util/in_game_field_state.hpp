//
// Created by plushjill on 03.12.2024.
//

#ifndef SNAKE_GAME_IN_GAME_FIELD_STATE_HPP
#define SNAKE_GAME_IN_GAME_FIELD_STATE_HPP
#include <QObject>
#include <QtCore>
#include <QColor>
#include <iostream>
#include <format>

class InGameFieldState : public QObject {
    Q_OBJECT

private:
    int m_field_cell_width {2};
    int m_field_cell_height {5};


public:
    explicit InGameFieldState(QObject *parent = nullptr) : QObject(parent) {};


    Q_INVOKABLE int get_field_cell_width() {
        return m_field_cell_width;
    }

    Q_INVOKABLE int get_field_cell_height() {
        return m_field_cell_height;
    }

    int red_cell_index {};
    Q_INVOKABLE QColor get_cell_color(int index) {
        if (index == red_cell_index) {
            return {"red"};
        }

        return {"blue"};
    }

    void update_field() {
        for (int i {}; i < m_field_cell_height * m_field_cell_width; ++i) {
            update_cell(i);
        }
        red_cell_index = (red_cell_index + 1) % 10;
    }

    void update_cell(int index) {
        emit cellUpdated(index);
    }
signals:
    void cellUpdated(int index);
};


#endif //SNAKE_GAME_IN_GAME_FIELD_STATE_HPP
