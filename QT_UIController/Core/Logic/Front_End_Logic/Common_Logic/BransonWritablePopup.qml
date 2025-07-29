import QtQuick 2.12
import QtQuick.Controls 2.0
import Style 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.SystemTypeDef 1.0

Rectangle
{
    id: popup
    z: 10
    property string qmltextAddNotes          : "Add Notes !"
    property string qmltextSave              : "Save"
    property string qmltextAddNotesDialog
    property bool   isMultiButtonPopup       : false
    property int    index

    property int rectleftMargin: parent.width * 0.43

    property var qmlTextArray: [qmltextAddNotes, qmltextSave]

    signal savedButtonClicked()
    signal closeButtonClicked()

    property string lastValidText: "";
    property int inputlimit: AlarmDetailsListModel.getMaxCharInput()
    enabled: DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_READ_ONLY ? false: true

    function updateLanguage()
    {
        qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.POPUP, qmlTextArray)
        qmltextAddNotes = qmlTextArray[textEnum.textAddNotesIdx]
        qmltextSave = qmlTextArray[textEnum.textSaveIdx]
    }

    QtObject
    {
        id: textEnum
        readonly property int textAddNotesIdx:       0
        readonly property int textSaveIdx:           1
    }

      visible: false
      width: Math.round(500 * Style.scaleHint)
      height: Math.round(250 * Style.scaleHint)
      focus: true
      Rectangle
      {
          id: popupBackground
          anchors.fill: parent
          implicitWidth: parent.width
          implicitHeight: parent.height/*parent.height*/
          opacity: 1
          color:"#ffffff"
          border.width: 0

          Rectangle
          {
              id: popupHeader
              width: parent.width
              implicitHeight: Math.round(50 * Style.scaleHint)
              color: Style.headerBackgroundColor

              Text
              {
                  id: headername
                  anchors.left: parent.left
                  anchors.leftMargin: Math.round(5 * Style.scaleHint)
                  anchors.verticalCenter: parent.verticalCenter
                  text: qmltextAddNotes
                  color: Style.whiteFontColor
                  font
                  {
                      family: Style.regular.name
                      pixelSize: Math.round(Style.style3 * Style.scaleHint)
                      bold: true
                  }
              }

              Image
              {
                  id: imageCross
                  anchors.right: parent.right
                  anchors.rightMargin: Math.round(5 * Style.scaleHint)
                  anchors.verticalCenter: parent.verticalCenter
                  width: Math.round(30 * Style.scaleHint)
                  height: Math.round(30 * Style.scaleHint)
                  sourceSize.width: Math.round(30 * Style.scaleHint)
                  sourceSize.height: Math.round(30 * Style.scaleHint)
                  source: "qrc:/Images/crossMark.svg"
                  fillMode: Image.PreserveAspectFit

                  MouseArea
                  {
                      id: imageCrossMA
                      anchors.fill: parent
                      cursorShape: Qt.PointingHandCursor
                      onClicked:
                      {
                          closeButtonClicked()
                      }
                  }
              }
          }

          TextField
          {
              id: dialogText
              anchors.horizontalCenter: parent.horizontalCenter
              anchors.top: popupHeader.bottom
              anchors.topMargin: Math.round(5 * Style.scaleHint)
              width: parent.width - Math.round(25 * Style.scaleHint)
              height: parent.height - Math.round(100 * Style.scaleHint)
              placeholderText: qmltextAddNotes
              color: Style.textFontColor
              font
              {
                  family: Style.regular.name
                  pixelSize: Math.round(Style.style2 * Style.scaleHint)
              }
              onTextChanged: if (length > inputlimit) remove(inputlimit, length);
          }

          BransonPrimaryButton
          {
              id: save
              implicitWidth: Math.round(124 * Style.scaleHint)
              implicitHeight: Math.round(30 * Style.scaleHint)
              fontSize: Math.round(Style.style2  * Style.scaleHint)
              anchors.top: dialogText.bottom
              anchors.topMargin: Math.round(8 * Style.scaleHint)
              anchors.left: parent.left
              anchors.leftMargin: (isMultiButtonPopup) ? Math.round(200 * Style.scaleHint) :
                                                       Math.round(350 * Style.scaleHint)
              text: qmltextSave
              font.family: Style.regular.name
              buttonColor: Style.blueFontColor
              textColor: "#FFFFFF"
              onClicked:
              {
                  AlarmDetailsListModel.updateSaveNotes(dialogText.text, index)
                  savedButtonClicked()
                  dialogText.text = ""
              }
          }
      }
  }
