import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.1

Item {

    RowLayout {
        clip: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        anchors.top: parent.top
    }

    Slider {
        id: slider
        x: 110
        y: 80
        width: 40
        height: 341
        clip: true
        orientation: Qt.Vertical
    }

    RadioButton {
        id: radioButton
        x: 378
        y: 102
        text: qsTr("Outer Loop")
    }

    RadioButton {
        id: radioButton1
        x: 378
        y: 159
        text: qsTr("Inner Loop")
    }

    RadioButton {
        id: radioButton2
        x: 378
        y: 220
        text: qsTr("Station Outer")
    }

    RadioButton {
        id: radioButton3
        x: 378
        y: 280
        text: qsTr("Station Inner")
    }

    Label {
        id: label
        x: 77
        y: 50
        text: qsTr("Speed")
    }

    Label {
        id: label1
        x: 144
        y: 50
    }
}
