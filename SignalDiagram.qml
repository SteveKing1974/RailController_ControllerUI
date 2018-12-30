import QtQuick 2.0
import elmsoft.rail.backendObject 1.0


Item
{
    function drawPoints(ctxLocal, startX, startY, width, height, nodeName)
    {
        var pointColour = BackendObject.getNode(nodeName).nodeColor;
        var oldStyle = ctxLocal.strokeStyle
        ctxLocal.beginPath();
        ctxLocal.strokeStyle = pointColour;

        ctxLocal.moveTo(startX, startY);
        ctxLocal.bezierCurveTo(startX + width/2, startY, startX + width/2, startY+height, startX + width, startY+height);
        ctxLocal.stroke();

        ctxLocal.strokeStyle = oldStyle;
    }

    function drawBreak(ctxLocal, startX, startY, leftNodeNode, rightNodeName)
    {
        var oldStyle = ctxLocal.strokeStyle

        ctxLocal.beginPath();
        ctxLocal.strokeStyle = BackendObject.getNode(leftNodeNode).nodeColor;
        ctxLocal.arc(startX, startY+10, 10, 3*Math.PI/2.0, 11*Math.PI/6, false);
        ctxLocal.stroke();
        ctxLocal.beginPath();
        ctxLocal.strokeStyle = BackendObject.getNode(rightNodeName).nodeColor;
        ctxLocal.arc(startX+20, startY-10, 10, Math.PI/2, 5*Math.PI/6, false);
        ctxLocal.stroke();
        ctxLocal.strokeStyle = oldStyle;
    }

    function drawLine(ctxLocal, startX, startY, endX, endY, nodeName)
    {
        var alineColour = BackendObject.getNode(nodeName).nodeColor;
        var oldStyle = ctxLocal.strokeStyle

        ctxLocal.beginPath()
        ctxLocal.strokeStyle = alineColour;

        ctxLocal.moveTo(startX, startY)
        ctxLocal.lineTo(endX, endY)

        ctxLocal.stroke()
        ctxLocal.strokeStyle = oldStyle;
    }


    id: mainContainer

    onVisibleChanged: if (visible) BackendObject.refreshPanel()

    Connections {
        target: BackendObject
        onPanelChanged: {
            drawingCanvas.requestPaint()
        }
    }

    Canvas
    {
        id: drawingCanvas
        anchors.fill: parent

        onPaint:
        {
            var ctx = getContext("2d")

            var trackGap = 50
            var bottomMargin = 10
            var leftMargin = 20
            var rightMargin = 20

            ctx.fillStyle = "white"
            ctx.fillRect(0,0,drawingCanvas.width ,drawingCanvas.height )
            ctx.lineWidth = 2;

            // Outer line
            var trackY = drawingCanvas.height - bottomMargin;

            drawLine(ctx, leftMargin, trackY, leftMargin*5, trackY, BackendObject.getKeys().outerLeft());
            drawLine(ctx, leftMargin*5, trackY, drawingCanvas.width - rightMargin*5, trackY, BackendObject.getKeys().outerCenter());
            drawLine(ctx, drawingCanvas.width - rightMargin*5, trackY, drawingCanvas.width - rightMargin, trackY, BackendObject.getKeys().outerRight());

            drawPoints(ctx, leftMargin*5, trackY - 5, 100, -1*(trackGap-10), BackendObject.getKeys().outerToInnerLeft())
            drawPoints(ctx, drawingCanvas.width - rightMargin*5, trackY - 5, -100, -1*(trackGap-10), BackendObject.getKeys().outerToInnerRight())

//            // Inner line
            trackY = drawingCanvas.height - bottomMargin - trackGap;

            drawLine(ctx, leftMargin, trackY, 200, trackY, BackendObject.getKeys().innerLeft());
            drawLine(ctx, 200, trackY, drawingCanvas.width - rightMargin*11, trackY, BackendObject.getKeys().innerCenter());
            drawLine(ctx, drawingCanvas.width - rightMargin*11, trackY, drawingCanvas.width - rightMargin, trackY, BackendObject.getKeys().innerRight());

            drawPoints(ctx, drawingCanvas.width - rightMargin*12, trackY - 5, -100, -1*(trackGap-10), BackendObject.getKeys().innerToStation())

//            // Station outer line
            trackY = drawingCanvas.height - bottomMargin - 2*trackGap;

            drawBreak(ctx, drawingCanvas.width  - rightMargin*4 - 150, trackY, BackendObject.getKeys().stationSidingRight1Entrance(), BackendObject.getKeys().stationSidingRight1())

            drawLine(ctx, leftMargin*8, trackY, leftMargin*12, trackY, BackendObject.getKeys().stationOuterLeft());
            drawLine(ctx, leftMargin*12, trackY, drawingCanvas.width - rightMargin*18, trackY, BackendObject.getKeys().stationOuterCenter());
            drawLine(ctx, drawingCanvas.width - rightMargin*18, trackY, drawingCanvas.width  - rightMargin*4 - 150, trackY, BackendObject.getKeys().stationOuterBetweenPoints());
            drawLine(ctx, drawingCanvas.width  - rightMargin*4 - 130, trackY, drawingCanvas.width  - rightMargin*4 + 50, trackY, BackendObject.getKeys().stationSidingRight1());

            drawPoints(ctx, leftMargin*12, drawingCanvas.height - bottomMargin - 2*trackGap - 5, 100, -1*(trackGap-10), BackendObject.getKeys().stationOuterToInnerLeft())
            drawPoints(ctx, drawingCanvas.width - rightMargin*18, drawingCanvas.height - bottomMargin - 2*trackGap - 5, -100, -1*(trackGap-10), BackendObject.getKeys().stationOuterToInnerRight())

            // Station inner line
            trackY = drawingCanvas.height - bottomMargin - 3*trackGap;

            drawBreak(ctx, drawingCanvas.width - rightMargin*15 - 100, drawingCanvas.height - bottomMargin - 3*trackGap, BackendObject.getKeys().stationInnerRight(), BackendObject.getKeys().stationInnerRightSiding())
            drawLine(ctx, leftMargin*2, trackY, leftMargin*15, trackY, BackendObject.getKeys().stationSidingLeft1());
            drawLine(ctx, leftMargin*15, trackY, drawingCanvas.width - rightMargin*15-100, trackY, BackendObject.getKeys().stationInnerCenter());
            drawLine(ctx, drawingCanvas.width - rightMargin*15-80, trackY, drawingCanvas.width - rightMargin*15, trackY, BackendObject.getKeys().stationInnerRightSiding());

            // Now the sidings left
            drawPoints(ctx, leftMargin*15, drawingCanvas.height - bottomMargin - 3*trackGap - 5, -100, -1*(trackGap-10), BackendObject.getKeys().dummyLeftBetweenSidings())
            drawPoints(ctx, leftMargin*10, drawingCanvas.height - bottomMargin - 4*trackGap , -100, -1*(trackGap-10), BackendObject.getKeys().stationSidingLeft3Entrance())

            drawBreak(ctx, leftMargin*10 - 120, drawingCanvas.height - bottomMargin - 5*trackGap + 10, BackendObject.getKeys().stationSidingLeft3(), BackendObject.getKeys().stationSidingLeft3Entrance())

            drawLine(ctx, leftMargin*2, drawingCanvas.height - bottomMargin - 4*trackGap + 5,
                     leftMargin*15 - 100, drawingCanvas.height - bottomMargin - 4*trackGap + 5, BackendObject.getKeys().stationSidingLeft2());
            drawLine(ctx, leftMargin*2, drawingCanvas.height - bottomMargin - 5*trackGap + 10,
                     leftMargin*10 - 120, drawingCanvas.height - bottomMargin - 5*trackGap + 10, BackendObject.getKeys().stationSidingLeft3());


            // Sidings on the right
            drawPoints(ctx, drawingCanvas.width - rightMargin*14, drawingCanvas.height - bottomMargin - 2*trackGap - 5, 100, -1*(trackGap-10), BackendObject.getKeys().dummyRightBetweenSidings())
            drawPoints(ctx, drawingCanvas.width - rightMargin*9, drawingCanvas.height - bottomMargin - 3*trackGap, 100, -1*(trackGap-10), BackendObject.getKeys().stationSidingRight3Entrance())

            drawBreak(ctx, drawingCanvas.width - rightMargin*4, drawingCanvas.height - bottomMargin - 4*trackGap + 10, BackendObject.getKeys().stationSidingRight3Entrance(), BackendObject.getKeys().stationSidingRight3())

            drawLine(ctx, drawingCanvas.width - rightMargin*9, drawingCanvas.height - bottomMargin - 3*trackGap + 5,
                     drawingCanvas.width - rightMargin*4 + 50, drawingCanvas.height - bottomMargin - 3*trackGap + 5, BackendObject.getKeys().stationSidingRight2());
            drawLine(ctx, drawingCanvas.width - rightMargin*4 + 20, drawingCanvas.height - bottomMargin - 4*trackGap + 10,
                     drawingCanvas.width - rightMargin*4 + 50, drawingCanvas.height - bottomMargin - 4*trackGap + 10, BackendObject.getKeys().stationSidingRight3());

        }
    }
}
