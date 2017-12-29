import QtQuick 2.0
import elmsoft.rail.backendObject 1.0


Item
{
    id: mainContainer
    height: 100
    width: 100
    x: 200
    y: 200

    onVisibleChanged: if (visible) BackendObject.refreshPanel()

    Canvas
    {
        id: drawingCanvas
        anchors.fill: parent

        function drawPoints(ctx, startX, startY, width, height)
        {
            ctx.beginPath();
            ctx.moveTo(startX, startY);
            ctx.bezierCurveTo(startX + width/2, startY, startX + width/2, startY+height, startX + width, startY+height);
            ctx.stroke();
        }

        function drawBreak(ctx, startX, startY, radius)
        {
            ctx.beginPath();
            ctx.arc(startX, startY+10, 10, 3*Math.PI/2.0, 11*Math.PI/6, false);
            ctx.stroke();
            ctx.beginPath();
            ctx.arc(startX+20, startY-10, 10, Math.PI/2, 5*Math.PI/6, false);
            ctx.stroke();
        }


        onPaint:
        {
            var ctx = getContext("2d")

            var trackGap = 50
            var bottomMargin = 70
            var leftMargin = 20
            var rightMargin = 20

            ctx.fillStyle = "white"
            ctx.fillRect(0,0,drawingCanvas.width ,drawingCanvas.height )
            ctx.lineWidth = 2;

            // Outer line
            ctx.strokeStyle = "red"
            ctx.beginPath()
            ctx.moveTo(leftMargin, drawingCanvas.height - bottomMargin)
            ctx.lineTo(drawingCanvas.width - rightMargin, drawingCanvas.height - bottomMargin)
            ctx.stroke()

            drawPoints(ctx, leftMargin*5, drawingCanvas.height - bottomMargin - 5, 100, -1*(trackGap-10))
            drawPoints(ctx, drawingCanvas.width - rightMargin*5, drawingCanvas.height - bottomMargin - 5, -100, -1*(trackGap-10))

            // Inner line
            ctx.strokeStyle = "green"
            ctx.beginPath()
            ctx.moveTo(leftMargin, drawingCanvas.height - bottomMargin - trackGap)
            ctx.lineTo(drawingCanvas.width - rightMargin, drawingCanvas.height - bottomMargin - trackGap)
            ctx.stroke()

            drawPoints(ctx, drawingCanvas.width - rightMargin*12, drawingCanvas.height - bottomMargin - trackGap - 5, -100, -1*(trackGap-10))

            // Station outer line
            ctx.strokeStyle = "blue"

            drawBreak(ctx, drawingCanvas.width  - rightMargin*4 - 150, drawingCanvas.height - bottomMargin - 2*trackGap)

            ctx.beginPath()
            ctx.moveTo(leftMargin*8, drawingCanvas.height - bottomMargin - 2*trackGap)
            ctx.lineTo(drawingCanvas.width  - rightMargin*4 - 150, drawingCanvas.height - bottomMargin - 2*trackGap)

            ctx.moveTo(drawingCanvas.width  - rightMargin*4 - 130, drawingCanvas.height - bottomMargin - 2*trackGap)
            ctx.lineTo(drawingCanvas.width  - rightMargin*4 + 50, drawingCanvas.height - bottomMargin - 2*trackGap)
            ctx.stroke()

            drawPoints(ctx, leftMargin*12, drawingCanvas.height - bottomMargin - 2*trackGap - 5, 100, -1*(trackGap-10))
            drawPoints(ctx, drawingCanvas.width - rightMargin*18, drawingCanvas.height - bottomMargin - 2*trackGap - 5, -100, -1*(trackGap-10))

            // Station inner line
            ctx.strokeStyle = "purple"

            drawBreak(ctx, drawingCanvas.width - rightMargin*15 - 100, drawingCanvas.height - bottomMargin - 3*trackGap)

            ctx.beginPath()
            ctx.moveTo(leftMargin*2, drawingCanvas.height - bottomMargin - 3*trackGap)
            ctx.lineTo(drawingCanvas.width - rightMargin*15 - 100, drawingCanvas.height - bottomMargin - 3*trackGap)
            ctx.moveTo(drawingCanvas.width - rightMargin*15 - 80, drawingCanvas.height - bottomMargin - 3*trackGap)
            ctx.lineTo(drawingCanvas.width - rightMargin*15, drawingCanvas.height - bottomMargin - 3*trackGap)
            ctx.stroke()

            // Now the sidings left
            drawPoints(ctx, leftMargin*15, drawingCanvas.height - bottomMargin - 3*trackGap - 5, -100, -1*(trackGap-10))
            drawPoints(ctx, leftMargin*10, drawingCanvas.height - bottomMargin - 4*trackGap , -100, -1*(trackGap-10))

            drawBreak(ctx, leftMargin*10 - 120, drawingCanvas.height - bottomMargin - 5*trackGap + 10)

            ctx.beginPath()
            ctx.moveTo(leftMargin*2, drawingCanvas.height - bottomMargin - 4*trackGap + 5)
            ctx.lineTo(leftMargin*15 - 100, drawingCanvas.height - bottomMargin - 4*trackGap + 5)
            ctx.moveTo(leftMargin*2, drawingCanvas.height - bottomMargin - 5*trackGap + 10)
            ctx.lineTo(leftMargin*10 - 120, drawingCanvas.height - bottomMargin - 5*trackGap + 10)
            ctx.stroke()

            // Sidings on the right
            ctx.strokeStyle = "blue"
            drawPoints(ctx, drawingCanvas.width - rightMargin*14, drawingCanvas.height - bottomMargin - 2*trackGap - 5, 100, -1*(trackGap-10))
            drawPoints(ctx, drawingCanvas.width - rightMargin*9, drawingCanvas.height - bottomMargin - 3*trackGap, 100, -1*(trackGap-10))

            drawBreak(ctx, drawingCanvas.width - rightMargin*4, drawingCanvas.height - bottomMargin - 4*trackGap + 10)

            ctx.beginPath()
            ctx.moveTo(drawingCanvas.width - rightMargin*9, drawingCanvas.height - bottomMargin - 3*trackGap + 5)
            ctx.lineTo(drawingCanvas.width - rightMargin*4 + 50, drawingCanvas.height - bottomMargin - 3*trackGap + 5)

            ctx.moveTo(drawingCanvas.width - rightMargin*4 + 20, drawingCanvas.height - bottomMargin - 4*trackGap + 10)
            ctx.lineTo(drawingCanvas.width - rightMargin*4 + 50, drawingCanvas.height - bottomMargin - 4*trackGap + 10)
            ctx.stroke()
        }
    }
}
