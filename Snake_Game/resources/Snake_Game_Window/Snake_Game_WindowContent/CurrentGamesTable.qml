// CurrentGamesTable.qml

import QtQuick
import QtQuick.Controls
import Qt.labs.qmlmodels

TableView {
    anchors.fill: parent
    columnSpacing: 1
    rowSpacing: 1
    clip: true

    model: TableModel {
        TableModelColumn {
            display: "IP"
        }
        TableModelColumn {
            display: "port"
        }
        TableModelColumn {
            display: "field_width"
        }
        TableModelColumn {
            display: "field_hight"
        }
        TableModelColumn {
            display: "food_static"
        }
        TableModelColumn {
            display: "players"
        }
    }

    delegate: Rectangle {
        implicitWidth: 100
        implicitHeight: 50
        border.width: 1

        Text {
            text: display
            anchors.centerIn: parent
        }
    }
}
