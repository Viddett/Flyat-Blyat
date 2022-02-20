import QtQuick 2.15
import QtQuick.Controls 2.15
import "widgets"
import "gfx"

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

    property int globalPadding: 30

    Constants { id: c }

    property QtObject serialCom
    Connections {
        target: serialCom

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

        function onGamepadStatus(status) {
            gamepadImage.source = status ? "gfx/xbox_gamepad_green" : "gfx/xbox_gamepad_red"
        }
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: c.appBg

        Text { id: welcomeText; text: "Privyet Comrade"
            font.pixelSize: 32
            color: c.sovietRed
            font.family: "Chernobyl"
            anchors.top: parent.top
            anchors.topMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text { text: "FlyatClient v0.1"; color: "gray"; font.pixelSize: 12; font.family: "Chernobyl"; padding: 5; anchors.right: parent.right; anchors.bottom: parent.bottom }

        Rectangle {
            id: gaugeBg
            anchors.top: parent.top
            anchors.topMargin: globalPadding
            anchors.left: parent.left
            anchors.leftMargin: -radius
            width: parent.width * 0.18
            height: parent.height * 0.4
            color: c.lightBlue
            radius: 5
            GaugeSlider {
                id: pitchGauge
                text: "Pitch"
                from: -1
                to: 1
                anchors.right: rollGauge.left
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
                anchors.right: powerGauge.left
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
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 30
                width: 30
            }
        }


        Rectangle {
            id: comBg
            anchors.top: parent.top
            anchors.topMargin: globalPadding
            anchors.right: parent.right
            anchors.rightMargin: -radius
            width: 180
            height: 70
            color: c.lightBlue
            radius: 5

            ComboBox {
                id: comBox
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.left: parent.left
                anchors.margins: 10
                width: parent.width * 0.7
                height: 30
                model: ListModel {
                    id: comBoxModel
                }
                onCurrentIndexChanged: {
                    if (comBoxModel.count > 0)
                        serialCom.setComPort(comBoxModel.get(currentIndex).text)
                }

                Text {
                    id: comText
                    text: "COM port"
                    color: c.lightGray
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
                        radius: 2
                        color: c.darkBlue
                    }
                    Text {
                        anchors.centerIn: parent
                        text: "Refresh"
                        color: c.lightGray
                    }
                    onPressed: comBoxButtonBg.color = c.lightBlue
                    onReleased:  comBoxButtonBg.color = c.darkBlue
                    onClicked: serialCom.refreshComPorts()
                }
            }
        }
        Image {
            id: gamepadImage
            anchors.right: comBg.left
            anchors.rightMargin: globalPadding
            anchors.top: background.top
            anchors.topMargin: globalPadding
            fillMode: Image.PreserveAspectFit
            height: comBg.height
            mipmap: true
        }
    }
}
