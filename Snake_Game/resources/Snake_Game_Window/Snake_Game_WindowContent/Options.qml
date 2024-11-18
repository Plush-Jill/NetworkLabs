import QtQuick
import QtQuick.Controls
import QtCore


Item {
    width: 1920
    height: 1080

    // width: parent.width
    // height: parent.height

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

        onClicked: loader.source = "MainMenu.qml"
    }

    Shortcut {
        sequence: "Escape"
        onActivated: loader.source = "MainMenu.qml"
    }

    Grid {
        id: grid
        columns: 3
        rows: 4
        x: 102
        y: 348
        width: 1716
        height: 344


        TextField {
            width: parent.width * (2 / 10)
            height: parent.height * (1 / parent.rows)
            color: "#ffffff"
            text: "field width"
            horizontalAlignment: Text.AlignHCenter
            selectByMouse: false
            cursorVisible: true
            readOnly: true
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
            width: parent.width * (7 / 10)
            height: parent.height * (1 / parent.rows)
            from: ConfigEditor.get_min_field_width()
            to: ConfigEditor.get_max_field_width()
            stepSize: 1
            // value: game_config.value("field_size/width", 20)
            value: ConfigEditor.get_field_width();
            onValueChanged: {
                ConfigEditor.update_config(
                    field_width_slider.value,
                    field_height_slider.value,
                    food_static_slider.value,
                    state_delay_slider.value
                );
            }
        }

        TextField {
            width: parent.width * (1 / 10)
            height: parent.height * (1 / parent.rows)
            color: "#ffffff"
            text: field_width_slider.value
            horizontalAlignment: Text.AlignHCenter
            persistentSelection: true
            activeFocusOnPress: false
            cursorVisible: true
            selectByMouse: false
            readOnly: true
            hoverEnabled: true
            placeholderTextColor: "#88000000"
            font.pointSize: 30
            background: Rectangle {
                color: "transparent" // Фон полностью прозрачный
                border.color: "transparent" // Убираем границу, если она есть
            }
        }

        TextField {
            width: parent.width * (2 / 10)
            height: parent.height * (1 / parent.rows)
            color: "#ffffff"
            text: "field height"
            horizontalAlignment: Text.AlignHCenter
            selectByMouse: false
            activeFocusOnPress: true
            overwriteMode: false
            cursorVisible: true
            readOnly: true
            font.pointSize: 30
            background: Rectangle {
                color: "transparent" // Фон полностью прозрачный
                border.color: "transparent" // Убираем границу, если она есть
            }
        }

        Slider {
            id: field_height_slider
            width: parent.width * (7 / 10)
            height: parent.height * (1 / parent.rows)
            from: ConfigEditor.get_min_field_height()
            to: ConfigEditor.get_max_field_height()
            stepSize: 1
            value: ConfigEditor.get_field_height();
            onValueChanged: {
                ConfigEditor.update_config(
                    field_width_slider.value,
                    field_height_slider.value,
                    food_static_slider.value,
                    state_delay_slider.value
                );
            }
        }


        TextField {
            width: parent.width * (1 / 10)
            height: parent.height * (1 / parent.rows)
            color: "#ffffff"
            text: field_height_slider.value
            horizontalAlignment: Text.AlignHCenter
            persistentSelection: true
            cursorVisible: true
            activeFocusOnPress: false
            selectByMouse: false
            readOnly: true
            hoverEnabled: true
            placeholderTextColor: "#88000000"
            font.pointSize: 30
            background: Rectangle {
                color: "transparent" // Фон полностью прозрачный
                border.color: "transparent" // Убираем границу, если она есть
            }
        }

        TextField {
            width: parent.width * (2 / 10)
            height: parent.height * (1 / parent.rows)
            color: "#ffffff"
            text: "food static"
            horizontalAlignment: Text.AlignHCenter
            selectByMouse: false
            readOnly: true
            cursorVisible: true
            font.pointSize: 30
            background: Rectangle {
                color: "transparent" // Фон полностью прозрачный
                border.color: "transparent" // Убираем границу, если она есть
            }
        }

        Slider {
            id: food_static_slider
            width: parent.width * (7 / 10)
            height: parent.height * (1 / parent.rows)
            from: ConfigEditor.get_min_food_static()
            to: ConfigEditor.get_max_food_static()
            stepSize: 1
            value: ConfigEditor.get_food_static();
            onValueChanged: {
                ConfigEditor.update_config(
                    field_width_slider.value,
                    field_height_slider.value,
                    food_static_slider.value,
                    state_delay_slider.value
                );
            }
        }

        TextField {
            width: parent.width * (1 / 10)
            height: parent.height * (1 / parent.rows)
            color: "#ffffff"
            text: food_static_slider.value
            horizontalAlignment: Text.AlignHCenter
            persistentSelection: true
            cursorVisible: true
            activeFocusOnPress: false
            selectByMouse: false
            readOnly: true
            hoverEnabled: true
            placeholderTextColor: "#88000000"
            font.pointSize: 30
            background: Rectangle {
                color: "transparent" // Фон полностью прозрачный
                border.color: "transparent" // Убираем границу, если она есть
            }
        }

        TextField {
            width: parent.width * (2 / 10)
            height: parent.height * (1 / parent.rows)
            color: "#ffffff"
            text: "state_delay (ms)"
            horizontalAlignment: Text.AlignHCenter
            selectByMouse: false
            readOnly: true
            cursorVisible: true
            font.pointSize: 30
            background: Rectangle {
                color: "transparent" // Фон полностью прозрачный
                border.color: "transparent" // Убираем границу, если она есть
            }
        }

        Slider {
            id: state_delay_slider
            width: parent.width * (7 / 10)
            height: parent.height * (1 / parent.rows)
            from: ConfigEditor.get_min_state_delay_ms()
            to: ConfigEditor.get_max_state_delay_ms()
            stepSize: 10
            value: ConfigEditor.get_state_delay_ms();
            onValueChanged: {
                ConfigEditor.update_config(
                    field_width_slider.value,
                    field_height_slider.value,
                    food_static_slider.value,
                    state_delay_slider.value
                );
            }
        }

        TextField {
            width: parent.width * (1 / 10)
            height: parent.height * (1 / parent.rows)
            color: "#ffffff"
            text: state_delay_slider.value
            horizontalAlignment: Text.AlignHCenter
            persistentSelection: true
            cursorVisible: true
            activeFocusOnPress: false
            selectByMouse: false
            readOnly: true
            hoverEnabled: true
            placeholderTextColor: "#88000000"
            font.pointSize: 30
            background: Rectangle {
                color: "transparent" // Фон полностью прозрачный
                border.color: "transparent" // Убираем границу, если она есть
            }
        }
    }
}
