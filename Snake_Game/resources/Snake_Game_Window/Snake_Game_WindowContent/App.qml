// App.qml
// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Controls 6.8


Window {
    width: 1920
    height: 1080
    visibility: Window.FullScreen
    visible: true
    color: "#431515"
    title: "Snake_Game_Window"


    Loader {
        id: loader
        anchors.fill: parent
        source: "MainMenu.qml"
        rotation: 0
    }
}

