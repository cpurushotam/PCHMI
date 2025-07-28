/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2023

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares MultiwelderInterface Class - responsible for interact between frontend and backend
                                       related to multiwelder.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 31/07/2023 - Initial implementation.
 rev2: 16/10/2023 - Added signal on welder selection changed from HMI
***************************************************************************/

#include "MultiwelderInterface.h"
#include <iostream>
#include "UpdateScreens.h"

int MultiwelderInterface::m_ActiveWelder=-1;

/**************************************************************************//**
*
* \brief  - MultiwelderInterface Constructor
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
MultiwelderInterface::MultiwelderInterface(QObject *parent) : QObject(parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::UnitChangedScreenUpdated, this, &MultiwelderInterface::OnfetchNamesForWelder);
}
/**************************************************************************//**
* \brief   - Return Address of connected welder.
*
* \param   - None
*
* \return  - QString - Address of connected welder.
******************************************************************************/
QString MultiwelderInterface::GetWelderConnected() const
{
    return m_WelderConnected;
}

/**************************************************************************//**
* \brief   - Return Address of disconnected welder.
*
* \param   - None
*
* \return  - QString - Address of disconnected welder.
******************************************************************************/
QString MultiwelderInterface::GetwelderDisconnect() const
{
    return m_welderDisconnect;
}


/**************************************************************************//**
* \brief   - Return Address of connected welder.
*
* \param   - None
*
* \return  - QString - Address of connected welder.
******************************************************************************/
int MultiwelderInterface::GetWelderId() const
{
    return m_welderId;
}
/**************************************************************************//**
* \brief   - Return selected welder ID.
*
* \param   - None.
*
* \return  - int - active welder
******************************************************************************/
int MultiwelderInterface::GetActiveWelder()
{
    return m_ActiveWelder;
}

/**************************************************************************//**
* \brief   - Set selected welder ID.
*
* \param   - int - active welder.
*
* \return  - None
******************************************************************************/
void MultiwelderInterface::setActiveWelder(int activeWelder)
{
    m_ActiveWelder = activeWelder;
    
    // Send signal to config interface to update on HMI
    emit selectWelderIndexChanged(activeWelder);
}

/**************************************************************************//**
* \brief   - Received IP Address of connected welder From WDS Server and send
*            signal to front end.
*
* \param   - uint16_t   welderId  - connected welder id
*            char *     IpAddr    - IP Address of connected welder.
*
* \return  - None -
******************************************************************************/
void MultiwelderInterface::OnPeerConnected(uint16_t welderId, char * IpAddr)
{
    m_WelderConnected=QString::fromStdString(IpAddr);
    m_welderId=welderId;

    // Send signal to frontend on welder connected.
    emit welderConnectedChanged();
}

/**************************************************************************//**
* \brief   - IP Address of disconnected welder From Comm Thread.
*
* \param   - char * IpAddr - IP Address of disconnected welder.
*
* \return  - None -
******************************************************************************/
void MultiwelderInterface::OnwelderRemoved(char *IpAddr)
{
    m_welderDisconnect=QString::fromStdString(IpAddr);

    // Send signal to frontend on welder disconnected.
    emit welderDisconnectChanged();
}
/**************************************************************************//**
* \brief   - Slot for fetching the Welder details .
*
* \param   - SystemConfigurationGeneral_MB class pointer and WelderId.
*
* \return  - None -
******************************************************************************/
void MultiwelderInterface::OnfetchNamesForWelder(SystemConfigurationGeneral_MB *SysConfgGenData_Obj, int WelderId)
{
    m_SysConfgGen = SysConfgGenData_Obj;

    if( m_SysConfgGen->IsDataUpdated() || m_ActiveWelderId != WelderId )
    {
        m_WelderName= QString::fromUtf8(m_SysConfgGen->GetSystemDetailsFromASC().welderName);
        if(m_WelderName != " ")
        {
          emit welderNameReceived(WelderId,m_WelderName);
        }
        m_ActiveWelderId = WelderId;
        m_SysConfgGen->SetIsDataUpdated(false);     /* Set m_IsDataUpdated flag to false after updating the data to HMI. */
    }
}
