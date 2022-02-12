import QtQuick 2.15
import QtQuick.Controls 2.15


ApplicationWindow {
    id: root
    visible: true
    property int fixedHeight: 800
    property int fixedWidth: 1200
    width: fixedWidth
    maximumWidth: fixedWidth
    minimumWidth: fixedWidth
    height: fixedHeight
    maximumHeight: fixedHeight
    minimumHeight: fixedHeight
    title: "FlyatBlyat Control Centre"

    Rectangle { id: background; anchors.fill: parent; color: "black"; opacity: 0.8 }
    Text { id: welcomeText; text: "Welcome Comrade"; font.pixelSize: 32; color: "#e6ad3030"; font.family: "Chernobyl"; anchors.centerIn: parent }
    Text { text: "FlyatClient v0.1"; color: "gray"; font.pixelSize: 12; font.family: "Chernobyl"; padding: 5; anchors.right: parent.right; anchors.bottom: parent.bottom }

    MouseArea {
        id: mouseArea
        anchors.fill: background
        onClicked: {
            colorTimer.stop()
        }
    }

    Timer {
        id: colorTimer
        interval: 50
        property double r: 0.5
        property double g: 0.5
        property double b: 0.5
        onTriggered: {
            r = r + ( Math.random() - 0.5) * 2 / 100
            g = g + ( Math.random() - 0.5) * 2 / 100
            b = b + ( Math.random() - 0.5) * 2 / 100
            welcomeText.color = Qt.rgba(r, g, b, 1)
            restart()
        }
        Component.onCompleted: {
            start()
        }
    }
}
