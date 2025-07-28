/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
     
---------------------------- MODULE DESCRIPTION ----------------------------

Hash and salt calculation and hash verification using OpenSSL library.
 
***************************************************************************/
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string>
#include <sstream>
#include <iomanip>

#include "HashData.h"
#include "DataLogger.h"

/**************************************************************************//**
* \brief   - constructor
*
* \param   - none	
* \return  - none
*
******************************************************************************/
HashData::HashData()
{
	m_LogID = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - destructor
*
* \param   - none	
* \return  - none
*
******************************************************************************/
HashData::~HashData()
{

}

/**************************************************************************//**
* \brief   - Generate a salt
*
* \param   - none	
* \return  - a random salt string
*
******************************************************************************/
std::string HashData::GenerateSalt()
{
	const int SaltSize = 16;
	unsigned char Salt[SaltSize] = { 0 };
	std::ostringstream HexSalt;
	char  msg[buff_size_config] = {0};
	
	if( RAND_bytes(Salt, SaltSize) !=1)
	{
		snprintf(msg,buff_size_config,"GenerateSalt_Failure");
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	}
	else
	{	
		for (int i = 0; i < SaltSize; ++i) 
		{
			HexSalt << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(Salt[i]);
		}
	}
	return HexSalt.str();
}

/**************************************************************************//**
* \brief   - Calculate hash of the passed Plaintext string
*
* \param   - Plaintext: string whose hash needs to be computed
		   - Salt: salt that will be used during hash calculations	
* \return  - hashed string on success else empty string.

******************************************************************************/
std::string HashData::CalculateHash(const std::string& Plaintext, const std::string& Salt)
{
	const int Iterations = 10000;
	const int HashLengthInBytes = 32; 
	unsigned char Hash[HashLengthInBytes] = { 0 };
	std::ostringstream HexHash;

	char  msg[buff_size_config] = {0};
	 
	int Result = PKCS5_PBKDF2_HMAC(Plaintext.c_str(), Plaintext.length(), (const unsigned char*)Salt.c_str(), Salt.length(), Iterations, EVP_sha512(), HashLengthInBytes, Hash);
	if (Result != 1) 
	{
		// Error occurred during key derivation
		snprintf(msg,buff_size_config,"CalculateHash_Failure");
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	}
	else
	{	
		for (int Index = 0; Index < HashLengthInBytes; ++Index) 
		{
			HexHash << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(Hash[Index]);
		}	
	}
	
	return HexHash.str();
}

/**************************************************************************//**
* \brief   - Verify if the hash calculated using passed Plaintext and Salt  
*			 matches the hash passed in HashedString
* \param   - Plaintext: string whose hash needs to be computed
		   - Salt: salt that will be used during hash calculations
		   - HashedString: hash that needs to be compared with calculated hash
* \return  - true if calculated hash matches passed hash, else false

******************************************************************************/
bool HashData::VerifyHash(const std::string& Plaintext, const std::string& Salt, const std::string& HashedString)
{
	bool Result = false;
	
	//Calculate Hash for the passed Plaintext and Salt combination
	std::string CalculatedHashString = CalculateHash(Plaintext, Salt);
	   
	//Compare the calculated Hash with the passed Hash
    if( (CalculatedHashString.empty() == false) && (CalculatedHashString == HashedString) )
    {
    	Result = true;
    }
    
    return Result;
}


