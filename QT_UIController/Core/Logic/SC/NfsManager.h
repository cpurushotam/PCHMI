/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the Weld Nfs Manager Implementation on HMI side.
 
***************************************************************************/

#ifndef NFSMANAGER_H_
#define NFSMANAGER_H_

#include "DataInterface.h"
#include "NfsConfig.h"

class NfsManager : public DataInterface
{
	public :
		NfsManager();
		~NfsManager();

		int GetData(MEMORY_BLOCK * const destination) override;
		int SetData(const MEMORY_BLOCK *const source) override;
		void InitiateNfsMountRequest(NfsConfig nfsConfiData);

	private :

		size_t m_LogID;
		NfsConfig m_NfsConfigData;
		bool m_SendNfsMountRequest;

		void SendNfsMountRequest(MEMORY_BLOCK * const destination);
};
#endif /* NFSMANAGER_H_ */
