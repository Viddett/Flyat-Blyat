import QtQuick 2.15
import QtQuick.Controls 2.15
import "Widgets"



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

    property QtObject backend
    Connections {
        target: backend
        function onControlUpdate(pitch, roll, speed) {
            pitchGauge.value = pitch
            rollGauge.value = roll
            powerGauge.value = speed
        }
    }

    Rectangle { id: background
        anchors.fill: parent
        color: "black"
        opacity: 0.8

        Text { id: welcomeText; text: "Welcome Comrade"
            font.pixelSize: 32
            color: "#e6ad3030"
            font.family: "Chernobyl"
            anchors.top: parent.top
            anchors.topMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
        }
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

        GaugeSlider {
            id: pitchGauge
            text: "Pitch"
            from: -1
            to: 1
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 30
            width: 30
        }
        GaugeSlider {
            id: rollGauge
            text: "Roll"
            from: -1
            to: 1
            anchors.left: pitchGauge.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 30
            width: 30
        }
        GaugeSlider {
            id: powerGauge
            text: "Power"
            from: 0
            to: 1
            anchors.left: rollGauge.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 30
            width: 30
        }
    }
}
