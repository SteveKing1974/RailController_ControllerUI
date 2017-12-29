import QtQuick 2.0

import elmsoft.rail.backendObject 1.0

Item {
    onVisibleChanged: if (visible) BackendObject.refreshControllers()
    ControllerItem {
        id: outer
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        controllerName: "Outer Loop"

        width: 250

        myController: BackendObject.getController(BackendObject.getKeys().outerLoop())
    }

    ControllerItem {
        id: inner

        anchors.top: parent.top
        anchors.left: outer.right
        anchors.bottom: parent.bottom

        controllerName: "Inner Loop"

        width: 250

        myController: BackendObject.getController(BackendObject.getKeys().innerLoop())
    }

    ControllerItem {
        id: stationOuter
        anchors.top: parent.top
        anchors.left: inner.right
        anchors.bottom: parent.bottom

        controllerName: "Station Outer"

        width: 250

        myController: BackendObject.getController(BackendObject.getKeys().stationOuter())
    }

    ControllerItem {
        id: stationInner
        anchors.top: parent.top
        anchors.left: stationOuter.right
        anchors.bottom: parent.bottom

        controllerName: "Station Inner"

        width: 250

        myController: BackendObject.getController(BackendObject.getKeys().stationInner())
    }
}
