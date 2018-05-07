import QtQuick 2.0
import elmsoft.rail.backendObject 1.0

Item {
    property string leverId: ""
    property QtObject myLever: BackendObject.getLever(leverId)

    width: leverImage.width
    height: leverImage.height

    MouseArea {
        anchors.fill: parent
        enabled: myLever.enabled

        onClicked: {
            myLever.toggle();
        }
    }

    Image {
        id: leverImage
        opacity: myLever.enabled ? 1 : 0.5
        source: 'images/resources/png/' + leverId + 'lever' + (myLever.pulled ? '_on' : '_off') + '.png';
    }
}
