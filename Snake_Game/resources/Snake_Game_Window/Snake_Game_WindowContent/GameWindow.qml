import QtQuick
import QtQuick.Controls
import QtCore
import QtQml.Models


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



    // property int gridWidth: configEditor.get_field_width()
    // property int gridHeight: configEditor.get_field_height()

    property int grid_width: 8
    property int grid_height: 8

    ListModel {
        id: cell_model
        // Component.onCompleted: {
        //     reset_grid(grid_width, grid_height)
        // }
    }

    function reset_grid(width, height) {
        cell_model.clear()
        for (let i = 0; i < width * height; i++) {
            cell_model.append({ hasFood: false, snakeSegment: false })
        }
        console.log("Model filled with:", cell_model.count, "items") // Отладка
    }

    function set_food_at(x, y) {
        let index = y * grid_width + x
        if (index >= 0 && index < cell_model.count) {
            cell_model.set(index, { hasFood: true, snakeSegment: false })
        }
    }

    function clear_food_at(x, y) {
        let index = y * grid_width + x
        if (index >= 0 && index < cell_model.count) {
            cell_model.set(index, { hasFood: false, snakeSegment: false })
        }
    }

    ListModel {
        id: game_field_grid_model

    }





    Grid {
        id: gameGrid1
        // columns: grid_width
        // rows: grid_height
        columns: InGameConfig.get_field_width()
        rows: InGameConfig.get_field_height()
        x: 434
        y: 124
        width: 830
        height: 766
        rowSpacing: 2
        columnSpacing: 2

        Repeater {
            // model: grid_width * grid_height
            model: InGameConfig.get_field_height() * InGameConfig.get_field_width()
            // model: 3 * 5

            delegate: Rectangle {
                width: gameGrid1.width / grid_width
                height: gameGrid1.height / grid_height
                color: "red"
                border.color: "#000000"
            }
        }
    }

    Button {
        x: 59
        y: 742
        width: 166
        height: 86
        text: "Add Food at (3, 3)"
        onClicked: set_food_at(3, 3)
    }

    Button {
        x: 36
        y: 872
        width: 212
        height: 88
        text: "Clear Food at (3, 3)"
        onClicked: clear_food_at(3, 3)
    }

    Button {
        x: 321
        y: 901
        width: 212
        height: 88
        text: "Reset Grid"
        onClicked: reset_grid(grid_width, grid_height)
    }

    // Grid {
    //     id: gameGrid
    //     x: 1409
    //     y: 513
    //     width: 451
    //     height: 410
    //     rows: 8
    //     rowSpacing: -2
    //     columns: 8
    //     columnSpacing: -2
    //
    //     Repeater {
    //         model: gameGrid.columns * gameGrid.rows
    //         Rectangle {
    //             width: 50
    //             height: 50
    //             color: "#d3d3d3"
    //             border.color: "#000000"
    //         }
    //     }
    // }
}
