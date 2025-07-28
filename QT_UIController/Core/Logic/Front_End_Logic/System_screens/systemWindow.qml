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
import "./../System_screens"

Item {

    id: systemWindow

    readonly property int qmlscreenIndicator:  UIScreenEnum.SYSTEM

    property string qmltextMenuName:               "System"
    property string qmlTextConfiguration:          "Configuration"
    property string qmlTextData:                   "Data"
    property string qmlTextInformation:            "Information"
    property string qmlTextServiceCount:           "Service Count"
    property string qmlTextCalibration:            "Calibration"

    //layout size
    readonly property int elementWidth:            180
    readonly property int elementHeight:           180
    readonly property int elementWidthMargin:      10
    readonly property int elementHeightMargin:     10
    property int rowNumber: 1
    property int columnNumber: 1

    //const
    readonly property int calibrationIndex: 1
    property var qmlTextArray:[qmlTextConfiguration, qmlTextInformation, qmlTextServiceCount, qmlTextCalibration]

    QtObject
    {
        id: textEnum
        readonly property int sysConfigurationIdx  : 0
        readonly property int sysInformationIdx    : 1
        readonly property int sysServiceCountIdx   : 2
        readonly property int sysCalibrationIdx    : 3
    }


    function updateLanguage()
    {
        qmltextMenuName = LanguageConfig.getLanguageMenuName(UIScreenEnum.SYSTEM, qmltextMenuName)
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.SYSTEM, qmlTextArray)
        qmlTextConfiguration = qmlTextArray[textEnum.sysConfigurationIdx]
        qmlTextInformation = qmlTextArray[textEnum.sysInformationIdx]
        qmlTextServiceCount = qmlTextArray[textEnum.sysServiceCountIdx]
        qmlTextCalibration = qmlTextArray[textEnum.sysCalibrationIdx]
        systemViewModel.resetModel()
    }

    function updateItemScreen(itemIndex)
    {
        switch(itemIndex)
        {
        case textEnum.sysConfigurationIdx:
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CONFIG)
            break

        case textEnum.sysInformationIdx:
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_INFO)
            break

        case textEnum.sysServiceCountIdx:
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_SERVICE_COUNT)
            break

        case textEnum.sysCalibrationIdx:
            mainWindow.menuChildOptionSelect(UIScreenEnum.SYSTEM, UIScreenEnum.SYSTEM_CALIBRATE)
            break

        default:
            break
        }
    }

    Connections
    {
        target:mainWindow
        function onLoadRightActionModel()
        {
            systemViewModel.resetModel()
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
        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.SYSTEM)
        systemViewModel.resetModel()
        caculateListModel()
        recalculateRowColumn()
    }

    function checkUserAccess()
    {
        var check =  false
        var logedinUserLevel = UserPrivilegeObj.getLogedInUserLevel()
        var isBarcodeRecipeRecall = UserPrivilegeObj.IsBarcoderecipeRecallAllowed
        var isAuthorityCheck = UserPrivilegeObj.IsModifyAuthoritiyCheckAllowed




        switch (logedinUserLevel)
        {
           case mainWindow.qmltextOperator:           //For operator only General will be visible in case if Allowed but not other screens .
               if(isBarcodeRecipeRecall || isAuthorityCheck)
               {
                   check =  true
               }
               break;
           case mainWindow.qmltextTechnician:         //SystemConfiguration is enabled for techcian then ENable "UserIO" Tab for "Technicain".

               if(UserPrivilegeObj.IsSystemConfigurationAllowed  || isBarcodeRecipeRecall || isAuthorityCheck )
               {
                   check = true
               }
               break;
           case mainWindow.qmltextSupervisor:       //Same as Technician

               if(UserPrivilegeObj.IsSystemConfigurationAllowed  || isBarcodeRecipeRecall || isAuthorityCheck )
               {
                   check = true
               }
               break;
           case mainWindow.qmltextExecutive:        //Will have access to all fields.
                check = true
               break;
           default:

               check = false

        }

        if(mainWindow.isAuthorityCheckEnable) /* User Authority check is disabled then they must be allowed to navigate to all the screens without restrictions . But in case of User Management tab use Dongle check and Authortiy check to access the window.*/
        {
            check = true
        }

        return check
    }

    ListModel
    {
        id: systemViewModel

        function resetModel()
        {
            systemViewModel.clear()
            systemViewModel.append({ "imageURL":  "qrc:/Images/systemConfiguration.svg",
                                       "textName":  qmlTextConfiguration,
                                       "itemIndex": 0,
                                       "userAccessLevel":checkUserAccess() ,
                                   })
            
            systemViewModel.append({ "imageURL":  "qrc:/Images/systemInformation.svg",
                                       "textName":  qmlTextInformation,
                                       "itemIndex": 1,
                                       "userAccessLevel": true,
                                   })

            systemViewModel.append({ "imageURL":  "qrc:/Images/systemInformation.svg",
                                       "textName":  qmlTextServiceCount,
                                       "itemIndex": 2,
                                       "userAccessLevel": true,
                                   })
            /*Visible only for electric actuator*/
            if(SystemConfiguration.CurrentSystemType === SystemTypeDef.ACTUATOR_ELECTRONIC)
            {
              systemViewModel.append({ "imageURL":  "qrc:/Images/systemCalibration.png",
                                     "textName":  qmlTextCalibration,
                                      "itemIndex": 3,
                                       "userAccessLevel": true,
                                   })
            }
        }
    }

    ListModel
    {
        id: systemActualModel
    }

    function caculateListModel()
    {
        systemActualModel.clear()
        for(var index = 0; index < systemViewModel.count; index++)
        {
            systemActualModel.append(systemViewModel.get(index))
        }
    }

    function recalculateRowColumn()
    {
        if(systemActualModel.count > 4)
        {
            columnNumber = 3
            var actualModelCnt = systemActualModel.count

            if(actualModelCnt % 3 === 0)
            {
                rowNumber = actualModelCnt / 3
            }

            else
            {
                rowNumber = actualModelCnt / 3 + 1
            }
        }

        else if(systemActualModel.count === 4)
        {
            columnNumber = 2
            rowNumber = 2
        }

        else
        {
            columnNumber = systemActualModel.count
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
        width: Math.round((elementWidth + elementWidthMargin) * columnNumber * Style.scaleHint)
        height: Math.round((elementHeight + elementHeightMargin) * rowNumber * Style.scaleHint)

        GridView
        {
            id: gridView
            interactive: false
            anchors.fill: parent
            model: systemActualModel
            cellHeight: parent.height / rowNumber + 4
            cellWidth: parent.width / columnNumber - 8

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
                        if(model.userAccessLevel)
                        {
                            updateItemScreen(model.itemIndex)
                        }

                        else
                        {
                            mainWindow.showBransonPopupForAccessDenied()
                        }
                    }
                }
            }
        }
    }
}
