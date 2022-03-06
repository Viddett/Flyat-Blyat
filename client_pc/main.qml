import QtQuick 2.15
import QtQuick.Controls 2.15
import "widgets"
import "gfx"

ApplicationWindow {
    id: root
    visible: true
    width: 1200
    maximumWidth: width
    minimumWidth: width
    height: 800
    maximumHeight: height
    minimumHeight: maximumHeight
    title: "FlyatBlyat Control Centre"

    property int globalMargin: 30

    Constants { id: c }

    property QtObject serialCom
    Connections {
        id: backendConnection
        target: serialCom

        function onPitchUpdate(pitch) {
            pitchGauge.value = pitch
        }
        function onRollUpdate(roll) {
            rollGauge.value = roll
        }
        function onSpeedUpdate(speed) {
            speedGauge.value = speed
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
        function onPitchTrimUpdate(pitchTrimValue) {
            pitchTrim.trimValue = pitchTrimValue
        }
        function onRollTrimUpdate(rollTrimValue) {
            rollTrim.trimValue = rollTrimValue
        }
        function onSpeedTrimUpdate(speedTrimValue) {
            speedTrim.trimValue = speedTrimValue
        }
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: c.darkBlue

        Image {
            source: "gfx/flyatblyat.png"
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            opacity: 0.1
        }

        Text { text: "FlyatClient v0.1"; color: "gray"; font.pixelSize: 12; font.family: "Chernobyl"; padding: 5; anchors.right: parent.right; anchors.bottom: parent.bottom }


        Rectangle {
            id: pitchBg
            anchors.top: background.top
            anchors.topMargin: 100
            anchors.left: background.left
            anchors.leftMargin: 100
            width: pitchGauge.width + speedTrim.height + 3.5 * globalMargin
            height: 400
            color: c.lightBlue
            radius: 5

            GaugeSlider {
                id: pitchGauge
                text: "Pitch"
                from: -1
                to: 1
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: globalMargin
                width: 30
            }
            TrimSlider {
                id: pitchTrim
                from: -1
                to: 1
                stepSize: 0.1
                orientation: pitchTrim.vertical
                anchors.bottom: parent.bottom
                anchors.left: pitchGauge.right
                anchors.margins: globalMargin
                width: pitchGauge.height
                height: 30
                onTrimValueChanged: {
                    serialCom.setTrim("pitch", trimValue)
                }
            }
        }

        Rectangle {
            id: powerBg
            anchors.top: pitchBg.top
            anchors.left: pitchBg.right
            anchors.leftMargin: globalMargin
            width: speedGauge.width + speedTrim.height + 3.5 * globalMargin
            height: 400
            color: c.lightBlue
            radius: 5

            GaugeSlider {
                id: speedGauge
                text: "Speed"
                from: 0
                to: 1
                anchors.left: powerBg.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 30
                width: 30
            }
            TrimSlider {
                id: speedTrim
                from: 0
                to: 1
                stepSize: 0.05
                orientation: speedTrim.vertical
                anchors.bottom: parent.bottom
                anchors.left: speedGauge.right
                anchors.margins: globalMargin
                width: speedGauge.height
                height: 30
                onTrimValueChanged: {
                    serialCom.setTrim("speed", trimValue)
                }
            }
        }
        Rectangle {
            id: rollBg
            anchors.top: pitchBg.bottom
            anchors.topMargin: globalMargin
            anchors.left: pitchBg.left
            anchors.right: powerBg.right
            height: rollGauge.width + rollTrim.height + 3 * globalMargin
            color: c.lightBlue
            radius: 5

            GaugeSlider {
                id: rollGauge
                text: "Roll"
                from: -1
                to: 1
                anchors.left: rollBg.left
                anchors.leftMargin: height
                anchors.top: parent.top
                height: rollBg.width - 2 * globalMargin
                anchors.margins: 30
                width: 30
                transform: Rotation {
                    origin.x: rollGauge.width / 2
                    origin.y: rollGauge.width / 2
                    angle: 90
                }
            }
            TrimSlider {
                id: rollTrim
                from: -1
                to: 1
                stepSize: 0.1
                orientation: rollTrim.horizontal
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 1.5 * globalMargin
                anchors.left: parent.left
                anchors.margins: globalMargin
                width: rollGauge.height
                height: 30
                onTrimValueChanged: {
                    serialCom.setTrim("roll", trimValue)
                }
            }
        }

        Rectangle {
            id: comBg
            anchors.top: parent.top
            anchors.topMargin: globalMargin
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
            anchors.rightMargin: globalMargin
            anchors.top: background.top
            anchors.topMargin: globalMargin
            fillMode: Image.PreserveAspectFit
            height: comBg.height
            mipmap: true
        }

        FBradioButtonColumn {
            id: modeColumn
            anchors.top: comBg.bottom
            anchors.topMargin: globalMargin
            anchors.left: comBg.left
            title: "Flight Mode:"
            rowNames: ["Auto", "Manual"]
            rowHeight: 30
            spacing: globalMargin / 2
            onCurrentIndexChanged: {
                console.log("Selected button:", rowNames[currentIndex])
            }
        }
    }


}

