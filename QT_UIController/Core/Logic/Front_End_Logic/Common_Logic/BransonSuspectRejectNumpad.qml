/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------

    BransonSuspectRejectNumpad.qml file handles suspect & reject data entry
    interface logic.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 06/02/2024 - Initial version.
***************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.2
import Style 1.0
import Com.Branson.SystemTypeDef 1.0

Item
{
    id: suspectRejectNumpad
    property int minWidth: Math.round(400 * Style.scaleHint)
    property int maxHeight: Math.round(430 * Style.scaleHint)
    property int headermaxHeight: Math.round(30 * Style.scaleHint)
    property string headerColor: Style.headerBackgroundColor
    property string headerText
    property string qmlTextTime:             "TIME"
    property string qmlTextEnergy:           "ENERGY"
    property string qmlTextPeakPower:        "PEAK POWER"
    property string qmlTextFrequency:        "FREQUENCY"
    property string qmlTextAbsoluteDistance: "ABSOLUTE DISTANCE"
    property string qmlTextCollapseDistance: "COLLAPSE DISTANCE"
    property string qmlTextTriggerDistance:  "TRIGGER DISTANCE"
    property string qmlTextEndWeldFORCE:     "END WELD FORCE"
    property string qmlTextVelocity:         "VELOCITY"

    property string headerTextSuffix : " SUSPECT & REJECT LIMITS"
    property string qmltextEnterValidLimitsMsg : "Please enter valid limits to continue"

    
    property string headerTextColor: "#FFFFFF"
    property int fontSize: Math.round(Style.style2 * Style.scaleHint)
    property bool suspectChecked
    property bool rejectChecked
    property var suspectLow
    property var rejectLow
    property var suspectHigh
    property var rejectHigh

    property var suspectLowMinRange
    property var rejectLowMinRange
    property var suspectLowMaxRange
    property var rejectLowMaxRange

    property int decimals
    property string suffix:  "%"

    Rectangle
    {
        id: background
        anchors.fill: parent
        color: Style.dialogBackgroundColor
        opacity: 0.75
        MouseArea
        {
            anchors.fill: parent
        }
    }

    Rectangle
    {
        id:root
        implicitWidth: minWidth
        implicitHeight:maxHeight
        anchors.centerIn: parent
        color: "#FFFFFF"
        Rectangle
        {
            id:header
            width: parent.width
            implicitHeight: headermaxHeight
            color: headerColor
            Text
            {
                id: headername
                anchors.left: header.left
                anchors.top: header.top
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.topMargin: Math.round(5 * Style.scaleHint)
                text: headerText + headerTextSuffix
                color: headerTextColor
                font
                {
                    family: Style.regular.name
                    pixelSize: fontSize
                }
            }

            Rectangle
            {
                id:rectimage
                implicitWidth: Math.round(24 * Style.scaleHint)
                implicitHeight: Math.round(24 * Style.scaleHint)
                anchors.right: header.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.top: header.top
                anchors.topMargin:Math.round(5 * Style.scaleHint)
                color: "transparent"

                Image
                {
                    id: headercls
                    anchors.fill: parent
                    source: "qrc:/Images/crossMark.svg"
                    sourceSize.width: headercls.width
                    sourceSize.height: headercls.height
                    smooth: true
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        suspectRejectNumpad.visible = false
                    }
                }
            }
        }

        BransonDoubleSwitchBoard
        {
            id: bransonDoubleSwitchBoard
            anchors.top: header.bottom
            anchors.left: header.left
            anchors.topMargin: Math.round(30 * Style.scaleHint)
            anchors.leftMargin: Math.round(100 * Style.scaleHint)
            isSuspectChecked: suspectChecked
            isRejectChecked: rejectChecked
            suspectLowInputValue: suspectLow
            rejectLowInputValue: rejectLow
            suspectHighInputValue: suspectHigh
            rejectHighInputValue: rejectHigh
            decimals: decimals
            suffix: suffix
            selectedSwitch: headerText
        }


        BransonPrimaryButton
        {
            id:cancel
            implicitWidth: Math.round(124 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.bottom: root.bottom
            anchors.bottomMargin: Math.round(15 * Style.scaleHint)
            anchors.left: root.left
            anchors.leftMargin: Math.round(60 * Style.scaleHint)
            text: "CANCEL"
            font.family: Style.regular.name
            buttonColor: "#E8E8E8"
            textColor: "#000000"
            onClicked:
            {
                suspectRejectNumpad.visible = false
            }
        }

        BransonPopup{
            id: messagePopup
            visible:false
            anchors.centerIn: parent
            focus:true
            qmltextWarningDialog: headerTextSuffix
            onOKButtonClicked:
            {
                messagePopup.visible = false
            }
            onCancelButtonClicked:
            {
                messagePopup.visible = false
            }
        }

        BransonPrimaryButton
        {
            id:done
            implicitWidth: Math.round(124 * Style.scaleHint)
            implicitHeight: Math.round(30 * Style.scaleHint)
            fontSize: Math.round(Style.style2  * Style.scaleHint)
            anchors.top: cancel.top
            anchors.left: cancel.right
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            text: "DONE"
            font.family: Style.regular.name
            onClicked:
            {
                if (bransonDoubleSwitchBoard.isSuspectChecked && bransonDoubleSwitchBoard.isRejectChecked)//suspectChecked && rejectChecked)
                {
                    if(parseFloat(bransonDoubleSwitchBoard.rejectLowInput) < parseFloat(bransonDoubleSwitchBoard.suspectLowInput) && parseFloat(bransonDoubleSwitchBoard.suspectLowInput) < parseFloat(bransonDoubleSwitchBoard.suspectHighInput) && parseFloat(bransonDoubleSwitchBoard.suspectHighInput) < parseFloat(bransonDoubleSwitchBoard.rejectHighInput))
                    {
                        if(headerText === qmlTextTime)
                        {
                            var isDataValid = true
                            if((parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowTime = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                                isDataValid = false
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowTime = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                                isDataValid = false
                            }

                            if((parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectHighInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighTime = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                                isDataValid = false
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighTime = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }
                            else
                            {
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                                isDataValid = false
                            }

                            if(isDataValid)
                            {
                                RecipeLabData.IsSuspectTime = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsRejectTime = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }

                        else if(headerText === qmlTextEnergy)
                        {
                            var isEnegryDataValid = true

                            if(( parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && ( parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowEnergy = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                                isEnegryDataValid = false
                            }
                            if(( parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && ( parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowEnergy = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                                isEnegryDataValid = false

                            }

                            if(( parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && ( parseFloat(bransonDoubleSwitchBoard.suspectHighInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighEnergy = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                                isEnegryDataValid = false

                            }
                            if((parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighEnergy = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }

                            else
                            {
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                                isEnegryDataValid = false

                            }
                            if(isEnegryDataValid)
                            {
                                RecipeLabData.IsSuspectEnergy = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsRejectEnergy = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }

                        else if(headerText === qmlTextPeakPower)
                        {

                            var isPeakPowerValid = true

                            if((parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowPeakPower = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                isPeakPowerValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowPeakPower = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                isPeakPowerValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }

                            if((parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectHighInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighPeakPower = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                isPeakPowerValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighPeakPower = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }
                            else
                            {
                                isPeakPowerValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if( isPeakPowerValid )
                            {
                                RecipeLabData.IsSuspectPeakPower = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsRejectPeakPower = bransonDoubleSwitchBoard.isRejectChecked
                            }

                        }

                        else if(headerText === qmlTextFrequency)
                        {
                            var isFrequecyData = true
                            if((parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowFrequency = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                isFrequecyData = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if(( parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && ( parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowFrequency = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                isFrequecyData = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectHighInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighFrequency = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                isFrequecyData = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighFrequency = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }
                            else
                            {
                                isFrequecyData = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if( isFrequecyData  )
                            {
                                RecipeLabData.IsSuspectFrequency = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsRejectFrequency = bransonDoubleSwitchBoard.isRejectChecked
                            }

                        }

                        else if(headerText === qmlTextAbsoluteDistance)
                        {

                            var isAbsDistDataValid = true
                            if((parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowAbsDist = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                isAbsDistDataValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if(( parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && ( parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowAbsDist = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                isAbsDistDataValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectHighInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighAbsDist = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                isAbsDistDataValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if(( parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && ( parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighAbsDist = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }
                            else
                            {
                                isAbsDistDataValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if(isAbsDistDataValid )
                            {
                                RecipeLabData.IsAbsDistSuspect = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsAbsDistReject = bransonDoubleSwitchBoard.isRejectChecked
                            }

                        }

                        else if(headerText === qmlTextCollapseDistance)
                        {

                            var isCollapseDisDataValid = true
                            if(( parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && ( parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowCollapseDist = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                isCollapseDisDataValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowCollapseDist = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                isCollapseDisDataValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectHighInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighCollapseDist = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else{
                                isCollapseDisDataValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if(( parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && ( parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighCollapseDist = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }

                            else
                            {
                                isCollapseDisDataValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if(  isCollapseDisDataValid)
                            {
                                RecipeLabData.IsCollapseDistSuspect = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsCollapseDistReject = bransonDoubleSwitchBoard.isRejectChecked
                            }

                        }

                        else if(headerText === qmlTextTriggerDistance)
                        {

                            var isTrigDisDataValid = true
                            if(( parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && ( parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowTriggerDist = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                isTrigDisDataValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowTriggerDist = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                isTrigDisDataValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectHighInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighTriggerDist = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                isTrigDisDataValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighTriggerDist = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }
                            else
                            {
                                isTrigDisDataValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if(   isTrigDisDataValid )
                            {
                                RecipeLabData.IsTriggerDistSuspect = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsTriggerDistReject = bransonDoubleSwitchBoard.isRejectChecked
                            }

                        }
                        else if(headerText === qmlTextEndWeldFORCE)
                        {
                            var isEndForceDataValid = true
                            if((parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowEndWeldForce = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                isEndForceDataValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowEndWeldForce = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                isEndForceDataValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectHighInput) < suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighEndWeldForce = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                isEndForceDataValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if(( parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && ( parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighEndWeldForce = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }
                            else
                            {
                                isEndForceDataValid = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if( isEndForceDataValid )
                            {
                                RecipeLabData.IsEndWeldForceSuspect = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsEndWeldForceReject = bransonDoubleSwitchBoard.isRejectChecked
                            }

                        }
                        else if(headerText === qmlTextVelocity)
                        {
                            var isVelocityDataValid  = true
                            if((parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowVelocity = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                isVelocityDataValid  = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowVelocity = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                isVelocityDataValid  = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectHighInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighVelocity = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                isVelocityDataValid  = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if(( parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && ( parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighVelocity = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }
                            else
                            {
                                isVelocityDataValid  = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if(  isVelocityDataValid)
                            {
                                RecipeLabData.IsVelocitySuspect = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsVelocityReject = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }
                        suspectRejectNumpad.visible = false
                    }
                    else
                    {
                        mainWindow.showMessagePopUp()
                    }
                }
                else if(bransonDoubleSwitchBoard.isSuspectChecked && bransonDoubleSwitchBoard.isRejectChecked == false)
                {

                    if(parseFloat(bransonDoubleSwitchBoard.suspectLowInput)  < parseFloat(bransonDoubleSwitchBoard.suspectHighInput) )
                    {
                        if(headerText === qmlTextTime)
                        {
                            var isSuspectDataValid = true
                            if((parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowTime = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                                isSuspectDataValid = false
                            }

                            if((parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectHighInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighTime = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                                isSuspectDataValid = false
                            }
                            if(isSuspectDataValid)
                            {
                                RecipeLabData.IsSuspectTime = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsRejectTime = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }
                        else if(headerText === qmlTextEnergy)
                        {
                            var isEnegryDataValid2 = true


                            if(( parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && ( parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowEnergy = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                                isEnegryDataValid2 = false
                            }

                            if(( parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && ( parseFloat(bransonDoubleSwitchBoard.suspectHighInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighEnergy = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                                isEnegryDataValid2 = false
                            }

                            if(isEnegryDataValid2)
                            {
                                RecipeLabData.IsSuspectEnergy = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsRejectEnergy = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }

                        else if(headerText === qmlTextPeakPower)
                        {

                            var isPeakPwrDataValid2 = true


                            if((parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowPeakPower = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                isPeakPwrDataValid2 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectHighInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighPeakPower = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                isPeakPwrDataValid2 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if( isPeakPwrDataValid2 )
                            {
                                RecipeLabData.IsSuspectPeakPower = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsRejectPeakPower = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }

                        else if(headerText === qmlTextFrequency)
                        {
                            var isFrequencyDataValid2 = true


                            if((parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowFrequency = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                isFrequencyDataValid2 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }

                            if((parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectHighInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighFrequency = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                isFrequencyDataValid2 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if( isFrequencyDataValid2)
                            {
                                RecipeLabData.IsSuspectFrequency = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsRejectFrequency = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }
                        else if(headerText === qmlTextAbsoluteDistance)
                        {

                            var isAbsDisDataValid2 = true
                            if((parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowAbsDist = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                isAbsDisDataValid2 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }

                            if((parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectHighInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighAbsDist = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                isAbsDisDataValid2 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if(isAbsDisDataValid2)
                            {
                                RecipeLabData.IsAbsDistSuspect = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsAbsDistReject = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }

                        else if(headerText === qmlTextCollapseDistance)
                        {

                            var isCollDisDataValid2 = true
                            if(( parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && ( parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowCollapseDist = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                isCollDisDataValid2 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }

                            if((parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectHighInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighCollapseDist = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                isCollDisDataValid2 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if( isCollDisDataValid2)
                            {
                                RecipeLabData.IsCollapseDistSuspect = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsCollapseDistReject = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }

                        else if(headerText === qmlTextTriggerDistance)
                        {
                            var istrigDisDataValid2 = true
                            if(( parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && ( parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowTriggerDist = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                istrigDisDataValid2 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectHighInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighTriggerDist = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                istrigDisDataValid2 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if( istrigDisDataValid2 ){

                                RecipeLabData.IsTriggerDistSuspect = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsTriggerDistReject = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }

                        else if(headerText === qmlTextEndWeldFORCE)
                        {
                            var isEndWeldFrcDataValid2 = true
                            if((parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowEndWeldForce = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                isEndWeldFrcDataValid2 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }

                            if((parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectHighInput) < suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighEndWeldForce = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                isEndWeldFrcDataValid2 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if(  isEndWeldFrcDataValid2 ){
                                RecipeLabData.IsEndWeldForceSuspect = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsEndWeldForceReject = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }

                        else if(headerText === qmlTextVelocity)
                        {
                            var isVelocityDataValid2 = true
                            if((parseFloat(bransonDoubleSwitchBoard.suspectLowInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectLowInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectLowVelocity = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            }
                            else
                            {
                                isVelocityDataValid2 =false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.suspectHighInput) >= suspectLowMinRange) && (parseFloat(bransonDoubleSwitchBoard.suspectHighInput) <= suspectLowMaxRange))
                            {
                                RecipeLabData.SuspectHighVelocity = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            }
                            else
                            {
                                isVelocityDataValid2 =false

                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if( isVelocityDataValid2 )
                            {
                                RecipeLabData.IsVelocitySuspect = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsVelocityReject = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }
                    }
                    else
                    {
                        mainWindow.showMessagePopUp()
                    }
                    suspectRejectNumpad.visible = false

                }
                else if(bransonDoubleSwitchBoard.isSuspectChecked == false && bransonDoubleSwitchBoard.isRejectChecked)
                {

                    if(parseFloat(bransonDoubleSwitchBoard.rejectLowInput)  < parseFloat(bransonDoubleSwitchBoard.rejectHighInput))
                    {
                        if(headerText === qmlTextTime)
                        {
                            var isDataValid1 = true
                            if((parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowTime = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                                isDataValid1 = false

                            }

                            if((parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighTime = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }
                            else
                            {
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                                isDataValid1 = false

                            }
                            if(isDataValid1)
                            {
                                RecipeLabData.IsSuspectTime = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsRejectTime = bransonDoubleSwitchBoard.isRejectChecked
                            }

                        }
                        else if(headerText === qmlTextEnergy)
                        {

                            var isEnegryDataValid1 = true

                            if(( parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && ( parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowEnergy = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                                isEnegryDataValid1 = false
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighEnergy = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }

                            else
                            {
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                                isEnegryDataValid1 = false

                            }
                            if(isEnegryDataValid1)
                            {
                                RecipeLabData.IsSuspectEnergy = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsRejectEnergy = bransonDoubleSwitchBoard.isRejectChecked
                            }

                        }

                        else if(headerText === qmlTextPeakPower)
                        {

                            var isPeakPwrValid1 =true
                            if((parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowPeakPower = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                isPeakPwrValid1 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighPeakPower = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }
                            else
                            {
                                isPeakPwrValid1 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if(  isPeakPwrValid1 )
                            {
                                RecipeLabData.IsSuspectPeakPower = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsRejectPeakPower = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }

                        else if(headerText === qmlTextFrequency)
                        {
                            var isFrequencyValid1 =true
                            if(( parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && ( parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowFrequency = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                isFrequencyValid1 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }

                            if((parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighFrequency = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }
                            else
                            {
                                isFrequencyValid1 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if( isFrequencyValid1)
                            {
                                RecipeLabData.IsSuspectFrequency = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsRejectFrequency = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }

                        else if(headerText === qmlTextAbsoluteDistance)
                        {
                            var isAbsDistValid1 =true
                            if(( parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && ( parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowAbsDist = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                isAbsDistValid1 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }

                            if(( parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && ( parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighAbsDist = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }
                            else
                            {
                                isAbsDistValid1 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if( isAbsDistValid1)
                            {
                                RecipeLabData.IsAbsDistSuspect = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsAbsDistReject = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }

                        else if(headerText === qmlTextCollapseDistance)
                        {
                            var isCollDistValid1 =true
                            if((parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowCollapseDist = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                isCollDistValid1 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }

                            if(( parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && ( parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighCollapseDist = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }

                            else
                            {
                                isCollDistValid1 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if( isCollDistValid1)
                            {
                                RecipeLabData.IsCollapseDistSuspect = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsCollapseDistReject = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }

                        else if(headerText === qmlTextTriggerDistance)
                        {
                            var isTrigDistValid1 =true
                            if((parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowTriggerDist = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                isTrigDistValid1 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if((parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighTriggerDist = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }
                            else
                            {
                                isTrigDistValid1 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if( isTrigDistValid1 )
                            {
                                RecipeLabData.IsTriggerDistSuspect = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsTriggerDistReject = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }

                        else if(headerText === qmlTextEndWeldFORCE)
                        {
                            var isEndWeldForceValid1 =true
                            if((parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowEndWeldForce = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                isEndWeldForceValid1 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if(( parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && ( parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighEndWeldForce = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }
                            else
                            {
                                isEndWeldForceValid1 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }

                            if( isEndWeldForceValid1 )
                            {
                                RecipeLabData.IsEndWeldForceSuspect = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsEndWeldForceReject = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }

                        else if(headerText === qmlTextVelocity)
                        {
                            var isVelocityValid1 =true
                            if((parseFloat(bransonDoubleSwitchBoard.rejectLowInput) >= rejectLowMinRange ) && (parseFloat(bransonDoubleSwitchBoard.rejectLowInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectLowVelocity = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            }
                            else
                            {
                                isVelocityValid1 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }

                            if(( parseFloat(bransonDoubleSwitchBoard.rejectHighInput) >= rejectLowMinRange ) && ( parseFloat(bransonDoubleSwitchBoard.rejectHighInput) <= rejectLowMaxRange))
                            {
                                RecipeLabData.RejectHighVelocity = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            }
                            else
                            {
                                isVelocityValid1 = false
                                messagePopup.visible = true
                                messagePopup.qmltextWarningDialog = qmltextEnterValidLimitsMsg
                            }
                            if(  isVelocityValid1 )
                            {
                                RecipeLabData.IsVelocitySuspect = bransonDoubleSwitchBoard.isSuspectChecked
                                RecipeLabData.IsVelocityReject = bransonDoubleSwitchBoard.isRejectChecked
                            }
                        }

                        suspectRejectNumpad.visible = false

                    }
                    else
                    {
                        mainWindow.showMessagePopUp()
                    }
                }
                    else if(bransonDoubleSwitchBoard.isSuspectChecked == false && bransonDoubleSwitchBoard.isRejectChecked == false)
                    {
                        if(headerText === qmlTextTime)
                        {
                            RecipeLabData.RejectLowTime = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            RecipeLabData.RejectHighTime = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            RecipeLabData.SuspectLowTime = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            RecipeLabData.SuspectHighTime = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            RecipeLabData.IsSuspectTime = bransonDoubleSwitchBoard.isSuspectChecked
                            RecipeLabData.IsRejectTime = bransonDoubleSwitchBoard.isRejectChecked
                        }

                        else if(headerText === qmlTextEnergy)
                        {
                            RecipeLabData.SuspectLowEnergy = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            RecipeLabData.SuspectHighEnergy = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            RecipeLabData.RejectLowEnergy = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            RecipeLabData.RejectHighEnergy = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            RecipeLabData.IsSuspectEnergy = bransonDoubleSwitchBoard.isSuspectChecked
                            RecipeLabData.IsRejectEnergy = bransonDoubleSwitchBoard.isRejectChecked
                        }
                        else if(headerText === qmlTextPeakPower)
                        {
                            RecipeLabData.SuspectLowPeakPower = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            RecipeLabData.SuspectHighPeakPower = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            RecipeLabData.RejectLowPeakPower = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            RecipeLabData.RejectHighPeakPower = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            RecipeLabData.IsSuspectPeakPower = bransonDoubleSwitchBoard.isSuspectChecked
                            RecipeLabData.IsRejectPeakPower = bransonDoubleSwitchBoard.isRejectChecked
                        }
                        else if(headerText === qmlTextFrequency)
                        {
                            RecipeLabData.SuspectLowFrequency = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            RecipeLabData.SuspectHighFrequency = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            RecipeLabData.RejectLowFrequency = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            RecipeLabData.RejectHighFrequency = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            RecipeLabData.IsSuspectFrequency = bransonDoubleSwitchBoard.isSuspectChecked
                            RecipeLabData.IsRejectFrequency = bransonDoubleSwitchBoard.isRejectChecked
                        }
                        else if(headerText === qmlTextAbsoluteDistance)
                        {
                            RecipeLabData.SuspectLowAbsDist = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            RecipeLabData.SuspectHighAbsDist = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            RecipeLabData.RejectLowAbsDist = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            RecipeLabData.RejectHighAbsDist = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            RecipeLabData.IsAbsDistSuspect = bransonDoubleSwitchBoard.isSuspectChecked
                            RecipeLabData.IsAbsDistReject = bransonDoubleSwitchBoard.isRejectChecked

                        }
                        else if(headerText === qmlTextCollapseDistance)
                        {
                            RecipeLabData.SuspectLowCollapseDist = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            RecipeLabData.SuspectHighCollapseDist = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            RecipeLabData.RejectLowTriggerDist = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            RecipeLabData.RejectHighTriggerDist = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            RecipeLabData.IsTriggerDistSuspect = bransonDoubleSwitchBoard.isSuspectChecked
                            RecipeLabData.IsTriggerDistReject = bransonDoubleSwitchBoard.isRejectChecked
                        }

                        else if(headerText === qmlTextTriggerDistance)
                        {
                            RecipeLabData.SuspectLowTriggerDist = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            RecipeLabData.SuspectHighTriggerDist = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            RecipeLabData.RejectLowTriggerDist = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            RecipeLabData.RejectHighTriggerDist = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            RecipeLabData.IsTriggerDistSuspect = bransonDoubleSwitchBoard.isSuspectChecked
                            RecipeLabData.IsTriggerDistReject = bransonDoubleSwitchBoard.isRejectChecked
                        }
                        else if(headerText === qmlTextEndWeldFORCE)
                        {
                            RecipeLabData.SuspectLowEndWeldForce = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            RecipeLabData.SuspectHighEndWeldForce = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            RecipeLabData.RejectLowEndWeldForce = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            RecipeLabData.RejectHighEndWeldForce = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            RecipeLabData.IsEndWeldForceSuspect = bransonDoubleSwitchBoard.isSuspectChecked
                            RecipeLabData.IsEndWeldForceReject = bransonDoubleSwitchBoard.isRejectChecked
                        }
                        else if(headerText === qmlTextVelocity)
                        {
                            RecipeLabData.SuspectLowVelocity = parseFloat(bransonDoubleSwitchBoard.suspectLowInput)
                            RecipeLabData.SuspectHighVelocity = parseFloat(bransonDoubleSwitchBoard.suspectHighInput)
                            RecipeLabData.RejectLowVelocity = parseFloat(bransonDoubleSwitchBoard.rejectLowInput)
                            RecipeLabData.RejectHighVelocity = parseFloat(bransonDoubleSwitchBoard.rejectHighInput)
                            RecipeLabData.IsVelocitySuspect = bransonDoubleSwitchBoard.isSuspectChecked
                            RecipeLabData.IsVelocityReject = bransonDoubleSwitchBoard.isRejectChecked
                        }
                        suspectRejectNumpad.visible = false
                    }
                }
            }
        }
    }
