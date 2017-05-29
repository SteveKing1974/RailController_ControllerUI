import QtQuick 2.0
import QtQuick 2.7
import QtQuick.Controls 2.1
import elmsoft.rail.backendObject 1.0

Item {
    property QtObject myController: NULL
    property string controllerName: ""

    Item {
        id: titleBlock

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: 30

        Label {
            id: title
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom

            verticalAlignment: Text.AlignVCenter

            font.bold: true

            text: controllerName
        }
    }

    Item {
        id: headerBlock

        anchors.top: titleBlock.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        height: 30

        Label {
            id: speedLabel
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 10

            verticalAlignment: Text.AlignVCenter

            text: qsTr("Speed")
        }

        Label {
            id: speedValue
            anchors.top: parent.top
            anchors.left: speedLabel.right
            anchors.bottom: parent.bottom

            anchors.leftMargin: 10

            verticalAlignment: Text.AlignVCenter

            text: myController.controlValueText
        }
    }


    Item {
        anchors.top: headerBlock.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Switch {
            id: dirSwitch

            anchors.topMargin: 50
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: speedSlider.right

            enabled: myController.canChangeDirection

            text: checked ? qsTr("Forward") : qsTr("Backward")

            checked: myController.direction === Controller.CONTROLLER_FORWARD
        }

        Slider {
            id: speedSlider

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom

            width: 80

            clip: true
            orientation: Qt.Vertical
            to: 100
            enabled: myController.state === Controller.CONTROLLER_ON
            value: myController.controlValue
            onValueChanged: myController.controlValue = value
        }

        Button {
            id: upTwentyButton
            anchors.top: dirSwitch.bottom
            anchors.left: dirSwitch.left
            anchors.topMargin: 20

            onClicked: speedSlider.value = speedSlider.value + 20

            enabled: speedSlider.enabled
            text: qsTr("^^")
        }

        Button {
            id: downTwentyButton
            anchors.top: upTwentyButton.bottom
            anchors.left: upTwentyButton.left
            anchors.topMargin: 20

            onClicked: speedSlider.value = speedSlider.value - 20

            enabled: speedSlider.enabled
            text: qsTr("vv")
        }

        Button {
            id: stopButton
            anchors.top: downTwentyButton.bottom
            anchors.left: downTwentyButton.left
            anchors.topMargin: 20

            onClicked: speedSlider.value = 0

            enabled: speedSlider.enabled
            text: qsTr("Stop")
        }
    }
}
