import QtQuick 2.0
import elmsoft.rail.backendObject 1.0

Item {
    property string leverId: ""
    property QtObject myLever: BackendObject.getLever(leverId)

    MouseArea {
        anchors.fill: parent
    }

    Image {
        anchors.fill: parent
        source: 'images/resources/png/' + leverId + '_off.png';
    }
}
