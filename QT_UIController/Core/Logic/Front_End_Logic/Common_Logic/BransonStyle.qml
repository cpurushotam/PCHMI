/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

pragma Singleton //we indicate that this QML Type is a singleton
import QtQuick 2.12
Item {
    readonly property int style1: 13
    readonly property int style2: 14

    readonly property int style3: 15
    readonly property int style4: 16

    readonly property int style5: 18
    readonly property int style6: 20

    readonly property int style7: 26
    readonly property int style8: 40

    readonly property int style9: 72
    readonly property int style10: 115

    readonly property int style0: 12

    readonly property string qmltextEnglish:                qsTr("English")
    readonly property string qmltextGerman:                 qsTr("Deutsche")
    readonly property string qmltextTraditionalChinese:     qsTr("中文(传统的)")
    readonly property string qmltextFrench:                 qsTr("Français")
    readonly property string qmltextKorean:                 qsTr("한국어")
    readonly property string qmltextItalian:                qsTr("Italiano")
    readonly property string qmltextSpanish:                qsTr("Español")
    readonly property string qmltextSimplifiedChinese:      qsTr("中文(简化的)")
    readonly property string qmltextJapanese:               qsTr("日本语")
    readonly property string qmltextDanish:                 qsTr("dansk")
    readonly property string qmltextSlovakian:              qsTr("Slovenský")
    readonly property string qmltextPolish:                 qsTr("Polskie")

    property FontLoader light: FontLoader {
        source: "qrc:/Fonts/OpenSans-Light.ttf"
    }

    property FontLoader regular: FontLoader {
        source: "qrc:/Fonts/OpenSans-Regular.ttf"
    }

    property FontLoader semibold: FontLoader {
        source: "qrc:/Fonts/OpenSans-Semibold.ttf"
    }

    property FontLoader italic: FontLoader {
        source: "qrc:/Fonts/OpenSans-Italic.ttf"
    }

    property color whiteFontColor: Qt.rgba(0xFF, 0xFF, 0xFF)
    property color blackFontColor: "#000000" //Comply Emerson Color Palette
    property color blueFontColor: "#17345C" //Comply Emerson Color Palette
    property color backgroundColor: "#E8E8E8" //Comply Emerson Color Palette
    property color whiteBackgroundColor: "#FFFFFF" //Comply Emerson Color Palette
    property color dialogBackgroundColor: "#dadada"
    property color titleBackgroundColor: "#004B8D"  //Comply Emerson Color Palette
    property color mainWindowOpacityColor: "#dadada"
    property color headerBackgroundColor : "#004B8D" //Comply Emerson Color Palette
    property color buttonBackgroundColor : "#17345C"
    property color disabledButtonBackgroundColor : "#757577"
    property color cancelButtonBackgroundColor: "#6c757d"
    property color navigationMenuBackgroundColor: "#272727" //Comply Emerson Color Palette
    property color frameBorderColor: "#c7c7c7"
    property color activeFrameBorderColor: "#004B8D"
    property color frameButtonBackgroundColor: "#E1EAEA"
    property color blueMachineDetails: "#004b9c"
    property color textFontColor: "#121212"
    property color textFieldBackgoundColor: "#ffffff"
    property color placeHolderTextColor: "#757577"

    property color contentBackgroundColor: "#f0f0f0"
    property color buttonColor: "#17345C"
    property color buttonTextColor: "#ffffff"
    property color cancelButtonTextColor: "#757577"
    property color subHeadingTextColor : "#2d383f"
    property color errorMsgTextColor : "#FF0000"
    property color pageIndicatorBorderColor : "#343A40"

    property color recipeNameFontColor : "#FFFFFF"
    property color recipeModeFrameColor: "#FFFFFF" //Comply Emerson Color Palette
  	property color generateReportCircleColor: "#707070"
    property color generateReportCircleHighlightColor: "#E0EDFA"
    property color opacityEffectColor: "#004B8D"
    property color progressBarBackgroundColor: "#004B8D"
    property color progressBarColor: "#3b82f6"
    property real scaleHint: 1.0
}
