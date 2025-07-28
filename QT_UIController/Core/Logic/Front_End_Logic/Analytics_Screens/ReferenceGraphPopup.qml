/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    This file displays the reference graph related signature.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 20/11/2024 - Initial version.
***************************************************************************/
import QtQuick 2.12
import QtQuick.Controls 2.0
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import "./../Common_Logic"
import "./../Analytics_Screens"

Rectangle
{
    id: popup
    z: 1
    property string qmltextLabel                 : "Alert"
    property string qmltextCancel                : "Cancel"
    property string qmltextYesContinueorReplace
    property string qmltextOk                    : "Ok"
    property string qmltextReplace               : "REPLACE"
    property string qmltextContinue              : "YES CONTINUE"

    property string qmltextSuccessText

    property string qmltextAlreadyExists         : "Already marked as a reference graph signature."
    property string qmltextAlert                 : "Alert"

    property string qmltextWarningDialog
    property string qmltextSubDialog
    property bool isMultiButtonPopup             : false
    property bool showRadioButtons               : false

    property bool showCancelButton               : false
    property bool showReplaceorYesContinueButton : false
    property bool showOkButton                   : false
    property bool showSuccessMsgText             : false
    property bool showGreyRect                   : false

    property int newReferenceWeldResultIndex
    property int oldReferenceWeldResultIndex
    property string oldReferenceGraphName
    property string newRferenceGraphName

    property var qmlTextArray: [qmltextLabel,  qmltextCancel, qmltextReplace, qmltextContinue, qmltextAlreadyExists, qmltextAlert]

    ListModel
    {
        id:radioButtonModel
    }

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.POPUP, qmlTextArray)
        qmltextLabel = qmlTextArray[textEnum.textWarningIdx]
        qmltextCancel = qmlTextArray[textEnum.textCancelIdx]
        qmltextReplace = qmlTextArray[textEnum.textReplaceIdx]
        qmltextContinue = qmlTextArray[textEnum.textContinueIdx]
        qmltextAlreadyExists = qmlTextArray[textEnum.textAlreadyExistsIdx]
        qmltextAlert = qmlTextArray[textEnum.textAlertIdx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textWarningIdx:       0
        readonly property int textCancelIdx:        1
        readonly property int textReplaceIdx:       2
        readonly property int textContinueIdx:      3
        readonly property int textAlreadyExistsIdx: 4
        readonly property int textAlertIdx:         5
    }

    function duplicateRefGraph(index)
    {
        var isDuplicateAvailable = false
        var size = ReferenceWeldGraphData.availableReferenceGraphSize()
        for (var i=0; i<size; i++)
        {
            if(index === ReferenceWeldGraphData.refweldResultIndex(i))
            {
                isDuplicateAvailable = true
                mainWindow.showBransonPopup(qmltextAlreadyExists, qmltextAlert)
                break
            }
        }
        return isDuplicateAvailable
    }

    Connections{
        target: ReferenceWeldGraphData
        function onReferenceGraphDataChanged()
        {
            radioButtonModel.clear()
            var size = ReferenceWeldGraphData.availableReferenceGraphSize()
            for (var i=0; i<size; i++)
            {
                var GraphName = ReferenceWeldGraphData.refGraphName(i)
                var Index = ReferenceWeldGraphData.refweldResultIndex(i)
                radioButtonModel.append({"GraphName": GraphName, "Index":Index });
            }
        }
    }
    signal oKButtonClicked()
    signal cancelButtonClicked()

    visible: false
    focus: true
    Rectangle
    {
        id: popupBackground
        anchors.fill: parent
        implicitWidth: parent.width
        implicitHeight: parent.height
        opacity: 1
        color:"#ffffff"
        border.width: 0
        clip:true
        Rectangle
        {
            id: numpadHeader
            width: parent.width
            implicitHeight: parent.height * 0.20
            color: Style.headerBackgroundColor
            Text
            {
                id: headername
                anchors.left: parent.left
                anchors.leftMargin: Math.round(5 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                text: qmltextLabel
                color: Style.whiteFontColor
                font
                {
                    family: Style.regular.name
                    pixelSize: Math.round(Style.style1 * Style.scaleHint)
                }
            }
            Image
            {
                id: crossImage
                source: "qrc:/Images/crossMark.svg"
                width: Math.round(16 * Style.scaleHint)
                height: Math.round(16 * Style.scaleHint)
                anchors.right: parent.right
                anchors.rightMargin: Math.round(5 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                sourceSize.width: alertImage.width
                sourceSize.height: alertImage.height
                smooth: true
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        cancelButtonClicked()
                    }
                }
            }
        }

        Image
        {
            id: alertImage
            source: "qrc:/Images/Exclaim-Circle-Red30.svg"
            width: Math.round(13 * Style.scaleHint)
            height: Math.round(13 * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin:  parent.width*0.45
            anchors.top: parent.top
            anchors.topMargin: parent.height * 0.25
            sourceSize.width: alertImage.width
            sourceSize.height: alertImage.height
            smooth: true
        }

        Text
        {
            id: dialogText
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.08
            anchors.top: alertImage.bottom
            anchors.topMargin:parent.height * 0.10
            anchors.right: parent.right
            anchors.rightMargin: parent.width * 0.08
            text: qmltextWarningDialog
            color: Style.textFontColor
            wrapMode: Text.Wrap
            width:parent.width
            font
            {
                family: Style.regular.name
                pixelSize: Math.round(Style.style1 * Style.scaleHint)*0.90
                weight : Font.Medium
            }
        }

        Rectangle
        {
            id: replaceGraphOptions
            anchors.top: dialogText.bottom
            anchors.topMargin: parent.height * 0.05
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.07
            width: parent.width * 0.85
            height: parent.height * 0.15
            color: "#E9E9E9"
            visible : showGreyRect
            Row
            {
                id: subDialogColumn
                anchors.centerIn: parent
                spacing: Math.round(10 * Style.scaleHint)
                Text
                {
                    id: subDialogText
                    text: qmltextSubDialog
                    color: Style.frameBorderColor
                    font.family: Style.regular.name
                    font.pixelSize: Math.round(10 * Style.scaleHint) * 0.90
                    visible: showRadioButtons
                }
                Row
                {
                    spacing: Math.round(10 * Style.scaleHint)
                    Repeater
                    {
                        model: radioButtonModel
                        delegate: RadioButton
                        {
                            id:radiobuttoncheck
                            text: model.GraphName
                            visible: showRadioButtons
                            font.pixelSize : replaceGraphOptions.height *0.30
                            onClicked:
                            {
                                oldReferenceWeldResultIndex =  model.Index
                                oldReferenceGraphName = model.GraphName
                            }
                        }
                    }
                }
            }

            Text
            {
                id: refgraphReplaceText
                anchors.centerIn: parent
                text:  qmltextSuccessText + oldReferenceGraphName
                font.pixelSize: parent.height *0.40
                visible: showSuccessMsgText
            }
        }
        BransonPrimaryButton
        {
            id: cancelButton
            implicitWidth: parent.width * 0.27
            implicitHeight: Math.round(22 * Style.scaleHint)
            fontSize: Math.round(11 * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(10 * Style.scaleHint)
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.20
            text: qmltextCancel
            font.family: Style.regular.name
            buttonColor: Style.cancelButtonTextColor
            textColor: "#FFFFFF"
            visible: showCancelButton
            onClicked:
            {
                cancelButtonClicked()
            }
        }

        BransonPrimaryButton
        {
            id: continueorRepalce
            visible: isMultiButtonPopup
            implicitWidth: parent.width * 0.27
            implicitHeight: Math.round(22 * Style.scaleHint)
            fontSize: Math.round(11 * Style.scaleHint)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(10 * Style.scaleHint)
            anchors.left: cancelButton.right
            anchors.leftMargin: (cancelButton.visible) ? parent.width * 0.09 : Math.round(-40 * Style.scaleHint)
            text: qmltextYesContinueorReplace
            font.family: Style.regular.name
            buttonColor: Style.blueFontColor
            textColor: "#FFFFFF"
            onClicked:
            {
                if(!(duplicateRefGraph(newReferenceWeldResultIndex)))
                {
                    if(continueorRepalce.text == qmltextReplace)
                    {
                        ReferenceWeldGraphData.replaceOldGraphWithNewGraphRequest(oldReferenceWeldResultIndex,newReferenceWeldResultIndex)
                    }

                    if(continueorRepalce.text == qmltextContinue)
                    {
                        ReferenceWeldGraphData.addReferenceGraphRequest(newReferenceWeldResultIndex)
                    }

                    oKButtonClicked()
                }
            }
        }
    }
}
