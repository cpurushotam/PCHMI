/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
     
---------------------------- MODULE DESCRIPTION ----------------------------

Hash and salt calculation and hash verification using OpenSSL library.
 
***************************************************************************/

#ifndef HASH_DATA_H_
#define HASH_DATA_H_

//NOTE: Hashing is a one way process, you can not retrieve back original Plaintext
//from the hashed string. Also during verification of Hash, it is must to use
//the same Salt that was used during hash calculation. So you will have to store
//the Salt value passed to the CalculateHash function in case you want to verify 
//the generated hash at later stage.

class HashData
{
public:
	HashData();
	~HashData();
	std::string GenerateSalt();
	std::string CalculateHash(const std::string& Plaintext, const std::string& Salt);
	bool VerifyHash(const std::string& Plaintext, const std::string& Salt, const std::string& HashedString);  
		
private:	
	size_t m_LogID;
};

#endif // HASH_DATA_H_
