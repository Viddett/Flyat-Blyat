import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    property alias value: slider.value
    property alias text: centerText.text

    Slider {
        id: slider
        orientation: Qt.Vertical
        anchors.fill: root
        background: Rectangle {
            id: sliderBg
            width: slider.width * 0.5
            height: parent.height
            anchors.centerIn: parent
            border.width: 1
            border.color: "white"
            radius: 5
            opacity: 0.5

            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: slider.value * sliderBg.height
                color: "#004d77"
            }

        }
        handle: Rectangle {
            id: sliderHandle
            x: slider.width / 2
            anchors.horizontalCenter: slider.horizontalCenter
            y: slider.visualPosition * (slider.availableHeight)
            width: slider.width
            height: width
            radius: width / 3
            opacity: 0.75
        }

        Text {
            id: centerText
            anchors.centerIn: parent
            color: "#004d77"
            font.pixelSize: sliderBg.width - 1
            font.letterSpacing: 10
            rotation: 270
        }
    }
}
