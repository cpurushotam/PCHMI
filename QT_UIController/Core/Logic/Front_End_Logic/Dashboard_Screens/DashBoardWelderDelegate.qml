import QtQuick 2.15
import QtQuick.Controls

Item {

    signal gotoWelderSelected;
    signal welderConnectRequested;

    property var progressValListWithDelimeter: progressValList

    onProgressValListWithDelimeterChanged: {
        var stringArray = progressValListWithDelimeter.split(",")
        arcProgressBar.progressValList = [];
        for (var i = 0; i < stringArray.length; i++) {
            arcProgressBar.progressValList.push(parseInt(stringArray[i]))
        }
    }

    Rectangle {
        id: dashboardDelegateBg
        anchors.fill: parent
        color: "white"
        border.color: "#BFBFBF"
        border.width: 2
    }

    Rectangle {
        id: header
        width: parent.width
        height: (parent.height*0.065)
        color: "#000000"
        border.color: "#BFBFBF"
        border.width: 1
        Text {
            id: headerTxt
            height: parent.height
            text: qsTr("WELDER ") + (index+1)
            color: "white"
            property real curScreenWidth: window.width
            property real orgScreenWidth: 1024
            font.pixelSize: (14 * (curScreenWidth/orgScreenWidth));
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.centerIn: parent
        }
    }

    Item {
        id: welderValCircle
        width: (parent.height*0.2)
        height: width
        // radius: (width*0.5)
        // color: "white"
        // border.color: "#757577"
        // border.width: 10
        anchors.top: header.bottom
        anchors.topMargin: (header.height*0.5)
        anchors.horizontalCenter: parent.horizontalCenter

        ArcProgressBar {
            id: arcProgressBar
            anchors.fill: parent
            radius: (welderValCircle.width*0.435)
            lineWidth: (width*0.135)
            //startAngleInDeg:90
            progressBarCount: 3
            colorsList: ["#00AA7E","#D31313","#757577"]
            progressValList: [65,15,20]
        }

        Text {
            id: welderValTxt
            height: parent.height
            text: welderVal
            color: "black"
            font.pixelSize: 30
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: batchCountOuterBox
        width: (parent.width*0.9)
        height: (totalCycleTimerTitleHeader.height)
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: yieldPercOuterBox.top
        anchors.bottomMargin: (height*0.25)
        Text {
            id: batchCountTxt
            text: qsTr("Batch Count")
            color: "black"
            font.pixelSize: 14
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.left: batchCountOuterBox.left
            anchors.leftMargin: (batchCountOuterBox.width*0.07)
        }
        Rectangle {
            id: batchCountValeBox
            width: (parent.width*0.3)
            height: (parent.height)
            color: "#E0ECFA"
            anchors.right: parent.right
            Text {
                id: batchCountValTxt
                text: batchCount
                color: "black"
                font.pixelSize: 14
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.centerIn: parent
            }
        }
    }

    Rectangle {
        id: yieldPercOuterBox
        width: (parent.width*0.9)
        height: (totalCycleTimerTitleHeader.height)
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: totalCycleTimerTitleHeader.top
        anchors.bottomMargin: (height*0.5)
        Text {
            id: yeildPecTxt
            text: qsTr("Yield Percentage")
            color: "black"
            font.pixelSize: 14
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.left: yieldPercOuterBox.left
            anchors.leftMargin: (yieldPercOuterBox.width*0.07)
        }
        Rectangle {
            id: yieldPerValeBox
            width: (parent.width*0.3)
            height: (parent.height)
            color: "#E0ECFA"
            anchors.right: parent.right
            Text {
                id: yeildPecValTxt
                text: ((yeildPercentage < 10 ? "0" : "") + yeildPercentage.toFixed(1))+"%"
                color: "black"
                font.pixelSize: 14
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.centerIn: parent
            }
        }
    }

    Rectangle {
        id: totalCycleTimerTitleHeader
        width: parent.width
        height: (header.height*0.75)
        color: "#004B8D"
        border.color: "#BFBFBF"
        border.width: 1
        anchors.top: header.bottom
        anchors.topMargin: (parent.height*0.395)
        Text {
            id: totalCycleTimerTitleHeaderTxt
            text: qsTr("Total Cycle Times (s)")
            color: "white"
            font.pixelSize: (12 * (curScreenWidth/orgScreenWidth));
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.centerIn: parent
        }
        Text {
            id: totalCycleTimeValTxt
            text: (totalCycleCount < 10 ? "0" : "") + totalCycleCount.toFixed(3)
            color: "black"
            font.pixelSize: 35
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.top: parent.top
            anchors.topMargin: (height*0.45)
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Rectangle {
        id: peakPowerTitleHeader
        width: parent.width
        height: (header.height*0.75)
        color: "#004B8D"
        border.color: "#BFBFBF"
        border.width: 1
        anchors.top: totalCycleTimerTitleHeader.bottom
        anchors.topMargin: (height*1.9)
        Text {
            id: peakPowerTitleHeaderTxt
            text: qsTr("Peak Power")
            color: "white"
            font.pixelSize: 12
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: peakPowerIndicatorOuterBox
        width: (parent.width*0.9)
        height: (peakPowerTitleHeader.height)
        color: "white"
        border.color: "#BFBFBF"
        border.width: 2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: peakPowerTitleHeader.bottom
        anchors.topMargin: (height*0.4)
        Rectangle {
            id: peakPowerIndicator
            width: (parent.width * (peackPower/100))
            height: (parent.height)
            color: "#00AA7E"

            Text {
                id: peakPecTxt
                text: (peackPower + "%")
                color: peackPower < 15 ? "black" : "white"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                //anchors.centerIn: parent
                anchors.left: (peackPower < 15 ? parent.right : parent.left)
                anchors.leftMargin: (peakPowerIndicator.width/2 - (peakPecTxt.width/2)) + (peackPower < 5 ? peakPecTxt.width*0.3 : 0)
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Rectangle {
        id: activeRecipeTitleHeader
        width: parent.width
        height: (header.height*0.75)
        color: "#004B8D"
        border.color: "#BFBFBF"
        border.width: 1
        anchors.top: peakPowerTitleHeader.bottom
        anchors.topMargin: (height*1.8)
        Text {
            id: activeRecipeTitleHeaderTxt
            text: qsTr("Active Recipe")
            color: "white"
            font.pixelSize: 12
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.centerIn: parent
        }
    }

    Text {
        id: speakerBoxValTxt
        text: (speakerBoxVal + qsTr(" : Speakerbox"))
        color: "black"
        font.pixelSize: 13
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.top: activeRecipeTitleHeader.bottom
        anchors.topMargin: (activeRecipeTitleHeader.height*0.25)
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        id: weldTimeVal
        text: ("Weld Time : ") +welderTime.toFixed(3) + " s"
        color: "black"
        font.pixelSize: 13
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.top: speakerBoxValTxt.bottom
        anchors.topMargin: (activeRecipeTitleHeader.height*0.2)
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        id: gotoWelderAction
        width: (activeRecipeTitleHeader.width * 0.66)
        height: (activeRecipeTitleHeader.height*1.27)
        color: "#17345C"
        border.color: "#BFBFBF"
        border.width: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: (activeRecipeTitleHeader.height*0.47)
        anchors.left: parent.left
        anchors.leftMargin: (activeRecipeTitleHeader.height*0.47)
        Text {
            id: gotoWelderActionTxt
            text: qsTr("GO TO WELDER")
            color: "white"
            font.pixelSize: 14
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                gotoWelderSelected();
            }
        }
    }

    ToolTip {
        text: "Tooltip text"
        background: Rectangle {
            color: "white"
            radius: 4
        }
    }

    Rectangle {
        id: welderConnectAction
        property bool hovered: false
        width: (gotoWelderAction.width * 0.27)
        height: gotoWelderAction.height
        color: connectionStatus ? "green" : "#757577"
        border.color: "#BFBFBF"
        border.width: 1
        anchors.bottom: gotoWelderAction.bottom
        anchors.left: gotoWelderAction.right
        anchors.leftMargin: (activeRecipeTitleHeader.height*0.47)
        enabled: connectionStatus
        // ToolTip.visible: hovered
        // ToolTip.text: connectionStatus ? "Connect" : "Disconnect"
        // ToolTip.background: Rectangle {
        //     color: "white" // Set your desired background color here
        //     radius: 4
        // }
        ToolTip {
            text: connectionStatus ? "Connect" : "Disconnect"
            visible: welderConnectAction.hovered
            background: Rectangle {
                color: "white"
                radius: 4
            }
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: parent.hovered = true
            onExited: parent.hovered = false
            onClicked: {
                welderConnectRequested();
            }
        }
    }
}
