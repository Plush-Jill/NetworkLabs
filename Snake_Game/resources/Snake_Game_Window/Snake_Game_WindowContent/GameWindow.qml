import QtQuick
import QtQuick.Controls
import QtCore
import QtQml.Models
import QtQml

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

    Shortcut {
        sequence: "Escape"
        onActivated: loader.source = "MainMenu.qml"
    }

    property int grid_width: 8
    property int grid_height: 8


    Grid {
        id: in_game_field
        columns: InGameFieldState.get_field_cell_width()
        rows: InGameFieldState.get_field_cell_height()
        x: 460
        y: 40
        width: 1000
        height: 1000
        rowSpacing: 2
        columnSpacing: 2

        Repeater {
            id: field_cell_repeater
            model: InGameFieldState.get_field_cell_height() * InGameFieldState.get_field_cell_width()

            delegate: Rectangle {
                width: 50
                height: 50
                color: InGameFieldState.get_cell_color(index);
                border.color: "#000000"

                function update_color() {
                    console.log("item at " + index + " updated");
                    color = InGameFieldState.get_cell_color(index);
                }
            }
        }

        Connections {
            target: InGameFieldState
            function on_cell_changed(index) {
                console.log("Cell at index " + index + " trying to update.");
                var item = field_cell_repeater.itemAt(index);
                if (item) {
                    item.update_color();
                } else {
                    console.warn("Cell at index " + index + " is not available yet.");
                }
            }
        }
    }
}
