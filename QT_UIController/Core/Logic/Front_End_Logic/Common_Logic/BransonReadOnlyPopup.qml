/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    BransonReadOnlyPopup.qml file displays alert message to user.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 30/05/2025 - Initial version.
***************************************************************************/
import QtQuick 2.12
import QtQuick.Controls 2.0
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0
import "../Common_Logic"

Popup
{
    id: popup
    z: 10
    property string qmltextLabel
    property string qmltextWarningDialog
    property string qmltextSubDialog
    property bool isMultiButtonPopup: false
    property bool okButtonToClosePopup: true

    property int rectleftMargin: parent.width * 0.43
    enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true
    closePolicy :Popup.NoAutoClose
    property var qmlTextArray: [qmltextLabel]

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.POPUP, qmlTextArray)
        qmltextLabel = qmlTextArray[textEnum.textWarningIdx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textWarningIdx:       0
    }

      visible: false
      width: mainWindow.showWidth * 0.35
      height: mainWindow.showHeight *0.30
      anchors.centerIn: parent
      focus: true
      background: Rectangle
      {
          id:rectMain
          color:"transparent"
      }

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
          }

          Text
          {
              id: dialogText
              anchors.left: parent.left
              anchors.leftMargin: parent.width * 0.08
              anchors.top: numpadHeader.bottom
              anchors.topMargin:parent.height * 0.15
              anchors.right: parent.right
              anchors.rightMargin: parent.width * 0.08
              text: qmltextWarningDialog
              color: Style.textFontColor
              wrapMode: Text.Wrap
              width:parent.width
              font
              {
                  family: Style.regular.name
                  pixelSize: Math.round(Style.style1 * Style.scaleHint) * 0.90
                  weight : Font.Medium
              }
          }

          Text
          {
              id: subDialogText
              text:qmltextSubDialog
              anchors.top: dialogText.bottom
              anchors.topMargin:parent.height * 0.05
              anchors.left: parent.left
              anchors.leftMargin: parent.width * 0.13
              color: Style.frameBorderColor
              font.family: Style.regular.name
              font.pixelSize: Math.round(10 * Style.scaleHint) * 0.90
          }
      }
  }
