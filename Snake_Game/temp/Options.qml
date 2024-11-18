import QtQuick
import QtQuick.Controls
import QtCore

Item {
    width: 1920
    height: 1080

    // width: parent.width
    // height: parent.height

    // Loader {
    //     id: loader
    //     anchors.centerIn: parent
    //     width: parent.width
    //     height: parent.height
    // }

    Rectangle {
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        color: "#431515"
    }
        Button {
            id: button
            x: 787
            y: 830
            width: 347
            height: 90
            text: "Back"
            font.pointSize: 40
            // Загружаем экран настроек в Loader
            // onClicked: {
                // loader.source = ""
            // }
            onClicked: loader.source = "MainMenu.qml" // Вернуться в главное меню
        }

        Grid {
            id: grid
            columns: 3
            rows: 3
            x: 242
            y: 116
            width: 1436
            height: 258

            // Settings {
            //     id: game_config
            //     property string config_file_path: "../../game_config.ini"
            // }

            TextField {
                width: parent.width * (1/4)
                height: parent.height * (1 / parent.rows)
                color: "#ffffff"
                text: "field width"
                hoverEnabled: true
                placeholderTextColor: "#88000000"
                font.pointSize: 30
                background: Rectangle {
                    color: "transparent" // Фон полностью прозрачный
                    border.color: "transparent" // Убираем границу, если она есть
                }
            }



            Slider {
                id: field_width_slider
                width: parent.width * (2/4)
                height: parent.height * (1 / parent.rows)
                from: 5
                to: 80
                stepSize: 1
                value: 10
                // value: game_config.value("field_size/width", 20)

                // onValueChanged: {
                //     game_config.setValue("field_size/width", field_width_slider.value)
                // }
            }

            TextField {
                width: parent.width * (1/4)
                height: parent.height * (1 / parent.rows)
                color: "#ffffff"
                text: field_width_slider.value
                hoverEnabled: true
                placeholderTextColor: "#88000000"
                font.pointSize: 30
                background: Rectangle {
                    color: "transparent" // Фон полностью прозрачный
                    border.color: "transparent" // Убираем границу, если она есть
                }
            }

            TextField {
                width: parent.width * (1/4)
                height: parent.height * (1 / parent.rows)
                color: "#ffffff"
                text: "field height"
                font.pointSize: 30
                background: Rectangle {
                    color: "transparent" // Фон полностью прозрачный
                    border.color: "transparent" // Убираем границу, если она есть
                }
            }

            Slider {
                id: field_height_slider
                width: parent.width * (1/4)
                height: parent.height * (1 / parent.rows)
                from: 5
                to: 80
                stepSize: 1
                value: 10
                // value: game_config.value("field_size/height", 15)
                //
                // onValueChanged: {
                //     game_config.setValue("field_size/height", field_height_slider.value)
                // }
            }


            TextField {
                width: parent.width * (1/4)
                height: parent.height * (1 / parent.rows)
                color: "#ffffff"
                text: field_height_slider.value
                hoverEnabled: true
                placeholderTextColor: "#88000000"
                font.pointSize: 30
                background: Rectangle {
                    color: "transparent" // Фон полностью прозрачный
                    border.color: "transparent" // Убираем границу, если она есть
                }
            }

            TextField {
                width: parent.width * (1/4)
                height: parent.height * (1 / parent.rows)
                color: "#ffffff"
                text: "food static"
                font.pointSize: 30
                background: Rectangle {
                    color: "transparent" // Фон полностью прозрачный
                    border.color: "transparent" // Убираем границу, если она есть
                }
            }

            Slider {
                id: food_static_slider
                width: parent.width * (1/4)
                height: parent.height * (1 / parent.rows)
                from: 0
                to: 10
                stepSize: 1
                value: 10
                // value: game_config.value("food/food_static", 2)
                //
                // onValueChanged: {
                //     game_config.setValue("food/food_static", food_static_slider.value)
                // }
            }

            TextField {
                width: parent.width * (1/4)
                height: parent.height * (1 / parent.rows)
                color: "#ffffff"
                text: food_static_slider.value
                hoverEnabled: true
                placeholderTextColor: "#88000000"
                font.pointSize: 30
                background: Rectangle {
                    color: "transparent" // Фон полностью прозрачный
                    border.color: "transparent" // Убираем границу, если она есть
                }
            }
        }
    // }
}
