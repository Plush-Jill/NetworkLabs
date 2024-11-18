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

void test_serializer() {
    CoordPoint coord_point = CoordPoint(2, 33);
    snakes::GameState::Coord coord_proto = ProtobufManager::create_coord(coord_point);
    coord_proto.set_x(41);
    coord_proto.set_y(2);
    std::string serialized_data;
    coord_proto.SerializeToString(&serialized_data);
    if (coord_proto.SerializeToString(&serialized_data)) {
        std::cout << "Successfully serialized" << std::endl;
        std::cout << "Serialized data: " << serialized_data << std::endl;
    } else {
        std::cerr << "Serializing error" << std::endl;
    }

    snakes::GameState::Coord parsed_coord_proto;
    if (parsed_coord_proto.ParseFromString(serialized_data)) {
        std::cout << boost::format("Coord: (%1%, %2%)")
                     % parsed_coord_proto.x()
                     % parsed_coord_proto.y() << std::endl;
    } else {
        std::cerr << "Deserialization error" << std::endl;
    }
}

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
