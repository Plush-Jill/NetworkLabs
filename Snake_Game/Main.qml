import QtQuick

Window {
    width: 1920
    height: 1080
    visible: true
    color: "#851616"
    visibility: Window.FullScreen
    flags: Qt.Window
    title: qsTr("Hello World")

    Image {
        id: image
        x: 63
        y: 51
        width: 441
        height: 248
        source: "qrc:/wallpapers.png"
        fillMode: Image.PreserveAspectFit
    }
}
