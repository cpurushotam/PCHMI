/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

This file is related to system window in leftaction menu.
 **********************************************************************************************************/


import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "./../Common_Logic"

Item {

    id: systemWindow

    readonly property int qmlscreenIndicator:  UIScreenEnum.DIAGNOSTICS

    property string qmltextMenuName       : "Diagnostics"
    property string qmlTextScan           : "Scan"
    property string qmlTextTest           : "Test"
    property string qmlTextSeek           : "Seek"
    property string qmlTextEvent          : "Event Log"
    property string qmlTextAlarm          : "Alarm Log"
    property string qmlTextUserIO         : "User IO"

    //layout size
    readonly property int elementWidth:            200
    readonly property int elementHeight:           200
    readonly property int elementWidthMargin:      10
    readonly property int elementHeightMargin:     10
    property int rowNumber: 1
    property int columnNumber: 1

    property var qmlTextArray:[qmlTextScan, qmlTextTest, qmlTextSeek,qmlTextEvent, qmlTextAlarm, qmlTextUserIO]

    QtObject
    {
        id: textEnum
        readonly property int scanIdx  : 0
        readonly property int testIdx  : 1
        readonly property int seekIdx  : 2
        readonly property int eventIdx : 3
        readonly property int alarmIdx : 4
        readonly property int userIoIdx: 5
    }


    function updateLanguage()
    {
        qmltextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.DIAGNOSTICS, qmltextMenuName)
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.DIAGNOSTICS, qmlTextArray)
        qmlTextScan = qmlTextArray[textEnum.scanIdx]
        qmlTextTest = qmlTextArray[textEnum.testIdx]
        qmlTextSeek = qmlTextArray[textEnum.seekIdx]
        qmlTextEvent = qmlTextArray[textEnum.eventIdx]
        qmlTextAlarm = qmlTextArray[textEnum.alarmIdx]
        qmlTextUserIO = qmlTextArray[textEnum.userIoIdx]
        diagnosticsViewModel.resetModel()
    }

    function updateItemScreen(itemIndex)
    {
        switch(itemIndex)
        {
        case textEnum.scanIdx :

            mainWindow.menuChildOptionSelect(UIScreenEnum.DIAGNOSTICS, UIScreenEnum.DIAGNOSTICS_SCAN)
            break

        case textEnum.testIdx :

            mainWindow.menuChildOptionSelect(UIScreenEnum.DIAGNOSTICS, UIScreenEnum.DIAGNOSTICS_TEST)
            break

        case textEnum.seekIdx :

            mainWindow.menuChildOptionSelect(UIScreenEnum.DIAGNOSTICS, UIScreenEnum.DIAGNOSTICS_SEEK)
            break
            
        case textEnum.eventIdx :
        
            mainWindow.menuChildOptionSelect(UIScreenEnum.DIAGNOSTICS, UIScreenEnum.DIAGNOSTICS_EVENT)
            break

        case textEnum.alarmIdx :
            mainWindow.menuChildOptionSelect(UIScreenEnum.DIAGNOSTICS, UIScreenEnum.DIAGNOSTICS_ALARM)
            break

        case textEnum.userIoIdx :
            mainWindow.menuChildOptionSelect(UIScreenEnum.DIAGNOSTICS, UIScreenEnum.DIAGNOSTIC_USERIO)
            break

        default:
            break
        }
    }

    Connections
    {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
            caculateListModel()
        }
    }


    Component.onCompleted:
    {
        updateLanguage()
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.DIAGNOSTICS
        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.DIAGNOSTICS)
        diagnosticsViewModel.resetModel()
        caculateListModel()
        recalculateRowColumn()
    }

    ListModel
    {
        id: diagnosticsViewModel
        function resetModel()
        {
            diagnosticsViewModel.clear()
            diagnosticsViewModel.append({ "imageURL":  "qrc:/Images/DiagnosticsScan.png",
                                            "textName":  qmlTextScan,
                                            "itemIndex": 0,
                                        })
            diagnosticsViewModel.append({ "imageURL":  "qrc:/Images/DiagnosticsTest.png",
                                            "textName":  qmlTextTest,
                                            "itemIndex": 1,

                                        })
            diagnosticsViewModel.append({ "imageURL":  "qrc:/Images/DiagnosticsSeek.png",
                                            "textName":  qmlTextSeek,
                                            "itemIndex": 2,

                                        })

            if(SystemConfiguration.EventLogSupportSystemType === SystemTypeDef.EVENT_LOG_SUPPORTED)
            {
                diagnosticsViewModel.append({ "imageURL":  "qrc:/Images/Time.png",
                                                "textName":  qmlTextEvent,
                                                "itemIndex": 3,

                                            })
            }

            diagnosticsViewModel.append({ "imageURL":  "qrc:/Images/Alarm.png",
                                            "textName":  qmlTextAlarm,
                                            "itemIndex": 4,

                                        })
            if(SystemConfiguration.UserIOSupportSystemType == SystemTypeDef.USER_IO_SUPPORTED  )
            {
                if(UserPrivilegeObj.getLogedInUserLevel() === mainWindow.qmltextTechnician || UserPrivilegeObj.getLogedInUserLevel=== mainWindow.qmltextSupervisor ||  UserPrivilegeObj.getLogedInUserLevel() ===mainWindow.qmltextExecutive || mainWindow.isAuthorityCheckEnable)
                {
                    diagnosticsViewModel.append({ "imageURL":  "qrc:/Images/User_IO.svg",
                                                    "textName":  qmlTextUserIO,
                                                    "itemIndex": 5,

                                                })
                }
            }
        }
    }

    ListModel
    {
        id: diagnosticsActualModel
    }

    function caculateListModel()
    {
        diagnosticsActualModel.clear()
        for(var index = 0; index < diagnosticsViewModel.count; index++)
        {

                diagnosticsActualModel.append(diagnosticsViewModel.get(index))

        }
    }

    function recalculateRowColumn()
    {
        if(diagnosticsActualModel.count > 4)
        {
            columnNumber = 3
            var actualModelCnt = diagnosticsActualModel.count
            if(actualModelCnt % 3 ===0)
            {
                rowNumber = actualModelCnt / 3
            }
            else
            {
                rowNumber = actualModelCnt / 3 + 1
            }
        }
        else if(diagnosticsActualModel.count === 4)
        {
            columnNumber = 2
            rowNumber = 2
        }
        else
        {
            columnNumber = diagnosticsActualModel.count
            rowNumber = 1
        }
    }

    Rectangle
    {
        id: systemRec
        color: Style.backgroundColor
        anchors.centerIn: parent
        anchors.top: parent.top
        anchors.topMargin: 7
        width: Math.round((elementWidth + elementWidthMargin) * columnNumber * Style.scaleHint * 0.9)
        height: Math.round((elementHeight + elementHeightMargin) * rowNumber * Style.scaleHint * 0.95)
        GridView
        {
            id: gridView
            interactive: false
            anchors.fill: parent
            model: diagnosticsActualModel
            cellHeight: parent.height / rowNumber
            cellWidth: parent.width / columnNumber

            delegate: Image
            {
                width: gridView.cellWidth
                height: gridView.cellHeight
                fillMode: Image.PreserveAspectFit
                source: "qrc:/Images/SystemCardBox.svg"
                visible: true
                Image
                {
                    id: cellIcon
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: Math.round(68 * Style.scaleHint)
                    width: Math.round(40* Style.scaleHint)
                    height: Math.round(40* Style.scaleHint)
                    fillMode: Image.PreserveAspectFit
                    source: model.imageURL
                }

                Text
                {
                    id: cellText
                    anchors.top: cellIcon.bottom
                    anchors.topMargin: Math.round(12 * Style.scaleHint)
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                    text: model.textName
                    color: Style.blackFontColor
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        updateItemScreen(model.itemIndex)
                        TestData.invokeUpdateFlag()
                    }
                }
            }
        }
    }
}
