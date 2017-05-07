import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.1
import elmsoft.rail.backendObject 1.0

Item {

    Slider {
        id: slider
        x: 110
        y: 80
        width: 40
        height: 341
        to: 100
        clip: true
        value: BackedObject.controlValue
        orientation: Qt.Vertical

        onValueChanged: BackedObject.controlValue = value
    }

    RadioButton {
        id: radioButton
        x: 378
        y: 102
        text: qsTr("Outer Loop")
        checked: BackedObject.currentController == BackedObject.OUTER_LOOP
        onCheckedChanged: if (checked) BackedObject.currentController = BackedObject.OUTER_LOOP
    }

    RadioButton {
        id: radioButton1
        x: 378
        y: 159
        text: qsTr("Inner Loop")
        checked: BackedObject.currentController == BackedObject.INNER_LOOP
        onCheckedChanged: if (checked) BackedObject.currentController = BackedObject.INNER_LOOP
    }

    RadioButton {
        id: radioButton2
        x: 378
        y: 220
        text: qsTr("Station Outer")
        checked: BackedObject.currentController == BackedObject.STATION_OUTER
        onCheckedChanged: if (checked) BackedObject.currentController = BackedObject.STATION_OUTER
    }

    RadioButton {
        id: radioButton3
        x: 378
        y: 280
        text: qsTr("Station Inner")
        checked: BackedObject.currentController == BackedObject.STATION_INNER
        onCheckedChanged: if (checked) BackedObject.currentController = BackedObject.STATION_INNER
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
        text: BackedObject.controlValueText
    }
}
