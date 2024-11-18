//
// Created by plushjill on 12.11.2024.
//

#include "include/util/config_editor.hpp"
#include <boost/dll.hpp>
#include <boost/format.hpp>
#include <iostream>

boost::filesystem::path ConfigEditor::m_absolute_config_path;


void ConfigEditor::update_config(const QString &field_width,
                                 const QString &field_height,
                                 const QString &food_static,
                                 const QString &state_delay
                                ) {
    boost::property_tree::ptree config;
    boost::property_tree::ini_parser::read_ini(
            ConfigEditor::m_absolute_config_path.string(),
            config);

    config.put("field_size.width", field_width.toStdString());
    config.put("field_size.height", field_height.toStdString());
    config.put("food.food_static", food_static.toStdString());
    config.put("state.state_delay_ms", state_delay.toStdString());

    boost::property_tree::write_ini(
            ConfigEditor::m_absolute_config_path.string(),
            config);
}

int ConfigEditor::get_field_width() {
    boost::property_tree::ptree config;
    boost::property_tree::ini_parser::read_ini(
            ConfigEditor::m_absolute_config_path.string(),
            config);
    return config.get<int>("field_size.width");
}

int ConfigEditor::get_field_height() {
    boost::property_tree::ptree config;
    boost::property_tree::ini_parser::read_ini(
            ConfigEditor::m_absolute_config_path.string(),
            config);
    return config.get<int>("field_size.height");
}

int ConfigEditor::get_food_static() {
    boost::property_tree::ptree config;
    boost::property_tree::ini_parser::read_ini(
            ConfigEditor::m_absolute_config_path.string(),
            config);
    return config.get<int>("food.food_static");
}

int ConfigEditor::get_max_field_height() {
    return m_max_field_height;
}

int ConfigEditor::get_max_field_width() {
    return m_max_field_width;
}

int ConfigEditor::get_max_food_static() {
    return m_max_food_static;
}

int ConfigEditor::get_min_field_height() {
    return m_min_field_height;
}

int ConfigEditor::get_min_field_width() {
    return m_min_field_width;
}

int ConfigEditor::get_min_food_static() {
    return m_min_food_static;
}

ConfigEditor::ConfigEditor(QObject *parent) : QObject(parent) {
    if (m_absolute_config_path.empty()) {
        ConfigEditor::init_config_path();
    }
}

void ConfigEditor::init_config_path() {
    boost::filesystem::path absolute_exec_path = boost::dll::program_location();
    m_absolute_config_path = absolute_exec_path.parent_path() /
                             m_relative_config_path;
}

int ConfigEditor::get_state_delay_ms() {
    boost::property_tree::ptree config;
    boost::property_tree::ini_parser::read_ini(
            ConfigEditor::m_absolute_config_path.string(),
            config);
    return config.get<int>("state.state_delay_ms");
}

int ConfigEditor::get_min_state_delay_ms() {
    return m_min_state_delay_ms;
}

int ConfigEditor::get_max_state_delay_ms() {
    return m_max_state_delay_ms;
}
