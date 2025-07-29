/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    FullScreenGraphWindow.qml file displays graph data in full screen view.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 10/10/2023 - Initial version.
***************************************************************************/

import QtQuick 2.0
import Style 1.0
import AxisDefine 1.0
import Com.Branson.GraphAxisEnum 1.0
import "./../Common_Logic"

Item {
    Component.onCompleted: {
        graphDataLoadTimer.start()
        chartViewHeader.leftAxisChanged.connect(leftline)
        chartViewHeader.rightAxisChanged.connect(rightline)
    }

    function leftline(index)
    {
        mychart.isPhaseLeftAxisVisible         = false
        mychart.isEnergyLeftAxisVisible        = false
        mychart.isFreqLeftAxisVisible          = false
        mychart.isCurrentLeftAxisVisible       = false
        mychart.isForceLeftAxisVisible         = false
        mychart.isVelocityLeftAxisVisible      = false
        mychart.isAbsoluteDistLeftAxisVisible  = false
        mychart.isCollapseDistLeftAxisVisible  = false
        mychart.isAmpLeftAxisVisible           = false
        mychart.isPowerLeftAxisVisible         = false
        mychart.isReqAmpLeftAxisVisible        = false

        switch(index)
        {
        case GraphAxisEnum.PHASE_IDX:
            mychart.isPhaseLeftAxisVisible         = true
            break;
        case GraphAxisEnum.ENERGY_IDX:
            mychart.isEnergyLeftAxisVisible        = true
            break
        case GraphAxisEnum.FREQ_IDX:
            mychart.isFreqLeftAxisVisible          = true
            break
        case GraphAxisEnum.CURRENT_IDX:
            mychart.isCurrentLeftAxisVisible       = true
            break
        case GraphAxisEnum.FORCE_IDX:
            mychart.isForceLeftAxisVisible         = true
            break
        case GraphAxisEnum.VELOCITY_IDX:
            mychart.isVelocityLeftAxisVisible      = true
            break
        case GraphAxisEnum.ABSOLUTEDIST_IDX:
            mychart.isAbsoluteDistLeftAxisVisible  = true
            break;
        case GraphAxisEnum.COLLAPSEDIST_IDX:
            mychart.isCollapseDistLeftAxisVisible  = true
            break
        case GraphAxisEnum.AMP_IDX:
            mychart.isAmpLeftAxisVisible           = true
            break;
        case GraphAxisEnum.POWER_IDX:
            mychart.isPowerLeftAxisVisible         = true
            break
        case GraphAxisEnum.REQAMP_IDX:
            mychart.isReqAmpLeftAxisVisible         = true
            break
        default:
            break;
        }
        chartViewHeader.rectleftcolor = AxisDefine.getAxisColor(index)
    }

    function rightline(index)
    {
        mychart.isPhaseRightAxisVisible        = false
        mychart.isEnergyRightAxisVisible       = false
        mychart.isFreqRightAxisVisible         = false
        mychart.isCurrentRightAxisVisible      = false
        mychart.isForceRightAxisVisible        = false
        mychart.isVelocityRightAxisVisible     = false
        mychart.isAbsoluteDistRightAxisVisible = false
        mychart.isCollapseDistRightAxisVisible = false
        mychart.isAmpRightAxisVisible          = false
        mychart.isPowerRightAxisVisible        = false
        mychart.isReqAmpRightAxisVisible       = false
        switch(index)
        {
        case GraphAxisEnum.PHASE_IDX:
            mychart.isPhaseRightAxisVisible        = true
            break;
        case GraphAxisEnum.ENERGY_IDX:
            mychart.isEnergyRightAxisVisible       = true
            break;
        case GraphAxisEnum.FREQ_IDX:
            mychart.isFreqRightAxisVisible         = true
            break;
        case GraphAxisEnum.CURRENT_IDX:
            mychart.isCurrentRightAxisVisible      = true
            break;
        case GraphAxisEnum.FORCE_IDX:
            mychart.isForceRightAxisVisible        = true
            break
        case GraphAxisEnum.VELOCITY_IDX:
            mychart.isVelocityRightAxisVisible     = true
            break;
        case GraphAxisEnum.ABSOLUTEDIST_IDX:
            mychart.isAbsoluteDistRightAxisVisible = true
            break;
        case GraphAxisEnum.COLLAPSEDIST_IDX:
            mychart.isCollapseDistRightAxisVisible = true
            break;
        case GraphAxisEnum.AMP_IDX:
            mychart.isAmpRightAxisVisible          = true
            break;
        case GraphAxisEnum.POWER_IDX:
            mychart.isPowerRightAxisVisible        = true
            break;
        case GraphAxisEnum.REQAMP_IDX:
            mychart.isReqAmpRightAxisVisible        = true
        default:
            break;
        }
        chartViewHeader.rectrightcolor = AxisDefine.getAxisColor(index)
    }

    function timechanged(data)
    {
        mychart.timemax = data
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
        }
    }

    BransonChartHeader
    {
        id: chartViewHeader
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: Math.round(50 * Style.scaleHint)
    }

    Rectangle
    {
        id: chartViewWindow
        anchors.top: chartViewHeader.bottom
        anchors.bottom: parent.bottom
        width: parent.width
        BransonChartView
        {
            id: mychart
            anchors.fill: parent
            flagDragDrop: true
            isNormalScreen: false
        }
    }

    Timer
    {
        id: graphDataLoadTimer
        interval: 3000
        repeat: true
        onTriggered:
        {
//            mychart.clearGraph()
//            WeldGraphObj.clearGraph()
//            WeldGraphObj.initiateWeldGraphSignature()
//            mychart.plotGraph()
        }
    }
}
