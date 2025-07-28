/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2023

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares COMM Peer Wrapper - 	 1. Provide wrapper over Peer info class
                                 2. Responsible for store information of peers

--------------------------- REVISION HISTORY ------------------------------
 rev1: 26/05/2023 - Initial implementation.

***************************************************************************/
#include "CommPeerWrapper.h"

/*****************************************************************************
* \brief   - Initilize static m_PeerMap.
******************************************************************************/
std::map <int,PeerInfo*> CommPeerWrapper::m_PeerMap;

/*****************************************************************************
* \brief   - Insert instance of peer info class into peer map.
*
* \param   - int        PeerId,
*            PeerInfo   *PeerData
*
* \return  - if success true else false
******************************************************************************/
bool CommPeerWrapper::SetPeerData(int PeerId, PeerInfo *PeerData)
{
    m_PeerMap[PeerId]=PeerData;
    return true;
}

/*****************************************************************************
* \brief   - Get instance of peer info class with associated peer id.
*
* \param   - int PeerId
*
* \return  - PeerInfo* - pointer to peer info
******************************************************************************/
PeerInfo* CommPeerWrapper::GetPeerData(int PeerId)
{
    return m_PeerMap[PeerId];
}

/*****************************************************************************
* \brief   - Return size of peer info map.
*
* \param   - None
*
* \return  - int - size of map
******************************************************************************/
int CommPeerWrapper::SizeOfPeerInfoMap()
{
    return m_PeerMap.size();
}

/*****************************************************************************
* \brief   - Delete instance of peer info class from peer map.
*
* \param   - int        PeerId,
*
* \return  - if success true else false
******************************************************************************/
bool CommPeerWrapper::RemovePeerData(int PeerID)
{
    bool status = true;
    if (!m_PeerMap.erase(PeerID))
    {
        status = false;
    }
    return status;
}
