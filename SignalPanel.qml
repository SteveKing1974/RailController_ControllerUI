import QtQuick 2.0
import QtQuick.Layouts 1.3
import elmsoft.rail.backendObject 1.0

Item {

    SignalDiagram
    {
        id: diagram
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 280
    }

    RowLayout {
        anchors.top: diagram.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        anchors.rightMargin: 10

        spacing: 6

        Image {
            source: 'images/resources/png/upmaincrossoverlever_off.png'
        }
        Image {
            source: 'images/resources/png/downmaincrossoverlever_off.png'
        }
        Image {
            source: 'images/resources/png/stationentrancelever_off.png'
        }
        Image {
            source: 'images/resources/png/downstationcrossoverlever_off.png'
        }
        Image {
            source: 'images/resources/png/upstationcrossoverlever_off.png'
        }
        Image {
            source: 'images/resources/png/upsiding1lever_off.png'
        }
        Image {
            source: 'images/resources/png/upsiding2lever_off.png'
        }
        Image {
            source: 'images/resources/png/downsiding1lever_off.png'
        }
        Image {
            source: 'images/resources/png/downsiding2lever_off.png'
        }
        Image {
            source: 'images/resources/png/upsidinglever_off.png'
        }
        Image {
            source: 'images/resources/png/stationsidinglever_off.png'
        }
        Image {
            source: 'images/resources/png/downsidinglowerlever_off.png'
        }
        Image {
            source: 'images/resources/png/downsidingupperlever_off.png'
        }
    }
}
