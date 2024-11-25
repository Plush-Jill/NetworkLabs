//
// Created by plushjill on 11.11.2024.
//

#ifndef SNAKE_GAME_MAIN_WINDOW_CONTROLLER_HPP
#define SNAKE_GAME_MAIN_WINDOW_CONTROLLER_HPP


#include <QObject>
#include <QDebug>
#include <iostream>

class MainWindowController : public QObject{
    Q_OBJECT

public:
    explicit MainWindowController(QObject *parent = nullptr);
public slots:
    static void on_button_clicked(){
        std::cout << "button clicked" << std::endl;
    }
};


#endif //SNAKE_GAME_MAIN_WINDOW_CONTROLLER_HPP
