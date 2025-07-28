import QtQuick 2.12
import QtQuick.Controls 2.0
import QtQuick.Controls 2.15
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0

Rectangle
{
    id: popup
    z: 10
    property string qmltextLabel  : "SELECT UNIT"
    property string qmltextSave   : "SAVE"
    property string qmltextCancel : "CANCEL"

    property int rectleftMargin: parent.width * 0.43
    property string qmltextMetricUnit   : " Metric"
    property string qmltextImperialUnit : " Imperial"
    property var qmlTextArray: [qmltextLabel, qmltextSave]
    property int currUnit
    enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.POPUP, qmlTextArray)
        qmltextLabel = qmlTextArray[textEnum.textWarningIdx]
        qmltextSave = qmlTextArray[textEnum.textOKIdx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textWarningIdx:       0
        readonly property int textOKIdx:            1
        readonly property int textCancelIdx:        2
    }

    QtObject
    {
        id: unitEnum
        readonly property int metricIDX:              0
        readonly property int imperialIDX:            1
    }

    signal oKButtonClicked()
    signal cancelButtonClicked()

    Connections
    {
        target:  mainWindow
        function onCurrentUnit(unit)
        {
            var currUnit =unit
            if(currUnit === unitEnum.metricIDX)
            {
                metricRadioButton.checked = true
                imperialRadioButton.checked = false
            }

            else if(currUnit === unitEnum.imperialIDX)
            {
                metricRadioButton.checked = false
                imperialRadioButton.checked = true
            }
        }
    }
      visible: false
      anchors.left: parent.left
      anchors.leftMargin: rectleftMargin
      anchors.verticalCenter: parent.verticalCenter
      width: mainWindow.showWidth * 0.35
      height: mainWindow.showHeight *0.30
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
              Image {
                  id: crossMark
                  fillMode:Image.PreserveAspectFit;
                  clip:true
                  source: "qrc:/Images/crossMark.svg"
                  anchors.right: parent.right
                  anchors.top:          parent.top
                  anchors.topMargin:    parent.height*0.15
                  anchors.rightMargin:  parent.height/2
                  sourceSize.width:  Math.round(Style.style4 * Style.scaleHint)
                  sourceSize.height: Math.round(Style.style4 * Style.scaleHint)+5

                  MouseArea {
                      anchors.fill: parent
                      onClicked: {
                          oKButtonClicked()
                      }
                  }
              }
          }

          Row
          {
              anchors.centerIn: parent
              x:zoomingSize(10)
              y:zoomingSize(31)
              z:1
              spacing:4
              RadioButton
              {
                  id:metricRadioButton
                  text: qmltextMetricUnit
                  font.pixelSize: zoomingSize(Style.style4)
                  font.family: Style.regular.name
                  onClicked:
                  {
                      currUnit = 0
                  }
              }
              RadioButton
              {
                  id: imperialRadioButton
                  text: qmltextImperialUnit
                  font.pixelSize: zoomingSize(Style.style4)
                  font.family: Style.regular.name
                  onClicked:
                  {
                      currUnit = 1
                  }
              }
          }




          BransonPrimaryButton
          {
              id: cancel
              implicitWidth: parent.width * 0.27
              implicitHeight: Math.round(22 * Style.scaleHint)
              fontSize: Math.round(11 * Style.scaleHint)
              anchors.bottom: parent.bottom
              anchors.bottomMargin: Math.round(10 * Style.scaleHint)
              anchors.left: parent.left
              anchors.leftMargin: parent.width * 0.2
              text: qmltextCancel
              font.family: Style.regular.name
              buttonColor: Style.blueFontColor
              textColor: "#FFFFFF"
              onClicked:
              {
                  oKButtonClicked()
              }
          }



          BransonPrimaryButton
          {
              id: savebutton
              implicitWidth: parent.width * 0.27
              implicitHeight: Math.round(22 * Style.scaleHint)
              fontSize: Math.round(11 * Style.scaleHint)
              anchors.bottom: parent.bottom
              anchors.bottomMargin: Math.round(10 * Style.scaleHint)
              anchors.left: cancel.right
              anchors.leftMargin: parent.width * 0.1
              text: qmltextSave
              font.family: Style.regular.name
              buttonColor: Style.blueFontColor
              textColor: "#FFFFFF"
              onClicked:
              {
                  UnitConversion.sendUnitChangeRequest(currUnit)
                  oKButtonClicked()
              }
          }
      }
  }
