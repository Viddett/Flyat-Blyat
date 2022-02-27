import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    property int vertical: 0
    property int horizontal: 1
    property int orientation: horizontal
    property alias from: slider.from
    property alias to: slider.to
    property alias stepSize: slider.stepSize
    property alias trimValue: slider.value

    Constants {
        id: c
    }

    Slider {
        id: slider
        anchors.fill: root
        stepSize: stepSize

        background: Rectangle {
            id: sliderBg
            width: parent.width
            height: parent.height * 0.2
            anchors.centerIn: parent
            color: c.darkBlue

            Row {
                id: tickColumn
                anchors.verticalCenter: sliderBg.verticalCenter
                anchors.horizontalCenter: sliderBg.horizontalCenter
                anchors.fill: parent
                Repeater {
                    id: repeater
                    model: slider.stepSize > 0 ? 1 + (slider.to - slider.from) / slider.stepSize : 0
                    anchors.fill: parent
                    Rectangle {
                        id: tick
                        color: c.lightGray
                        width: 2
                        height: index % 2 == 0 ? 8 : 5
                        y: repeater.height / 2
                        x: ( index * ((repeater.width) / (repeater.count-1)) ) - index *  width/(repeater.count-1)
                        Text {
                            id: tickText
                            text: index % 2 == 0 ? (slider.from + (index * slider.stepSize)).toPrecision(1)*100 : ""
                            y: tick.y * 6
                            anchors.horizontalCenter: tick.horizontalCenter
                            color: c.lightGray
                            font.pixelSize: tick.width * 6
                            transform: Rotation {
                                origin.x: tickText.width / 2
                                origin.y: tickText.height / 2
                                angle: orientation ?? vertical ? 0 : 90
                            }
                        }
                    }
                }
            }
        }

        handle: Rectangle {
            id: sliderHandle
            height: parent.height
            width:  height / 3
            color: c.lightGray
            anchors.verticalCenter: slider.verticalCenter
            x: slider.visualPosition * slider.width - (width / 2)
        }

    }
    transform: Rotation {
        origin.x: slider.height / 2
        origin.y: slider.height / 2
        angle: orientation == vertical ? -90 : 0
    }
}
