#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include <QUrl>
#include "../include/util/config_editor.hpp"
#include <QtQml/qqmlregistration.h>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/dll.hpp>
#include "util/protobuf_manager.hpp"


Q_DECL_EXPORT int main(int argc, char *argv[]) {

    boost::filesystem::path absolute_exec_path = boost::dll::program_location();

    boost::filesystem::path qml_app_path = (absolute_exec_path.parent_path().parent_path()) /
            "resources/Snake_Game_Window/Snake_Game_WindowContent/App.qml";

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine(QUrl::fromLocalFile(qml_app_path.string().c_str()));

    auto* config_editor = new ConfigEditor;
    engine.rootContext()->setContextProperty("ConfigEditor", config_editor);

    return QGuiApplication::exec();
}
