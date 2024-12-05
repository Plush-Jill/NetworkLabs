import QtQuick
import QtQuick.Controls
import QtCore
import QtQml.Models
import QtQml
import com.example.snake 1.0

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
    SnakeController {
        id: snake_controller
    }
    // InGameFieldView {
    //     id: view
    // }
    Shortcut {
        sequence: "Escape"
        onActivated: loader.source = "MainMenu.qml"
    }

    property int grid_width: 8
    property int grid_height: 8


    Grid {
        id: in_game_field
        columns: InGameFieldView.get_field_cell_width()
        rows: InGameFieldView.get_field_cell_height()
        x: 460
        y: 40
        width: 1000
        height: 1000
        rowSpacing: 2
        columnSpacing: 2

        Repeater {
            id: field_cell_repeater
            model: InGameFieldView.get_field_cell_height() * InGameFieldView.get_field_cell_width()

            delegate: Rectangle {
                width: 50
                height: 50
                // color: InGameFieldState.get_cell_color(index);
                color: "white"
                border.color: "#000000"
                // on_cell_changed: {
                //     update_color();
                // }
                function update_color() {
                    console.log("item at " + index + " updated");
                    color = InGameFieldView.get_cell_color(index);
                }
                Connections {
                    target: InGameFieldView

                    function onCellUpdated(idx) {
                        var rect = in_game_field.children[idx];
                        rect.color = InGameFieldView.get_cell_color(idx);
                    }
                }
            }
        }
    }

}
