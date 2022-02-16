import QtQuick 2.15
import QtQuick.Controls 2.15
import "Widgets"
import "Gfx"

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
        function onComBoxClear() {
            comBoxModel.clear()
        }
        function onComPortUpdate(comPort) {
            comBoxModel.append({text: comPort})
        }
    }

    Rectangle { id: background
        anchors.fill: parent
        color: "black"
        opacity: 0.8

        Text { id: welcomeText; text: "Privyet Comrade"
            font.pixelSize: 32
            color: "#CC0000"
            font.family: "Chernobyl"
            anchors.top: parent.top
            anchors.topMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text { text: "FlyatClient v0.1"; color: "gray"; font.pixelSize: 12; font.family: "Chernobyl"; padding: 5; anchors.right: parent.right; anchors.bottom: parent.bottom }


        GaugeSlider {
            id: pitchGauge
            text: "Pitch"
            from: -1
            to: 1
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 50
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
            anchors.margins: 50
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
            anchors.margins: 50
            width: 30
        }
        Rectangle {
            id: gaugeBg
            anchors.top: pitchGauge.top
            anchors.left: pitchGauge.left
            anchors.bottom: pitchGauge.bottom
            anchors.right: powerGauge.right
            anchors.margins: -20
            color: "white"
            opacity: 0.2
            radius: 5
        }


        ComboBox {
            id: comBox
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: 50
            width: 120
            height: 30
            model: ListModel {
                id: comBoxModel
            }
            onCurrentIndexChanged: {
                if (comBoxModel.count > 0)
                    backend.setComPort(comBoxModel.get(currentIndex).text)
            }

            Text {
                id: comText
                text: "COM port"
                color: "white"
                font.pixelSize: 15
                anchors.bottom: parent.top
                anchors.left: parent.left
                anchors.margins: 5
            }
            Button {
                anchors.right: comBox.right
                anchors.left: comText.right
                anchors.leftMargin: 8
                anchors.verticalCenter: comText.verticalCenter
                height: comText.height
                width: height
                background: Rectangle {
                    id: comBoxButtonBg
                    opacity: 0.9
                    radius: 2
                }
                Text {
                    anchors.centerIn: parent
                    text: "Refresh"
                }
                onPressed: comBoxButtonBg.color = "gray"
                onReleased:  comBoxButtonBg.color = "white"
                onClicked: backend.refreshComPorts()
            }

            Rectangle {
                anchors.top: comText.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                color: "white"
                opacity: 0.4
                radius: 5
                scale: 1.2
            }
        }
    }
}
