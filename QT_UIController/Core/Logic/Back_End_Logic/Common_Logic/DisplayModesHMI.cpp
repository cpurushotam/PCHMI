/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the DisplayModesHMI related implementation
 ***************************************************************************/
#include "DisplayModesHMI.h"
#include "UpdateScreens.h"
#include "PlatformConfig.h"
#include "FieldbusSupport.h"
#include "MultiwelderInterface.h"

/**************************************************************************//**
*
* \brief   - Constructor DisplayModesHMI class.
*
* \param   - none
*
* \return  - none
*
******************************************************************************/
DisplayModesHMI::DisplayModesHMI(QObject *parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::DisplayModeDataUpdated, this, &DisplayModesHMI::OnDisplayModeUpdated);
}

/*************************************************************************//**
* \brief   - Wrapper function to function DisplayMode on HMI.
*
* \param   - None
*
* \return  - return int DisplayMode to QML.
*
******************************************************************************/
int DisplayModesHMI::getDisplayMode()
{
    int isSupportAvailable = PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), FIELDBUS_SUPPORT_KEY);

    if(isSupportAvailable > NO_FIELDBUS )
    {
        if((m_PlcTokenStatus == TOKEN_ACQUIRED_BY_FIELDBUS) && (m_DisplayMode != MODE_LOCKED))
        {
            m_DisplayMode = MODE_READ_ONLY;
        }
        else if((m_PlcTokenStatus == TOKEN_ACQUIRED_BY_FIELDBUS) && (m_DisplayMode == MODE_LOCKED))
        {
            m_DisplayMode = MODE_LOCKED;
        }
        else if((m_PlcTokenStatus == TOKEN_RELEASED_BY_FIELDBUS) && (m_DisplayMode != MODE_LOCKED))
        {
            m_DisplayMode = MODE_FULLY_FUNCTIONAL;
        }
        else if((m_PlcTokenStatus == TOKEN_RELEASED_BY_FIELDBUS) && (m_DisplayMode == MODE_LOCKED))
        {
            m_DisplayMode = MODE_LOCKED;
        }
        return m_DisplayMode;
    }
    else
    {
        return m_DisplayMode;
    }
}

/*************************************************************************//**
* \brief   - Slot to initlaize the DisplayMgr class pointer to get DisplayMgr class data .
*
* \param   - DisplayMgr class pointer, Welder Id - Current welder Id.
*
* \return  - None.
*
******************************************************************************/
void DisplayModesHMI::OnDisplayModeUpdated(DisplayMgr *DisplayMgr_Obj, int WelderId)
{
    DisplayMgrPtr = DisplayMgr_Obj;

    if(DisplayMgrPtr->GetIsDisplayModeUpdatedFlag() == true )
    {
        m_DisplayMode =  DisplayMgrPtr->GetDisplayMode();
        m_PlcTokenStatus = DisplayMgrPtr->GetFieldBusTokenStatus();
        DisplayMgrPtr->SetIsDisplayModeUpdated();
        emit currentDisplayModeChanged();
    }
    if( m_WelderId != WelderId)
    {
        m_WelderId = WelderId;
    }
}
