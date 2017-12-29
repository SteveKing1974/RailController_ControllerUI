import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import elmsoft.rail.backendObject 1.0

ApplicationWindow {
    visible: true
    width: 1000
    height: 480
    title: qsTr("Hello World")

    Item {
        id: panelItem

        visible: false

        anchors.top: parent.top;
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: selectSwitch.top

        SignalDiagram
        {
            visible: !selectSwitch.checked
            anchors.fill: parent
        }

        ControlPanel {
            visible: selectSwitch.checked
            anchors.fill: parent
        }
    }



    Switch {
        id: selectSwitch

        height: 50
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left


        text: qsTr("Controllers")

        checked: false
    }

    Component.onCompleted: panelItem.visible = true
}

