//
// Created by plushjill on 12.11.2024.
//

#ifndef SNAKE_GAME_CONFIG_EDITOR_HPP
#define SNAKE_GAME_CONFIG_EDITOR_HPP
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtCore>
#include <QtGui>
#include <boost/filesystem.hpp>

class ConfigEditor : public QObject {
Q_OBJECT

private:
    constexpr static const char* m_relative_config_path {"../resources/game_config.ini"};
    static boost::filesystem::path m_absolute_config_path;

    constexpr static const int m_min_field_width {5};
    constexpr static const int m_max_field_width {80};

    constexpr static const int m_min_field_height {5};
    constexpr static const int m_max_field_height {80};

    constexpr static const int m_min_food_static {0};
    constexpr static const int m_max_food_static {10};

    constexpr static const int m_min_state_delay_ms {500};
    constexpr static const int m_max_state_delay_ms {4000};

    static void init_config_path();
public:
    explicit ConfigEditor(QObject *parent = nullptr);

    Q_INVOKABLE void update_config(
            const int &field_width,
            const int &field_height,
            const int &food_static,
            const int &state_delay
    );
    Q_INVOKABLE int get_field_width();
    Q_INVOKABLE int get_field_height();
    Q_INVOKABLE int get_food_static();
    Q_INVOKABLE int get_state_delay_ms();

    Q_INVOKABLE int get_max_field_height();
    Q_INVOKABLE int get_max_field_width();
    Q_INVOKABLE int get_max_food_static();
    Q_INVOKABLE int get_min_field_height();
    Q_INVOKABLE int get_min_field_width();
    Q_INVOKABLE int get_min_food_static();
    Q_INVOKABLE int get_min_state_delay_ms();
    Q_INVOKABLE int get_max_state_delay_ms();

};



#endif //SNAKE_GAME_CONFIG_EDITOR_HPP
