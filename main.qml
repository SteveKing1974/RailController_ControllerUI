import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import elmsoft.rail.backendObject 1.0

ApplicationWindow {
    visible: true
    width: 1000
    height: 480
    title: qsTr("Hello World")


    ControllerItem {
        id: outer
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        controllerName: "Outer Loop"

        width: 250

        myController: BackendObject.getController(BackendObject.OUTER_LOOP)
    }

    ControllerItem {
        id: inner

        anchors.top: parent.top
        anchors.left: outer.right
        anchors.bottom: parent.bottom

        controllerName: "Inner Loop"

        width: 250

        myController: BackendObject.getController(BackendObject.INNER_LOOP)
    }

    ControllerItem {
        id: stationOuter
        anchors.top: parent.top
        anchors.left: inner.right
        anchors.bottom: parent.bottom

        controllerName: "Station Outer"

        width: 250

        myController: BackendObject.getController(BackendObject.STATION_OUTER)
    }

    ControllerItem {
        id: stationInner
        anchors.top: parent.top
        anchors.left: stationOuter.right
        anchors.bottom: parent.bottom

        controllerName: "Station Inner"

        width: 250

        myController: BackendObject.getController(BackendObject.STATION_INNER)
    }

}
