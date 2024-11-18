import QtQuick
import QtQuick.Controls



Item {

    width: 1920
    height: 1080
    objectName: JoinWindow

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#431515"
    }

    CurrentGamesTable {
        anchors.leftMargin: 703
        anchors.rightMargin: 905
        anchors.topMargin: 381
        anchors.bottomMargin: 469

    }


}
