#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include <QUrl>
#include "../include/util/config_editor.hpp"
#include <QtQml/qqmlregistration.h>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/dll.hpp>
#include "util/protobuf_manager.hpp"
#include "include/in_game_field_state.hpp"
#include "controller/snake_controller.hpp"


void foo (InGameFieldView* state) {
    while (1) {
        usleep(90000);
        state->update_field();
    }
}

Q_DECL_EXPORT int main(int argc, char *argv[]) {

    boost::filesystem::path absolute_exec_path = boost::dll::program_location();

    boost::filesystem::path qml_app_path = (absolute_exec_path.parent_path().parent_path()) /
            "resources/Snake_Game_Window/Snake_Game_WindowContent/App.qml";

    QGuiApplication app(argc, argv);
    QFontDatabase::addApplicationFont((absolute_exec_path.parent_path().parent_path() /
                                        "resources/Comic Sans MS.ttf").string().c_str());
    QUrl app_url = QUrl::fromLocalFile(qml_app_path.string().c_str());



    QQmlApplicationEngine engine;

//    qmlRegisterType<SnakeController>("com.example.snake", 1, 0, "SnakeController");
//    qmlRegisterType<InGameFieldView>("com.example.snake", 1, 0, "InGameFieldView");


    auto* snake_controller = new SnakeController;
    engine.rootContext()->setContextProperty("SnakeController", snake_controller);
    auto* in_game_field_view = new InGameFieldView;
    engine.rootContext()->setContextProperty("InGameFieldView", in_game_field_view);
    auto* config_editor = new ConfigEditor;
    engine.rootContext()->setContextProperty("ConfigEditor", config_editor);

    engine.load(app_url);

    std::thread thread(foo, in_game_field_view);
//    QGuiApplication::exec();
//    thread.join();
//    return 0;
    return QGuiApplication::exec();
}
