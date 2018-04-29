import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import elmsoft.rail.backendObject 1.0

ApplicationWindow {
    visible: true
    width: 1200
    height: 680
    title: qsTr("Hello World")

    Switch {
        id: selectSwitch

        height: 50
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left


        text: qsTr("Controllers")

        checked: false
    }


    Item {
        id: panelItem

        visible: false

        anchors.top: selectSwitch.bottom;
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        SignalPanel
        {
            visible: !selectSwitch.checked
            anchors.fill: parent
        }

        ControlPanel {
            visible: selectSwitch.checked
            anchors.fill: parent
        }
    }

    Component.onCompleted: panelItem.visible = true
}

