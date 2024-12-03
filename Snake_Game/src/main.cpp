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
#include "util/in_game_field_state.hpp"

void foo (InGameFieldState* state) {
    sleep(5);
    state->update_field();
    std::cout << "field updated" << std::endl;
}

Q_DECL_EXPORT int main(int argc, char *argv[]) {

    boost::filesystem::path absolute_exec_path = boost::dll::program_location();

    boost::filesystem::path qml_app_path = (absolute_exec_path.parent_path().parent_path()) /
            "resources/Snake_Game_Window/Snake_Game_WindowContent/App.qml";

    QGuiApplication app(argc, argv);

    QUrl app_url = QUrl::fromLocalFile(qml_app_path.string().c_str());

    QQmlApplicationEngine engine;

    auto* in_game_field_state = new InGameFieldState;
    engine.rootContext()->setContextProperty("InGameFieldState", in_game_field_state);
    auto* config_editor = new ConfigEditor;
    engine.rootContext()->setContextProperty("ConfigEditor", config_editor);


    std::thread thread(foo, in_game_field_state);

    engine.load(app_url);
    return QGuiApplication::exec();
}
