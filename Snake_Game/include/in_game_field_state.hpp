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
#include "model/game_field.hpp"

class InGameFieldView : public QObject {
    Q_OBJECT

private:
    std::shared_ptr<GameField> m_game_field;
    std::shared_ptr<std::unordered_map<CellContent, QColor>> m_color_map;
    int m_field_cell_width {4};
    int m_field_cell_height {8};


public:
    explicit InGameFieldView(QObject *parent = nullptr) : QObject(parent) {
        m_color_map->insert({CellContent::Snake, {"green"}});
        m_color_map->insert({CellContent::Food, {"red"}});
        m_color_map->insert({CellContent::Snake, {"white"}});
    };


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

    Q_INVOKABLE QColor get_cell_color_from_state(int index) {
        Coord coord {index / m_game_field->get_field_width(),
                          index % m_game_field->get_field_width()};

        return m_color_map->at(m_game_field->get_cell_content(coord));
    }

    Q_INVOKABLE QColor get_cell_color_by_state(int index) {
        Coord index_point
            {index % m_field_cell_width, index / m_field_cell_width};
        return {"red"};
    }

    void update_field() {
        for (int i {}; i < m_field_cell_height * m_field_cell_width; ++i) {
            update_cell(i);
        }
        red_cell_index = (red_cell_index + 1) % (m_field_cell_width * m_field_cell_height);
    }

    void update_cell(int index) {
        emit cellUpdated(index);
    }
signals:
    void cellUpdated(int index);
};


#endif //SNAKE_GAME_IN_GAME_FIELD_STATE_HPP
