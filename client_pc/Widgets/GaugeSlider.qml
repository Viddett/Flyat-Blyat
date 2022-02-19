import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    property alias value: slider.value
    property string text: ""
    property alias from: slider.from
    property alias to: slider.to

    Constants {
        id: c
    }

    Slider {
        id: slider
        orientation: Qt.Vertical
        anchors.fill: root
        background: Rectangle {
            id: sliderBg
            width: parent.width * 0.5
            height: parent.height
            anchors.centerIn: parent
            color: c.appBg
            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: parent.height - sliderHandle.y
                color: c.darkBlue
            }
            Text {
                id: centerText
                text: root.text + " " + parseInt(100*slider.value) + "%"
                color: c.lightGray
                height: parent.width
                x: 0
                y: parent.height
                horizontalAlignment: Text.AlignLeft
                leftPadding: 10
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: sliderBg.width - 1
                font.letterSpacing: 10
                transform: Rotation {
                    origin.x: 0
                    origin.y: 0
                    angle: 270
                }
            }
        }
        handle: Rectangle {
            id: sliderHandle
            visible: false
            x: slider.width / 2
            anchors.horizontalCenter: slider.horizontalCenter
            y: slider.visualPosition * slider.height
            width: slider.width
            height: width / 3
            radius: width / 3
        }
    }
}
