import QtQuick 2.15
import QtQuick.Controls 2.15

Column {
    id: rootCol
    property int rowHeight: 30
    property variant rowNames: ["row1", "row2", "row3"]
    property string title: "Title"
    property int currentIndex: 0

    Text {
        text: rootCol.title
        color: c.lightBlue
        font.pixelSize: rootCol.rowHeight * 0.8
        Component.onCompleted: {
            visible: rootCol.title.length == 0
        }
    }

    Repeater {
        id: rootRepeater
        model: rowNames.length

        RadioButton {
            id: radioButton
            height: rootCol.rowHeight * 0.7
            width: height
            contentItem: Text {
                id: buttonText
                text: rowNames[index]
                opacity: enabled ? 1.0 : 0.7
                color: c.lightBlue
                font.pixelSize: parent.height * 0.8
                verticalAlignment: Text.AlignVCenter
                leftPadding: radioButton.indicator.width + radioButton.spacing
            }
            indicator: Rectangle {
                id: buttonIndicator
                height: rootCol.rowHeight
                width: height
                anchors.verticalCenter: parent.verticalCenter
                radius: 0.8 * (height / 2)
                border.color: c.lightBlue
                border.width: 3
                color: c.lightGray

                Rectangle {
                    id: activeIndicator
                    height: parent.height * 0.5
                    width: height
                    anchors.centerIn: parent
                    radius: height * (parent.radius / parent.height)
                    color: radioButton.down ? c.lightBlue : c.darkBlue
                    visible: radioButton.checked
                }
            }
        }
    }
}
