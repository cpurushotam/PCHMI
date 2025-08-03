import QtQuick 2.15

Item {
    id: arcProgressBar

    property string bgColor: "white"

    property int radius: 80
    property int lineWidth: 15
    property real startAngleInDeg:90.0
    property int progressBarCount: 3
    property var colorsList: ["red","green","blue"]
    property var progressValList: [65,20,15]

    // Rectangle {
    //     id: bgRect
    //     anchors.fill: parent
    //     color: arcProgressBar.bgColor
    // }

    Canvas {
        id: canvas
        anchors.centerIn: parent
        width: parent.width
        height: parent.height

        onPaint: {
            var centerX = width / 2
            var centerY = height / 2
            var radius = arcProgressBar.radius
            var lineWidth = arcProgressBar.lineWidth

            var totalAngle = 2 * Math.PI
            var startAngle = (2 * Math.PI * (arcProgressBar.startAngleInDeg/360))

            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            ctx.lineWidth = lineWidth
            //ctx.lineCap = "round"
            for(var i = 0; i < arcProgressBar.progressBarCount; i++)
            {
                ctx.beginPath()
                ctx.strokeStyle = arcProgressBar.colorsList[i];
                var endAngle = (startAngle + (totalAngle * (arcProgressBar.progressValList[i]/100)));
                console.log("i = ",i,"startAngle = ",startAngle)
                console.log("i = ",i,"endAngle = ",endAngle)
                ctx.arc(centerX, centerY, radius, startAngle, endAngle)
                ctx.stroke()
                startAngle = endAngle;
            }
        }

        Component.onCompleted: requestPaint()
    }
}
