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
#ifndef COMMPEERWRAPPER_H
#define COMMPEERWRAPPER_H

#include <map>
#include "CommPeerInfo.h"

/* CommPeerWrapper Class defination */
class CommPeerWrapper
{


public:
    /* Declaration of map to store instance of each peer inforation with respective peerId*/
    static std::map <int, PeerInfo*> m_PeerMap;

    /* Set instance of peer inforation class with respective peerId into map */
    static bool SetPeerData(int PeerID, PeerInfo *PeerData);

    /* Get instance of peer inforation class based on peerId from map */
    static PeerInfo* GetPeerData(int PeerID);

    /* Return size of peer info map */
    static int SizeOfPeerInfoMap();

    /* Remove peer data from m_PeerMap when peer get disconnected at runtime */
    static bool RemovePeerData(int PeerID);

};

#endif // COMMPEERWRAPPER_H
