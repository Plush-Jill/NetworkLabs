

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls

// import Snake_Game_Window 1.0
Item {
    width: 1920
    height: 1080

    objectName: MainMenu
    // width: parent.width
    // height: parent.height



    Loader {
        id: loader
    }

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#431515"
    }

    AnimatedImage {
        id: animatedImage
        x: 946
        y: 40
        width: 900
        height: 136
        source: "resources/Solid_Snake_2.gif"
    }

    AnimatedImage {
        id: animatedImage1
        x: 1238
        y: 198
        width: 608
        height: 404
        source: "resources/Solid_Snake_3.gif"
        playing: true
    }

    AnimatedImage {
        id: animatedImage2
        x: 1458
        y: 628
        width: 388
        height: 312
        source: "resources/Kris.gif"
    }

    Column {
        id: main_menu_column
        x: 24
        y: 412
        width: 452
        height: 508
        spacing: 10
        readonly property int main_menu_button_height: 90

        Shortcut {
            sequence: "Escape"
            onActivated: Qt.quit()
        }

        Shortcut {
            sequence: "4"
            onActivated: exit_button.clicked()
        }

        Button {
            id: host_new_game_button
            width: parent.width
            height: 90
            text: "Host new game"
            font.pointSize: 26
            font.family: "Arial"
            flat: false
            enabled: true
            display: AbstractButton.TextBesideIcon
            checked: false
            checkable: false
            autoRepeat: false
            autoExclusive: false
        }

        Button {
            id: join_game_button
            width: parent.width
            height: 90
            text: "Join game"
            font.pointSize: 26
            font.family: "Arial"
            flat: false
            enabled: true
            display: AbstractButton.TextBesideIcon
            checked: false
            checkable: false
            autoRepeat: false
            autoExclusive: false
        }

        Button {
            id: options_button
            width: parent.width
            height: 90
            text: "Options (edit config)"
            font.pointSize: 26
            font.family: "Arial"
            flat: false
            enabled: true
            display: AbstractButton.TextBesideIcon
            checked: false
            checkable: false
            autoRepeat: false
            autoExclusive: false
            // Загружаем экран настроек в Loader
            // onClicked: {
            //     loader.set("Options.qml")
            // }
            onClicked: loader.source = "Options.qml" // Переход к опциям
        }

        Button {
            id: exit_button
            width: parent.width
            height: 90
            text: "Exit"
            font.pointSize: 26
            font.family: "Arial"
            flat: false
            enabled: true
            display: AbstractButton.TextBesideIcon
            checked: false
            checkable: false
            autoRepeat: false
            autoExclusive: false
            onClicked: Qt.quit()
        }
    }
}
