import QtQuick 2.15

Item {
    id:dashBoardWindowItem


    Rectangle {
        anchors.fill: parent
        color: "white"
    }

    ListView {
        id: welderListView
        width: (parent.width * 0.95)
        height: parent.height * 0.95
        anchors.centerIn: parent
        orientation: ListView.Horizontal
        model: dashBoardModel
        spacing: (parent.width*0.013)
        boundsBehavior: Flickable.StopAtBounds
        delegate: DashBoardWelderDelegate {
            id: welderDelegate
            width: (welderListView.width*0.239)
            height: (welderListView.height)
            // color: "white"
            // border.color: "#BFBFBF"
            // border.width: 2

            onGotoWelderSelected: {
                console.log("Go To Welder selected, WelderID: ",(index+1))
            }
            onWelderConnectRequested: {
                console.log("Connect Welder selected, WelderID: ",(index+1))
            }
        }
    }
}
