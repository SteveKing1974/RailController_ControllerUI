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

        SignalLever {
            leverId: BackendObject.getKeys().upMainCrossover();
        }
        SignalLever {
            leverId: BackendObject.getKeys().downMainCrossover();
        }
        SignalLever {
            leverId: BackendObject.getKeys().stationEntranceCrossover();
        }
        SignalLever {
            leverId: BackendObject.getKeys().downStationCrossover();
        }
        SignalLever {
            leverId: BackendObject.getKeys().upStationCrossover();
        }
        SignalLever {
            leverId: BackendObject.getKeys().upSiding1();
        }
        SignalLever {
            leverId: BackendObject.getKeys().upSiding2();
        }
        SignalLever {
            leverId: BackendObject.getKeys().downSiding1();
        }
        SignalLever {
            leverId: BackendObject.getKeys().downSiding2();
        }
        SignalLever {
            leverId: BackendObject.getKeys().topSidingUp();
        }
        SignalLever {
            leverId: BackendObject.getKeys().stationSidingDown();
        }
        SignalLever {
            leverId: BackendObject.getKeys().bottomSidingDown();
        }
        SignalLever {
            leverId: BackendObject.getKeys().topSidingDown();
        }
    }
}
